//////////////////////////////////////////////////////////////////////////
//	Author:	Jamie Stewart
//	Date:	08/05/2017
//	Brief:	The font manager - it is in charge of handling fonts
//          Multiple fonts can be utilised to display different information
//          to the screen
//////////////////////////////////////////////////////////////////////////
#include "FontManager.h"
#include "Font.h"
#include <assert.h>
#include <stb_truetype.h>

using namespace UG;

//////////////////////////////////////////////////////////////////////////
// Create and initialise the font manager and set up the Vertex and index buffrers that will be drawn to
///////////////////////////////////////////////////////////////////////////
FontManager::FontManager() :m_pCurrentFont(nullptr)
{
	
}

//////////////////////////////////////////////////////////////////////////
FontManager::~FontManager()
{
	
}

///////////////////////////////////////////////////////////////////////////
// DrawString - this function is called via a framework accessor to create a new
//      character string to draw this frame, it pushes chars into the draw queue
//////////////////////////////////////////////////////////////////////////
void FontManager::DrawString(const char* pBuffer, glm::vec4 v4Position, unsigned int a_layer, glm::vec4 v4colour)
{
	if (m_pCurrentFont != nullptr)
	{
		m_pCurrentFont->DrawString(pBuffer, v4Position, a_layer, v4colour);
	}
}

//////////////////////////////////////////////////////////////////////////
// Finds an index for the font 
//////////////////////////////////////////////////////////////////////////

int FontManager::FindFontIndex(Font* a_pFont)
{
	if (m_Fonts.size() > 0)
	{
		auto _iter = m_Fonts.begin();
		for (unsigned int i = 0; _iter != m_Fonts.end(); ++_iter, ++i)
		{
			if ((*_iter) == a_pFont)
			{
				return i;
			}
		}
	}
	return -1;
}
///////////////////////////////////////////////////////////////////////////
// adds a new font to the font manager
//////////////////////////////////////////////////////////////////////////
int FontManager::AddFont(const char* pFontName, unsigned short a_size)
{
	Font* pFont = new Font(pFontName, a_size);

	int index = FindFontIndex(nullptr);
	if (index != -1)
	{
		m_Fonts[index] = pFont;
	}
	else
	{
		m_Fonts.push_back(pFont);
		index = ((int)m_Fonts.size() - 1);
	}
	return index;
}
//////////////////////////////////////////////////////////////////////////
// if we dont need the font then we better remove it. 
//////////////////////////////////////////////////////////////////////////
void FontManager::RemoveFont(const int& a_fontID)
{
	Font* pFont = m_Fonts[a_fontID];
	if (pFont != nullptr)
	{
		if (pFont == m_pCurrentFont)
		{
			m_pCurrentFont = nullptr;
		}
		delete pFont;
		m_Fonts[a_fontID] = pFont = nullptr;
	}
}
///////////////////////////////////////////////////////////////////////////
// SetFont() - sets the currect font if there is not a font available it will use the 
// debug font
//////////////////////////////////////////////////////////////////////////
void FontManager::SetFont(const int& a_fontID)
{
	Font* pFont = m_Fonts[a_fontID];
	if (pFont != nullptr)
	{
		m_pCurrentFont = pFont;
	}
}


