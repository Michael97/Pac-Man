#pragma once
#ifndef __UG_FONT_H__
#define __UG_FONT_H__


#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct stbtt_fontinfo;

namespace UG
{
	class Texture;

	// a class that wraps up a True Type Font within an OpenGL texture
	class Font
	{
		friend class FontManager;
	public:

		Font(const char* a_fontFile, unsigned short a_fontHeight);
		~Font();

		// returns the OpenGL texture handle
		unsigned int	GetTextureHandle() const;

		// returns size of string using this font
		// height includes characters that go below starting height
		void GetStringSize(const char* a_str, float& a_width, float& a_height);

		// returns a rectangle that fits the string, with x0y0 being bottom left, x1y1 top right
		void GetStringBounds(const char* str, float& a_x0, float& a_y0, float& a_x1, float& a_y1);

		void DrawString(const char* a_str, glm::vec4 v4Position, unsigned int a_layer, glm::vec4 v4colour = glm::vec4(1.f, 1.f, 1.f, 1.f) );
	private:
		stbtt_fontinfo*	m_fontInfo;
		Texture*		m_texture;
		unsigned int	m_spriteID;
		void*			m_glyphData;
		//unsigned int	m_glHandle, m_pixelBufferHandle;
		unsigned short	m_textureWidth, m_textureHeight;
	};

}//end namespace

#endif //__UG_FONT_H__