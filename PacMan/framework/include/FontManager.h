#pragma once

#ifndef __UG_FONT_MANAGER_H__
#define __UG_FONT_MANAGER_H__

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>

namespace UG
{
	//forward declarations
	class Font;
	
	//////////////////////////////////////////////////////////////////////////
	class FontManager
	{
	public:
		
		FontManager();
		~FontManager();
		
	public:
		void				DrawString(const char* pBuffer, glm::vec4 v4Position, unsigned int a_layer, glm::vec4 v4colour = glm::vec4(1.f, 1.f, 1.f,1.f));
		
		int					AddFont(const char* a_pFontName, unsigned short a_size);

		void                RemoveFont(const int& a_fontID);

		void				SetFont(const int& a_fontID);

	private:
		int FindFontIndex(Font* a_pFont);
		//This is a simple struct to allow us to easily have fonts that can be swapped in and out 
		//for rendering as the render for all characters is done in one long stream, with this we can 
		//break that stream up and allocate the appropriate font texture where required
		Font*					   m_pCurrentFont;
		std::vector< Font*>        m_Fonts;

	};

}//Namespace UG

#endif //__UG_FONT_MANAGER_H__

