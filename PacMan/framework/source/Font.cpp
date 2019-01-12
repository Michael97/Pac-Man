#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include "Font.h"
#include <stdio.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#include "TextureManager.h"
#include "Texture.h"
#include "SpriteManager.h"

using namespace UG;

Font::Font(const char* trueTypeFontFile, unsigned short fontHeight)
	: m_glyphData(nullptr), m_texture(nullptr),	m_textureWidth(0),	m_textureHeight(0), m_spriteID(0)
{

	FILE* file = nullptr;
	fopen_s(&file, trueTypeFontFile, "rb");
	if (file != nullptr) 
	{
		unsigned char* ttf_buffer = new unsigned char[4096 * 1024];
		memset(ttf_buffer, 0, sizeof(unsigned char) * 4096 * 1024);
		fread(ttf_buffer, sizeof(unsigned char), 4096 * 1024, file);
		fclose(file);

		m_fontInfo = new stbtt_fontinfo();
		stbtt_InitFont(m_fontInfo, ttf_buffer, 0);

		// determine size of texture image
		m_textureWidth = fontHeight / 16 * 256;
		m_textureHeight = fontHeight / 16 * 256;

		if (fontHeight <= 16) {
			m_textureWidth = 256;
			m_textureHeight = 256;
		}

		if (m_textureWidth > 2048)
			m_textureWidth = 2048;
		if (m_textureHeight > 2048)
			m_textureHeight = 2048;

		unsigned char* tempBitmapData = new unsigned char[m_textureWidth * m_textureHeight];
		memset(tempBitmapData, 0, sizeof(unsigned char) * m_textureWidth * m_textureHeight);

		m_glyphData = new stbtt_bakedchar[256];
		memset(m_glyphData, 0, sizeof(stbtt_bakedchar) * 256);
		stbtt_BakeFontBitmap(ttf_buffer, 0, fontHeight, tempBitmapData, m_textureWidth, m_textureHeight, 0, 256, (stbtt_bakedchar*)m_glyphData);
		m_texture = TextureManager::GetInstance()->CreateTexture(trueTypeFontFile, m_textureWidth, m_textureHeight, tempBitmapData, Texture::Format::GREY);

		//Now that we have a texture loaded create a sprite to make use of this texture for rendering
		glm::vec2 size = glm::vec2(0.f, 0.f);
		glm::vec2 origin = glm::vec2(0.5f, 0.5f);
		m_spriteID = SpriteManager::GetInstance()->AddSprite(trueTypeFontFile, size, origin );


		delete[] ttf_buffer;
	}
}

Font::~Font() {
	delete[](stbtt_bakedchar*)m_glyphData;
	delete m_fontInfo;
	if (m_texture != nullptr)
	{
		TextureManager::GetInstance()->RemoveTexture(m_texture);
	}
	
}

unsigned int Font::GetTextureHandle() const
{
	return m_texture->GetHandle();
}

void Font::GetStringSize(const char* a_str, float& a_width, float& a_height)
{

	stbtt_aligned_quad Q = {};
	float low = 9999999, high = -9999999;
	float xPos = 0.0f;
	float yPos = 0.0f;

	while (*a_str != 0) 
	{
		stbtt_GetBakedQuad(
			(stbtt_bakedchar*)m_glyphData,
			m_textureWidth,
			m_textureHeight,
			(unsigned char)*a_str, &xPos, &yPos, &Q, 1);

		low = low > Q.y0 ? Q.y0 : low;
		high = high < Q.y1 ? Q.y1 : high;

		a_str++;
	}

	a_height = high - low;
	a_width = Q.x1;
}

void Font::GetStringBounds(const char* a_str, float& a_x0, float& a_y0, float& a_x1, float& a_y1) 
{

	stbtt_aligned_quad Q = {};
	a_y1 = 9999999, a_y0 = -9999999;
	a_x0 = 9999999, a_x1 = -9999999;
	float xPos = 0.0f;
	float yPos = 0.0f;

	while (*a_str != 0) {
		stbtt_GetBakedQuad(
			(stbtt_bakedchar*)m_glyphData,
			m_textureWidth,
			m_textureHeight,
			(unsigned char)*a_str, &xPos, &yPos, &Q, 1);

		a_y1 = a_y1 > Q.y0 ? Q.y0 : a_y1;
		a_y0 = a_y0 < Q.y1 ? Q.y1 : a_y0;

		a_x1 = a_x1 < Q.x1 ? Q.x1 : a_x1;
		a_x0 = a_x0 > Q.x0 ? Q.x0 : a_x0;

		a_str++;
	}

	a_y0 *= -1;
	a_y1 *= -1;
}

void Font::DrawString(const char* a_str, glm::vec4 a_v4Position, unsigned int a_layer, glm::vec4 a_v4colour)
{
	stbtt_aligned_quad Q = {};

	// font renders top to bottom, so we need to invert it
	int w = 0, h = 0;
	glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);

	float xPos = a_v4Position.x; float yPos = a_v4Position.y;
	yPos = h - yPos;

	float currX = 0.f; 
	SpriteManager* spMan = SpriteManager::GetInstance();
	if (spMan)
	{
		Sprite* pSprite = spMan->GetSprite(m_spriteID);
		pSprite->SetColour(a_v4colour);
		
		while (*a_str != 0)
		{
			currX = xPos;
			stbtt_GetBakedQuad((stbtt_bakedchar*)m_glyphData, m_textureWidth, m_textureHeight, *a_str, &xPos, &yPos, &Q, 1);
			float fWidth = Q.x1 - Q.x0;
			float fHeight = Q.y1 - Q.y0;
			
			pSprite->SetSize(fWidth,fHeight);
			float halfH = fHeight * 0.5f;
			float offset = h - Q.y1;
			float expectedYPos = halfH + offset;
			glm::vec4 spritePos = glm::vec4(currX + (fWidth * 0.5f), expectedYPos, 0.f, -1.f);
			pSprite->SetPosition(spritePos);
			pSprite->SetLayer(a_layer);
			glm::vec2 minUV = glm::vec2(Q.s0, Q.t0);
			glm::vec2 maxUV = glm::vec2(Q.s1, Q.t1);
			pSprite->SetUVCoords(minUV, maxUV);
			spMan->MarkSpriteForDraw(m_spriteID);


			++a_str;
		}
	}
}