////////////////////////////////////////////////////////////////
// Author:	Jamie Stewart
// Date:	25/06/2015
// Brief:	Texture Handler
///////////////////////////////////////////////////////////////

#include "gl_core_4_4.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <cstdio>
#include <string.h>
#include <stdlib.h>

using namespace UG;
///////////////////////////////////////////////////////////////
//constructor
///////////////////////////////////////////////////////////////
Texture::Texture() 
	: m_filename("none"), m_glHandle(0), m_iWidth(0), m_iHeight(0), m_format(NONE)
{

}

Texture::Texture(const char* a_filename) 
	: m_filename(a_filename), m_glHandle(0), m_iWidth(0), m_iHeight(0), m_format(NONE)
{
	if (a_filename != NULL)
	{		
		Load(a_filename);
	}
}

Texture::Texture(const char* a_filename, unsigned int a_width, unsigned int a_height, Format a_format, unsigned char* a_pixelData)
	: m_filename(a_filename), m_glHandle(0), m_iWidth(0), m_iHeight(0), m_format(NONE)
{
	Create(a_filename, a_width, a_height, a_format, a_pixelData);
}


///////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////
Texture::~Texture()
{
	if (m_glHandle != 0)
	{
		glDeleteTextures(1, &m_glHandle);
	}
}
///////////////////////////////////////////////////////////////	
bool Texture::Load(const char* filename)
{
	//if we have a glHandle then we have an image loaded already, this needs to be unloaded.
	if (m_glHandle != 0) {
		glDeleteTextures(1, &m_glHandle);
		m_glHandle = 0;
		m_filename = "none";
	}

	//Call the stbi_load function to load image data into CPU side memory
	int x = 0, y = 0, comp = 0;
	unsigned char* loadedPixels = stbi_load(filename, &x, &y, &comp, STBI_default);

	if (loadedPixels != nullptr)
	{
		glGenTextures(1, &m_glHandle);
		glBindTexture(GL_TEXTURE_2D, m_glHandle);
		unsigned int glImageMode = 0;
		switch (comp) {
		case STBI_grey:
			m_format = GREY;
			glImageMode = GL_RED;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, x, y,
				0, GL_RED, GL_UNSIGNED_BYTE, loadedPixels);
			break;
		case STBI_grey_alpha:
			m_format = GREY_ALPHA;
			glImageMode = GL_RG;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, x, y,
				0, GL_RG, GL_UNSIGNED_BYTE, loadedPixels);
			break;
		case STBI_rgb:
			m_format = RGB;
			glImageMode = GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y,
				0, GL_RGB, GL_UNSIGNED_BYTE, loadedPixels);
			break;
		case STBI_rgb_alpha:
			m_format = RGBA;
			glImageMode = GL_RGBA;
			break;
		default:	//Image Mode not supported
			stbi_image_free(loadedPixels); glDeleteTextures(1, &m_glHandle); return false;
			break;
		};

		glTexImage2D(GL_TEXTURE_2D, 0, glImageMode, x, y, 0, glImageMode, GL_UNSIGNED_BYTE, loadedPixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		
		//Data has already been passed to OpenGL via glTexImage2D, we do not need a CPU side copy
		stbi_image_free(loadedPixels);

		m_iWidth = (unsigned int)x;
		m_iHeight = (unsigned int)y;
		m_filename = filename;
		return true;
	}
	return false;
}

bool Texture::Create(const char* a_pName, unsigned int a_width, unsigned int a_height, Format a_format, unsigned char* a_pixelData)
{
	if (m_glHandle != 0) {
		glDeleteTextures(1, &m_glHandle);
		m_glHandle = 0;
	}

	m_iWidth = a_width;
	m_iHeight = a_height;
	m_format = a_format;
	m_filename = a_pName;
	glGenTextures(1, &m_glHandle);
	glBindTexture(GL_TEXTURE_2D, m_glHandle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	switch (m_format) {
	case GREY:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_iWidth, m_iHeight, 0, GL_RED, GL_UNSIGNED_BYTE, a_pixelData);
		break;
	case GREY_ALPHA:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, m_iWidth, m_iHeight, 0, GL_RG, GL_UNSIGNED_BYTE, a_pixelData);
		break;
	case RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, a_pixelData);
		break;
	case RGBA:
	default:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iWidth, m_iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, a_pixelData);
	};

	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}
///////////////////////////////////////////////////////////////
// Unload() 
///////////////////////////////////////////////////////////////
bool Texture::UnLoad()
{
	if (m_glHandle != 0)
	{
		glDeleteTextures(1, &m_glHandle);
		return true;
	}
	return false;
}
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
void Texture::GetSize(unsigned int &iWidth, unsigned int &iHeight) const
{
	iWidth = m_iWidth;
	iHeight = m_iHeight;
}


