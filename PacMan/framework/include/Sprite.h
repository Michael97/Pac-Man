#pragma once
#ifndef __UG_SPRITE_H__
#define __UG_SPRITE_H__

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>

namespace UG
{
	class Texture;
	//This is a structure to hold the data that is required to render the sprite in the shader
	struct SpriteData
	{
		glm::mat4 posRot;
		glm::vec4 UVCoords;
		glm::vec4 color; 
		glm::vec2 origin;
		glm::vec2 scale;
	};

	struct SpriteVertex
	{
		glm::vec4 position;
		glm::vec2 uv;
	};

	struct SpriteVertexData
	{
		SpriteVertex vertex[4];
	};

	class Sprite
	{
	public:
		Sprite(const char* a_pTexture, const glm::vec2& a_v2Size, const glm::vec2& a_v2Origin, const glm::vec4 a_fv4UVCoordinates = glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4 a_v4colour = glm::vec4(1.f, 1.f, 1.f, 1.f));
		Sprite(const glm::vec2& a_v2Size, const glm::vec2& a_v2Origin, const glm::vec4 a_fv4UVCoordinates = glm::vec4(0.f, 0.f, 1.f, 1.f), glm::vec4 a_v4colour = glm::vec4(1.f, 1.f, 1.f, 1.f));
		Sprite(const Sprite& pSprite);
		~Sprite();
		///////////////////////////////////////////////////////////////////////////
		// Fucntions to set and Get sprite attributes 
		///////////////////////////////////////////////////////////////////////////
		void					setRotation(const float a_iRotation);
		
		void					SetColour(const glm::vec4& a_v4colour);
		void					GetColour(glm::vec4& a_v4colour) const;

		void					SetPosition(glm::vec4& a_pos);
		void					GetPosition(glm::vec4& a_pos) const;

		void					SetMatrix(glm::mat4& a_mat4);
		void					GetMatrix(glm::mat4& a_mat4) const;

		void					SetOrigin(const glm::vec2& a_v2Origin);
		void					GetOrigin(glm::vec2& a_v2Origin) const;

		void					SetSize(float a_iWidth, float a_iHeight);
		void					GetSize(float& a_iWidth, float& a_iHeight) const;

		Texture*				GetTexture() const { return m_pTexture; }
		unsigned int			GetTextureID() const;
		

		void					SetUVCoords(const glm::vec2& a_minUVCoords, const glm::vec2& a_maxUVCoords);
		void					GetUVCoords(glm::vec2& a_minUVCoords, glm::vec2& a_maxUVCoords) const;

		void					SetLayer(unsigned int a_uLayer);
		unsigned int			GetLayer() const { return (unsigned int)(-m_spriteData.posRot[3][2]); }

		void					SetBlendParameters(const unsigned int& a_uiSourceFactor, const unsigned int& a_uiDestinationFactor);
		void					GetBlendParameters(unsigned int& a_uiSourceFactor, unsigned int& a_uiDestinationFactor) const;
		
		void					GetSpriteData(SpriteData& a_spriteData) const { a_spriteData = m_spriteData; }
		const SpriteData&		GetSpriteData() const { return m_spriteData; }

		static const SpriteVertexData vboData;
		static const unsigned int vboIndex[6];

	private:
		SpriteData		m_spriteData;

		std::string		m_textureName;
		Texture*		m_pTexture;
		
		unsigned int	m_uSourceBlendMode;
		unsigned int	m_uDestinationBlendMode;
		
		

	};
	///////////////////////////////////////////////////////////////////////////
	//inline functions 
	// these are inlined to improve performance as they are called frequently
	///////////////////////////////////////////////////////////////////////////
	inline void Sprite::SetPosition(glm::vec4& a_pos)
	{
		m_spriteData.posRot[3] = a_pos;
	}

	inline void Sprite::GetPosition(glm::vec4& a_pos) const
	{
		a_pos = m_spriteData.posRot[3];
	}

	inline void Sprite::SetMatrix(glm::mat4& a_mat4)
	{
		m_spriteData.posRot = a_mat4;
	}

	inline void Sprite::GetMatrix(glm::mat4& a_mat4) const
	{
		a_mat4 = m_spriteData.posRot;
	}

	inline void Sprite::SetSize(float a_iWidth, float a_iHeight)
	{
		m_spriteData.scale = glm::vec2(a_iWidth, a_iHeight);
	}

	inline void Sprite::GetSize(float& a_iWidth, float& a_iHeight) const
	{
		a_iWidth = m_spriteData.scale.x;
		a_iHeight = m_spriteData.scale.y;
	}
}//end namespace UG

#endif //__UG_SPRITE_H__
