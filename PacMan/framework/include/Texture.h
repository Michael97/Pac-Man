//////////////////////////////////////////////////////////////////////////
// Author:	Jamie Stewart
// Date:	25/06/2015
// Brief:	Texture Handler
//////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__
#include <string>

namespace UG
{
	//////////////////////////////////////////////////////////////////////////
	//Class to load in texture data
	//  A texture is just a buffer with some data in it regarding the pixel colours
	//  All texture data is pushed to the GPU on load so that it doesn't occupy memory on the CPU side
	//////////////////////////////////////////////////////////////////////////


	class Texture
	{
	public:
		//A small enumeration to describe image format, single channel (GREY), two channel, three or four channel
		typedef enum Format : unsigned int
		{
			NONE = 0,
			GREY,
			GREY_ALPHA,
			RGB,
			RGBA
		}Format;

		//Constructors
		Texture();
		Texture(const char* a_filename);
		Texture(const char* a_filename, unsigned int a_width, unsigned int a_height, Format a_format, unsigned char* a_pixelData = nullptr);
		//destructor
		virtual ~Texture();
		//Functionality to load or create a texture with an unload function.
		bool	Load(const char* filename);
		bool	Create(const char* a_pName, unsigned int a_width, unsigned int a_height, Format a_format, unsigned char* a_pixelData = nullptr);
		bool	UnLoad();

		//Getters to retrieve information about a texture
		unsigned int			GetHandle() const { return m_glHandle; }
		const std::string&		GetFilename() const { return m_filename; }
		void					GetSize(unsigned int &iWidth, unsigned int &iHeight) const;
		unsigned int			GetWidth() const { return m_iWidth; }
		unsigned int			GetHeight() const { return m_iHeight; }
		unsigned int			GetFormat() const { return m_format; }
		

	private:
		std::string     m_filename;
		unsigned int	m_glHandle;
		Format			m_format;
		int				m_iWidth;
		int				m_iHeight;
		
	};
}//end namespace UG

#endif //__TEXTURE_H__
