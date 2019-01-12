//////////////////////////////////////////////////////////////////////////
//	Author:	Jamie Stewart
//	Date:	08/07/2015
//	Brief:	Class to manage sprites
//////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef _SPRITEMANAGER_H_
#define _SPRITEMANAGER_H_
//////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>
#include <queue>

#include "Sprite.h"

namespace UG
{
	//////////////////////////////////////////////////////////////////////////
	/*struct SpriteBatch
	{
		unsigned int iNumToRender;
		SpriteVertexData svd[64];
	};*/
	//////////////////////////////////////////////////////////////////////////
	class SpriteManager
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		//This class is a static instance or a singleton class
		//////////////////////////////////////////////////////////////////////////
		static SpriteManager* CreateInstance();
		static SpriteManager* GetInstance();
		static void DestroyInstance();
		//////////////////////////////////////////////////////////////////////////
		void Draw(unsigned int a_uiShaderID);
		//////////////////////////////////////////////////////////////////////////
		int				AddSprite(const char* a_pTexture, glm::vec2& a_v2Size, glm::vec2& a_v2Origin, glm::vec4 a_vfUVCoords = glm::vec4(0.f, 0.f, 1.f,1.f), glm::vec4 a_v4colour = glm::vec4(1.f, 1.f, 1.f, 1.f));
		int				AddSprite( glm::vec2& a_v2Size, glm::vec2& a_v2Origin, glm::vec4 a_vfUVCoords = glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4 a_v4colour = glm::vec4(1.f, 1.f, 1.f, 1.f));
		int				DuplicateSprite(int a_uiSpriteID);
		void			RemoveSprite(int a_uiSpriteID);

		void			MarkSpriteForDraw(int a_uiSpriteID);
		

		Sprite*			GetSprite(int a_iSpriteID);
		int				GetLineSpriteID() { return m_lineSprite; }

	protected:

		SpriteManager();
		~SpriteManager();

		int FindSpriteIndex(Sprite* a_pSprite);

		struct SpriteDataObject {
			SpriteData m_data;
			unsigned int m_textureID;
		};
		//function for sorting the Render Queue Based on Layer and texture ID
		struct SortRenderQueue {
			bool operator()(const SpriteDataObject& lhs, const SpriteDataObject& rhs) const {
				if (lhs.m_data.posRot[3][2] != rhs.m_data.posRot[3][2]) {
					return lhs.m_data.posRot[3][2] > rhs.m_data.posRot[3][2];
				}
				else if (lhs.m_textureID != rhs.m_textureID) {
					return lhs.m_textureID < rhs.m_textureID;
				}
				else
					return false;
			}
		};
		//Struct to be used as a getter for retreiving sprite data from a base sprite
		struct SpriteDataGetter {
			const UG::SpriteData& operator()(const SpriteDataObject& sprite) const
			{
				return sprite.m_data;
			}
		};

	private:
		

		std::vector<Sprite*>				m_Sprites;
		
		std::vector<SpriteDataObject>		m_vSpriteData;
		
		static SpriteManager*				m_pInstance;
		unsigned int m_lineSprite;
		unsigned int m_ShaderID;

		unsigned int m_uiVAO;
		unsigned int m_uiVBO;
		unsigned int m_uiIBO;

		unsigned int dtb;
		static unsigned int DefaultBufferCapacity;

	};

}//end namespace UG

 //////////////////////////////////////////////////////////////////////////
#endif //_SPRITEMANAGER_H_
 //////////////////////////////////////////////////////////////////////////