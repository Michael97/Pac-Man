#pragma once

#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <map>
#include <string>



namespace UG {

	class Texture;
	//////////////////////////////////////////////////////////////////////////
	//A manager class for the textures currently in memory
	//////////////////////////////////////////////////////////////////////////
	class TextureManager
	{
	protected:
		TextureManager();
		~TextureManager();
	public:
		static TextureManager*		CreateInstance();
		static TextureManager*		GetInstance();
		static void					DestroyInstance();

		bool		TextureExists(const char* a_filename, Texture* a_texture) const;
		Texture*	LoadTexture(const char* a_pTextureName);
		Texture*	CreateTexture(const char* a_pName, unsigned int a_width, unsigned int a_height, unsigned char* a_pixelData = nullptr, unsigned int a_format = 1);
		void	    RemoveTexture(Texture* a_texture);
		
	private:
		static TextureManager*					m_pInstance;
		struct TextureRef
		{
			Texture* pTexture;
			unsigned int refCout;
		};

		std::map< std::string, TextureRef >		m_pTextureDictionary;
		
	};


}//namespace UG

#endif //__TEXTURE_MANAGER_H__

