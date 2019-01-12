#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>

#include "Sprite.h"
#include "TextureManager.h"
#include "Texture.h"

namespace UG
{
	//===================================================================================================================================================
	//As instnacing is being used to render the sptires every sprite shares a vertex and index buffer.
	const SpriteVertexData Sprite::vboData = {
		SpriteVertex{ glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec2(0.f, 1.f) },
		SpriteVertex{ glm::vec4(1.f, 0.f, 0.f, 1.f), glm::vec2(1.f, 1.f) },
		SpriteVertex{ glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec2(0.f, 0.f) },
		SpriteVertex{ glm::vec4(1.f, 1.f, 0.f, 1.f), glm::vec2(1.f, 0.f) },
	};
	const unsigned int Sprite::vboIndex[6] = { 0,1,2,1,3,2 };
	//===================================================================================================================================================

	Sprite::Sprite(const char* a_pTexture, const glm::vec2& a_v2Size, const glm::vec2& a_fOrigin, const glm::vec4 a_fv4UVCoordinates, glm::vec4 a_v4colour)
	{
		m_spriteData.posRot = glm::mat4(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		SetSize(a_v2Size.x, a_v2Size.y);
		SetOrigin(a_fOrigin);
		m_spriteData.color = a_v4colour;
		m_pTexture = nullptr;
		SetUVCoords(glm::vec2(a_fv4UVCoordinates.x, a_fv4UVCoordinates.y), glm::vec2(a_fv4UVCoordinates.z, a_fv4UVCoordinates.w));
		m_uSourceBlendMode = GL_SRC_ALPHA;
		m_uDestinationBlendMode = GL_ONE_MINUS_SRC_ALPHA;
		m_textureName = a_pTexture;
		if (TextureManager::GetInstance())
		{
			m_pTexture = (a_pTexture != nullptr) ? TextureManager::GetInstance()->LoadTexture(a_pTexture) : nullptr;
		}
	}

	Sprite::Sprite(const glm::vec2& a_v2Size, const glm::vec2& a_v2Origin, const glm::vec4 a_fv4UVCoordinates, glm::vec4 a_v4colour)
	{
		m_spriteData.posRot = glm::mat4(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		SetSize(a_v2Size.x, a_v2Size.y);
		SetOrigin(a_v2Origin);
		m_spriteData.color = a_v4colour;
		m_pTexture = nullptr;
		SetUVCoords(glm::vec2(a_fv4UVCoordinates.x, a_fv4UVCoordinates.y), glm::vec2(a_fv4UVCoordinates.z, a_fv4UVCoordinates.w));
		m_uSourceBlendMode = GL_SRC_ALPHA;
		m_uDestinationBlendMode = GL_ONE_MINUS_SRC_ALPHA;
		m_textureName = "none";
		if (TextureManager::GetInstance())
		{
			unsigned int pixels[1] = { 0xFFFFFFFF };
			m_pTexture = TextureManager::GetInstance()->CreateTexture("none", 1, 1, (unsigned char*)pixels, Texture::Format::RGBA);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	Sprite::Sprite(const Sprite& pSprite)
	{
		m_spriteData.posRot = pSprite.m_spriteData.posRot;
		m_spriteData.color = pSprite.m_spriteData.color;
		m_spriteData.origin = pSprite.m_spriteData.origin;
		m_spriteData.scale = pSprite.m_spriteData.scale;
		m_spriteData.UVCoords = pSprite.m_spriteData.UVCoords;
		m_textureName = pSprite.m_textureName;
		m_uSourceBlendMode = pSprite.m_uSourceBlendMode;;
		m_uDestinationBlendMode = pSprite.m_uDestinationBlendMode;
		
		if (TextureManager::GetInstance())
		{
			m_pTexture = TextureManager::GetInstance()->LoadTexture(m_textureName.c_str());
		}
	}

	//////////////////////////////////////////////////////////////////////////
	Sprite::~Sprite()
	{
		if (TextureManager::GetInstance())
		{
			TextureManager::GetInstance()->RemoveTexture(m_pTexture);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	// Set the origin point for the matrix
	// - Note: a_v2Origin should be a value between 0 and 1 for both x and y
	//   as this is a ratio position
	//////////////////////////////////////////////////////////////////////////
	void Sprite::SetOrigin(const glm::vec2& a_v2Origin)
	{
		m_spriteData.origin = a_v2Origin;
		if (m_spriteData.origin.x > 1.f || m_spriteData.origin.y > 1.f)
		{
			m_spriteData.origin = m_spriteData.origin / m_spriteData.scale.xy;
		}
	}

	void Sprite::GetOrigin(glm::vec2& a_v2Origin) const
	{
		a_v2Origin = m_spriteData.origin;
	}
	//////////////////////////////////////////////////////////////////////////
	void Sprite::setRotation(float a_iRotation)
	{
		float Deg2Rad = 0.01745329251994329577f;
		float fRadians = a_iRotation *  Deg2Rad;
		m_spriteData.posRot = glm::rotate(m_spriteData.posRot, fRadians, glm::vec3(0.f, 0.f, 1.f));
	}
	///////////////////////////////////////////////////////////////////////////
	void	Sprite::SetColour(const glm::vec4& a_v4colour)
	{
		m_spriteData.color = a_v4colour;
	}

	void	Sprite::GetColour(glm::vec4& a_v4colour) const
	{
		a_v4colour = m_spriteData.color;
	}
	///////////////////////////////////////////////////////////////////////////
	void	Sprite::SetUVCoords(const glm::vec2& a_minUVCoords, const glm::vec2& a_maxUVCoords)
	{
		m_spriteData.UVCoords = glm::vec4(a_minUVCoords, a_maxUVCoords - a_minUVCoords);

	}

	void	Sprite::GetUVCoords(glm::vec2& a_minUVCoords, glm::vec2& a_maxUVCoords) const
	{
		a_minUVCoords = m_spriteData.UVCoords.xy;
		a_maxUVCoords = m_spriteData.UVCoords.xy + m_spriteData.UVCoords.zw;
	}

	void	Sprite::SetBlendParameters(const unsigned int& a_uiSourceFactor, const unsigned int& a_uiDestinationFactor)
	{
		m_uSourceBlendMode = a_uiSourceFactor;
		m_uDestinationBlendMode = a_uiDestinationFactor;
	}

	void	Sprite::GetBlendParameters(unsigned int& a_uiSourceFactor, unsigned int& a_uiDestinationFactor) const
	{
		a_uiSourceFactor = m_uSourceBlendMode;
		a_uiDestinationFactor = m_uDestinationBlendMode;
	}

	unsigned int Sprite::GetTextureID() const 
	{
		return m_pTexture->GetHandle();
	}

	void Sprite::SetLayer(unsigned int a_uLayer)
	{
		m_spriteData.posRot[3][2] = -(float)(a_uLayer); 
	}

} // namespace UG