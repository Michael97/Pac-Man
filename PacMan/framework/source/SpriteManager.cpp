//////////////////////////////////////////////////////////////////////////
//	Author:	Jamie Stewart
//	Date:	08/07/2015
//	Brief:	Class to manage sprites
//////////////////////////////////////////////////////////////////////////
#include "gl_core_4_4.h"
#include "SpriteManager.h"
#include "TextureManager.h"

#include "UG_Assert.h"
#include <iterator>
#include <algorithm>

namespace UG
{
	unsigned int SpriteManager::DefaultBufferCapacity = 10000;

	SpriteManager* SpriteManager::m_pInstance = 0;
	//////////////////////////////////////////////////////////////////////////
	SpriteManager* SpriteManager::CreateInstance()
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new SpriteManager();
		}
		return m_pInstance;
	}
	//////////////////////////////////////////////////////////////////////////
	SpriteManager* SpriteManager::GetInstance()
	{
		return m_pInstance;
	}
	//////////////////////////////////////////////////////////////////////////
	void SpriteManager::DestroyInstance()
	{
		if (m_pInstance != NULL)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	SpriteManager::SpriteManager()
	{

		glGenVertexArrays(1, &m_uiVAO);
		glBindVertexArray(m_uiVAO);
		glGenBuffers(1, &m_uiVBO);
		glGenBuffers(1, &m_uiIBO);

		glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(SpriteVertex), Sprite::vboData.vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), Sprite::vboIndex, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(UG::SpriteVertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(UG::SpriteVertex), ((char*)0) + 16);
		
		glBindVertexArray(0);

		glGenBuffers(1, &dtb);
		glBindBuffer(GL_TEXTURE_BUFFER, dtb);
		glBufferData(GL_TEXTURE_BUFFER, sizeof(SpriteData) * DefaultBufferCapacity, nullptr, GL_STATIC_DRAW);

		glBindBuffer(GL_TEXTURE_BUFFER, 0);

		glm::vec2 v2Size = glm::vec2(1.f, 1.f);
		glm::vec2 v2Origin = glm::vec2(0.f, 0.5f);
		glm::vec4 uvCoords = glm::vec4(0.f, 0.f, 1.f, 1.f);

		m_lineSprite = AddSprite(v2Size, v2Origin, uvCoords);

	}
	//////////////////////////////////////////////////////////////////////////
	SpriteManager::~SpriteManager()
	{
		RemoveSprite(m_lineSprite);
		//Get rid of the texture buffer that is used for sprites
		glDeleteBuffers(1, &dtb);

		glDeleteVertexArrays(1, &m_uiVAO);
		glDeleteBuffers(1, &m_uiVBO);
		glDeleteBuffers(1, &m_uiIBO);

	}
	//////////////////////////////////////////////////////////////////////////
	//Draw Sprite
	// Sort the sprites in a buffer based on the following criteria
	//  - layer
	//  - texture ID (group textures together)
	//  - blendModes?
	//////////////////////////////////////////////////////////////////////////
	void SpriteManager::Draw(unsigned int a_uiShaderID)
	{
		//sort and fill the sprite data buffers
				
		
		//\=======================================================================

		// set the texture to use slot 0 in the shader
		GLuint texUniformID = glGetUniformLocation(a_uiShaderID, "diffuseTexture");
		glUniform1i(texUniformID, 0);

		glBindVertexArray(m_uiVAO);

		glActiveTexture(GL_TEXTURE0);
		

		if (m_vSpriteData.size() > 0)
		{
			//Get an iterator to the first object in the render queue
			std::sort(m_vSpriteData.begin(), m_vSpriteData.end(), SortRenderQueue());

			auto it = m_vSpriteData.cbegin();
			auto begin = it;
			auto last = std::prev(m_vSpriteData.end());
			//use this object to set the initial values for the layer and texture
			unsigned int currentLayer = (unsigned int)((*it).m_data.posRot[3][2]);
			unsigned int currentTextureID = (*it).m_textureID;
			unsigned int layer = currentLayer;
			unsigned int textureID = currentTextureID;

			glBindBuffer(GL_TEXTURE_BUFFER, dtb);
			glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, dtb);

			for (; it != m_vSpriteData.cend(); ++it)
			{
				layer = (unsigned int)(fabsf((*it).m_data.posRot[3][2]));
				textureID = (*it).m_textureID;
				if (it == last || layer != currentLayer || textureID != currentTextureID)
				{
					auto end = (it == last) ? (layer != currentLayer || textureID != currentTextureID) ? it : m_vSpriteData.cend() : it;

					//A change in layer or texture has occurred lets draw all the sprites 
					//copy all the items we have iterated over into the sprite data vector
					std::vector< UG::SpriteData > spriteData;
					//reserve some space for the vector
					spriteData.reserve(std::distance(begin, it));
					std::transform(begin, end, std::back_inserter(spriteData), SpriteDataGetter());

					glBindTexture(GL_TEXTURE_2D, currentTextureID);


					//If we have loads of sprites we need to resize the texture that we're using for instancing
					//TODO:: if capacity is greater than 80,000 then perhaps use multiple texture buffer objects?
					if (spriteData.size() > DefaultBufferCapacity)
					{
						DefaultBufferCapacity *= 2;
						glBufferData(GL_TEXTURE_BUFFER, sizeof(SpriteData) * DefaultBufferCapacity, nullptr, GL_STATIC_DRAW);
					}

					glBufferSubData(GL_TEXTURE_BUFFER, 0, spriteData.size() * sizeof(UG::SpriteData), &spriteData[0]);
					glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, (GLsizei)spriteData.size());

					currentLayer = layer;
					currentTextureID = textureID;
					begin = it;

					if (it == last && end != m_vSpriteData.cend())
					{
						it--;
					}

				}
			}
		}
		m_vSpriteData.clear();



		glUseProgram(0);
	}
	//////////////////////////////////////////////////////////////////////////
	// Finds an index for the sprite 
	//////////////////////////////////////////////////////////////////////////

	int SpriteManager::FindSpriteIndex(Sprite* a_pSprite)
	{
		if (m_Sprites.size() > 0)
		{
			auto sprite_iter = m_Sprites.begin();
			for (unsigned int i = 0; sprite_iter != m_Sprites.end(); ++sprite_iter, ++i)
			{
				if ((*sprite_iter) == a_pSprite)
				{
					return i;
				}
			}
		}
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
	// Adds a sprite to the sprite manager, 
	//////////////////////////////////////////////////////////////////////////
	int SpriteManager::AddSprite(const char* a_pTexture, glm::vec2& a_v2Size, glm::vec2& a_v2Origin, glm::vec4 a_vfUVCoords, glm::vec4 a_v4colour)
	{
		Sprite* pSprite = new Sprite(a_pTexture, a_v2Size, a_v2Origin, a_vfUVCoords, a_v4colour);
		int index = FindSpriteIndex(nullptr);
		if (index != -1)
		{
			m_Sprites[index] = pSprite;
		}
		else
		{
			m_Sprites.push_back(pSprite);
			index = ((int)m_Sprites.size() - 1);
		}
		return index;
	}

	int SpriteManager::AddSprite(glm::vec2& a_v2Size, glm::vec2& a_v2Origin, glm::vec4 a_vfUVCoords, glm::vec4 a_v4colour)
	{
		Sprite* pSprite = new Sprite(a_v2Size, a_v2Origin, a_vfUVCoords, a_v4colour);
		int index = FindSpriteIndex(nullptr);
		if (index != -1)
		{
			m_Sprites[index] = pSprite;
		}
		else
		{
			m_Sprites.push_back(pSprite);
			index = ((int)m_Sprites.size() - 1);
		}
		return index;
	}
	//////////////////////////////////////////////////////////////////////////
	// duplicates a sprite that already exists in the sprite manager
	//////////////////////////////////////////////////////////////////////////
	int SpriteManager::DuplicateSprite(int a_uiSpriteID)
	{
		int index = -1;
		if (m_Sprites.size() > 0)
		{
			Sprite* pSprite = m_Sprites[a_uiSpriteID];
			if (pSprite != NULL)
			{
				Sprite* pCopyOfSprite = new Sprite(*pSprite);
				index = FindSpriteIndex(nullptr);
				if (index != -1)
				{
					m_Sprites[index] = pCopyOfSprite;
				}
				else
				{
					m_Sprites.push_back(pCopyOfSprite);
					index = ((int)m_Sprites.size() - 1);
				}
			}
		}
		return index;
	}

	//////////////////////////////////////////////////////////////////////////
	//Gets rid of a sprite from our sprite manager
	//////////////////////////////////////////////////////////////////////////
	void SpriteManager::RemoveSprite(int a_uiSpriteID)
	{
		Sprite* pSprite = m_Sprites[a_uiSpriteID];
		if (pSprite != nullptr)
		{
			delete pSprite;
			m_Sprites[a_uiSpriteID] = pSprite = nullptr;
		}
	}

	
	Sprite* SpriteManager::GetSprite(int a_iSpriteID)
	{
		Sprite* pSprite = m_Sprites[a_iSpriteID];
		return pSprite;
	}
	//////////////////////////////////////////////////////////////////////////
	// Mark for Draw
	// Pushes a copy of the sprite into the draw queue
	//////////////////////////////////////////////////////////////////////////
	void SpriteManager::MarkSpriteForDraw(int a_uiSpriteID)
	{
		Sprite* pSprite = m_Sprites[a_uiSpriteID];
		if (pSprite != nullptr)
		{
			SpriteDataObject sdo;
			sdo.m_data = pSprite->GetSpriteData();
			sdo.m_textureID = pSprite->GetTextureID();

			m_vSpriteData.push_back(sdo);
		}
	}

}//namespace UG