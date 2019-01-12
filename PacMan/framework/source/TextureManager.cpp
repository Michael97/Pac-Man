#include "TextureManager.h"
#include "Texture.h"

using namespace UG;


#pragma region Singleton Funtionality
///////////////////////////////////////////////////////////////
//Singleton functionality
///////////////////////////////////////////////////////////////
TextureManager* TextureManager::m_pInstance = nullptr;

TextureManager* TextureManager::CreateInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new TextureManager();
	}
	return m_pInstance;
}
///////////////////////////////////////////////////////////////
TextureManager* TextureManager::GetInstance()
{
	return m_pInstance;
}
///////////////////////////////////////////////////////////////
void TextureManager::DestroyInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
///////////////////////////////////////////////////////////////
#pragma endregion
///////////////////////////////////////////////////////////////

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	m_pTextureDictionary.clear();
}

///////////////////////////////////////////////////////////////
//Load Texture 
// - This uses an STD map as a texture atlas/dictionary to keep track of 
//   textures that are currently in memory and increments/decrements references 
//   as they are used or released
///////////////////////////////////////////////////////////////
Texture* TextureManager::LoadTexture(const char* a_pTextureName)
{
	Texture* pTexture = nullptr;
	if (a_pTextureName != nullptr)
	{
		std::map< std::string, TextureRef >::iterator dictionaryIter = m_pTextureDictionary.find(a_pTextureName);
		if (dictionaryIter != m_pTextureDictionary.end())
		{
			//We have found our Texture in the Dictionary return a reference to it and 
			//increment the reference count for the texture too
			TextureRef& texture = (TextureRef&)(dictionaryIter->second);
			pTexture = texture.pTexture;
			++texture.refCout;
		}
		else
		{
			//THis texture was not in memory so we best load it into memory
			pTexture = new Texture(a_pTextureName);
			TextureRef texRef = { pTexture, 1 };
			m_pTextureDictionary[a_pTextureName] = texRef;
		}
	}
	return pTexture;
}

Texture* TextureManager::CreateTexture(const char* a_pName, unsigned int a_width, unsigned int a_height, unsigned char* a_pixelData, unsigned int a_format)
{
	Texture* pTexture = nullptr;
	std::map< std::string, TextureRef >::iterator dictionaryIter = m_pTextureDictionary.find(a_pName);
	if (dictionaryIter != m_pTextureDictionary.end())
	{
		//We have found our Texture in the Dictionary return a reference to it and 
		//increment the reference count for the texture too
		TextureRef& texture = (TextureRef&)(dictionaryIter->second);
		pTexture = texture.pTexture;
		++texture.refCout;
	}
	else
	{
		//This texture was not in memory so we best create it into memory
		pTexture = new Texture(a_pName, a_width, a_height, (Texture::Format)(a_format), a_pixelData);
		TextureRef texRef = { pTexture, 1 };
		m_pTextureDictionary[a_pName] = texRef;
	}
	return pTexture;
}
///////////////////////////////////////////////////////////////
// Removes a texture from memory
// - internally just decrements a reference counter, when that
// gets to 0 it will unload it.
///////////////////////////////////////////////////////////////
void TextureManager::RemoveTexture(Texture* a_pTexture)
{
	std::map< std::string, TextureRef >::iterator dictionaryIter = m_pTextureDictionary.begin();
	for (; dictionaryIter != m_pTextureDictionary.end(); ++dictionaryIter)
	{
		
		TextureRef& texRef = (TextureRef&)(dictionaryIter->second);
		if (a_pTexture == texRef.pTexture)
		{
			--texRef.refCout;
			if (texRef.refCout <= 0)
			{
				delete texRef.pTexture;
				texRef.pTexture = nullptr;
				m_pTextureDictionary.erase(dictionaryIter);
				break;
			}
		}
	}
}


bool TextureManager::TextureExists(const char* a_pTextureName, Texture* a_texture) const
{
	auto dictionaryIter = m_pTextureDictionary.find(a_pTextureName);
	if (dictionaryIter != m_pTextureDictionary.end())
	{
		//We have found our Texture in the Dictionary return a reference to it and 
		//increment the reference count for the texture too
		TextureRef& texRef = (TextureRef&)(dictionaryIter->second);
		a_texture = texRef.pTexture;
		return true;
	}
	return false;
}
