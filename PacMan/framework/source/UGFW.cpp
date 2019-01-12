#include "UGFW.h"
#include "Application.h"
#include "SpriteManager.h"
#include "FontManager.h"
#include "TextureManager.h"
#include "Input.h"


////////////////////////////////////////////////////////////////
int	UG::Create(int a_iWidth, int a_iHeight, bool a_bFullscreen /*= false*/, const char* a_pWindowTitle /*= nullptr*/, int a_xPosition /*= 0*/, int a_yPosition /*= 0*/)
{
	Application* pApp = Application::CreateInstance();
	if (pApp  != nullptr)
	{
		pApp->onCreate(a_iWidth, a_iHeight, a_bFullscreen, a_pWindowTitle, a_xPosition, a_yPosition);
		return 1;
	}
	return 0;
}
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void UG::Dispose()
{
	if (Application::GetInstance())
	{
		Application::DestroyInstance();
	}
}
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
bool UG::Process()
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		return pApp->process();
	}
	return false;
}

void UG::Close()
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		pApp->destroy();
	}
}

//////////////////////////////////////////////////////////////////////////
//Gets the screen size of the default window
//////////////////////////////////////////////////////////////////////////
void UG::GetScreenSize(int& a_iWidth, int& a_iHeight)
{
	Application* pApp = Application::GetInstance();
	pApp->GetWindowSize(a_iWidth, a_iHeight);
}

void UG::SetScreenSize(const int& a_iWidth, const int& a_iHeight)
{
	Application* pApp = Application::GetInstance();
	pApp->SetWindowSize(a_iWidth, a_iHeight);
}
//////////////////////////////////////////////////////////////////////////
// Does what it says on the tin clears the render buffer or screen
//////////////////////////////////////////////////////////////////////////
void UG::ClearScreen()
{
	Application* pApp = Application::GetInstance();
	pApp->ClearScreen();
	
}
//////////////////////////////////////////////////////////////////////////////
// Changes the background colour of the render window
//////////////////////////////////////////////////////////////////////////////
void UG::SetBackgroundColor(SColour a_bgColor)
{
	glm::vec4 bgColor = glm::vec4(a_bgColor.rgba.colours.r / 255.f,
		a_bgColor.rgba.colours.g / 255.f,
		a_bgColor.rgba.colours.b / 255.f,
		a_bgColor.rgba.colours.a / 255.f);

	Application* pApp = Application::GetInstance();
	pApp->SetBackgroundColour(bgColor);
	
}

#pragma region Sprite creation and mainpulation functionality
//////////////////////////////////////////////////////////////////////////
// Sprite creation, copy and destruction
//////////////////////////////////////////////////////////////////////////
int UG::CreateSprite(const char* a_pTextureName, float a_fWidth, float a_fHeight, bool a_bDrawFromCenter, SColour a_sColour /* = SColour( 0xFF, 0xFF, 0xFF, 0xFF )*/)
{
	glm::vec2 v2Size = glm::vec2(a_fWidth, a_fHeight);
	glm::vec2 v2Origin = a_bDrawFromCenter ? glm::vec2(0.5f, 0.5f) : glm::vec2(0.f, 1.f);
	glm::vec4 uvCoords = glm::vec4(0.f, 0.f, 1.f, 1.f);
	return CreateSprite(a_pTextureName, glm::value_ptr(v2Size), glm::value_ptr(v2Origin), glm::value_ptr(uvCoords), a_sColour);
}

int UG::CreateSprite(const char* a_pTextureName, const float* a_fv2Size, const float* a_fv2Origin, const float* a_fv4UVCoords /*= nullptr*/, SColour a_sColour)
{
	//Set up the UV Coordinates
	glm::vec4 v4UVCoords = (a_fv4UVCoords) ?
		glm::vec4(a_fv4UVCoords[0], a_fv4UVCoords[1], a_fv4UVCoords[2], a_fv4UVCoords[3]) :
		glm::vec4(0.f, 0.f, 1.f, 1.f);
	//Set up the colour
	glm::vec4 v4Color = glm::vec4(a_sColour.rgba.colours.r / 255.f,
		a_sColour.rgba.colours.g / 255.f,
		a_sColour.rgba.colours.b / 255.f,
		a_sColour.rgba.colours.a / 255.f);
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		glm::vec2 v2Size = glm::vec2(a_fv2Size[0], a_fv2Size[1]);
		glm::vec2 v2Origin = glm::vec2(a_fv2Origin[0], a_fv2Origin[1]);
		return pSpriteManager->AddSprite(a_pTextureName, v2Size, v2Origin, v4UVCoords, v4Color);
	}
	return 0;
}

int UG::DuplicateSprite(int a_uiSpriteID)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		return pSpriteManager->DuplicateSprite(a_uiSpriteID);
	}
	return 0;
}

void UG::DestroySprite(int a_uiSpriteID)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		pSpriteManager->RemoveSprite(a_uiSpriteID);
	}
}
//////////////////////////////////////////////////////////////////////////
//Drawing
//////////////////////////////////////////////////////////////////////////
void UG::DrawSprite(int a_uiSpriteID)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		pSpriteManager->MarkSpriteForDraw(a_uiSpriteID);
	}
}

//////////////////////////////////////////////////////////////////////////
/// Sprite Layer Setters and Getter
//////////////////////////////////////////////////////////////////////////
void UG::SetSpriteLayer(int a_iSpriteID, const unsigned int& a_uiLayer)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_iSpriteID);
		pSprite->SetLayer(a_uiLayer);
	}
}
//////////////////////////////////////////////////////////////////////////
void UG::GetSpriteLayer(int a_iSpriteID, unsigned int& a_uiLayer)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_iSpriteID);
		a_uiLayer = pSprite->GetLayer();
	}
}
//////////////////////////////////////////////////////////////////////////
//Movement, Rotation and Scale
//////////////////////////////////////////////////////////////////////////
void UG::SetSpritePosition(int a_uiSpriteID, float a_fXPos, float a_fYPos)
{
	glm::vec2 v2Pos = glm::vec2(a_fXPos, a_fYPos);
	SetSpritePosition(a_uiSpriteID, glm::value_ptr(v2Pos));
}

void UG::SetSpritePosition(int a_uiSpriteID, const float* a_vFloatVec)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		float fLayer = (float)(pSprite->GetLayer());
		glm::vec4 pos = glm::vec4(a_vFloatVec[0], a_vFloatVec[1], fLayer, 1.f);
		pSprite->SetPosition(pos);
	}
}

void UG::GetSpritePosition(int a_uiSpriteID, float& a_xPos, float& a_YPos)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		glm::vec4 v4Pos;
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		pSprite->GetPosition(v4Pos);
		a_xPos = v4Pos.x; a_YPos = v4Pos.y;
	}
}

void UG::SetSpriteMatrix(int a_uiSpriteID, const float* a_fm4)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		glm::mat4 m4;
		memcpy(glm::value_ptr(m4), a_fm4, sizeof(float) * 16);
		pSprite->SetMatrix(m4);
	}
}

void UG::GetSpriteMatrix(int a_uiSpriteID, float* a_fm4)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		glm::mat4 m4;
		pSprite->GetMatrix(m4);
		a_fm4 = glm::value_ptr(m4);
	}
}

void UG::SetSpriteRotation(int a_uiSpriteID, float a_fRotation)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);

		glm::mat4 m4 = glm::mat4(1.f, 0.f, 0.f, 0.f,
								 0.f, 1.f, 0.f, 0.f,
								 0.f, 0.f, 1.f, 0.f,
								 0.f, 0.f, 0.f, 1.f);
		glm::vec4 pos;
		pSprite->GetPosition(pos);
		pSprite->SetMatrix(m4);
		pSprite->SetPosition(pos);

		pSprite->setRotation(a_fRotation);
	}
}

void UG::RotateSprite(int a_uiSpriteID, float a_fRotation)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		pSprite->setRotation(a_fRotation);
	}
}

void UG::SetSpriteScale(int a_uiSpriteID, const float& a_fSpriteWidth, const float& a_fSpriteHeight)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		pSprite->SetSize(a_fSpriteWidth, a_fSpriteHeight);
	}
}

void UG::GetSpriteScale(int a_uiSpriteID, float& a_fSpriteWidth, float& a_fSpriteHeight)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		pSprite->GetSize(a_fSpriteWidth, a_fSpriteHeight);

	}
}
//////////////////////////////////////////////////////////////////////////
//UV Coordinates
//////////////////////////////////////////////////////////////////////////
void UG::SetSpriteUVCoordinates(int a_uiSpriteID, float a_minUCoord, float a_minVCoord, float a_maxUCoord, float a_maxVCoord)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		glm::vec2 minUV(a_minUCoord, a_minVCoord);
		glm::vec2 maxUV(a_maxUCoord, a_maxVCoord);
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		pSprite->SetUVCoords(minUV, maxUV);
	}
}

void UG::SetSpriteUVCoordinates(int a_uiSpriteID, const float* a_fUVVec4)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		glm::vec2 minUV(a_fUVVec4[0], a_fUVVec4[1]);
		glm::vec2 maxUV(a_fUVVec4[2], a_fUVVec4[3]);
		pSprite->SetUVCoords(minUV, maxUV);
	}
}

void UG::GetSpriteUVCoordinates(int a_uiSpriteID, float& a_minUCoord, float& a_minVCoord, float& a_maxUCoord, float& a_maxVCoord)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		glm::vec2 minUVCoord;
		glm::vec2 maxUVCoord;
		pSprite->GetUVCoords(minUVCoord, maxUVCoord);

		a_minUCoord = minUVCoord.x; a_minVCoord = minUVCoord.y;
		a_maxUCoord = maxUVCoord.x; a_maxVCoord = maxUVCoord.y;
	}
}

void UG::GetSpriteUVCoordinates(int a_uiSpriteID, float* a_fUVVec4)
{
	glm::vec4 v4SpriteCoordinates = glm::vec4(0.f, 0.f, 0.f, 0.f);
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		glm::vec2 minUVCoord;
		glm::vec2 maxUVCoord;
		pSprite->GetUVCoords(minUVCoord, maxUVCoord);

		v4SpriteCoordinates.x = minUVCoord.x; v4SpriteCoordinates.y = minUVCoord.y;
		v4SpriteCoordinates.z = maxUVCoord.x; v4SpriteCoordinates.w = maxUVCoord.y;
	}
	a_fUVVec4 = glm::value_ptr(v4SpriteCoordinates);
}
//////////////////////////////////////////////////////////////////////////
//Color
//////////////////////////////////////////////////////////////////////////
void UG::SetSpriteColour(int a_uiSpriteID, const SColour& a_sColour)
{
	glm::vec4 v4colour = glm::vec4(a_sColour.rgba.colours.r / 255.f, a_sColour.rgba.colours.g / 255.f, a_sColour.rgba.colours.b / 255.f, a_sColour.rgba.colours.a / 255.f);
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		pSprite->SetColour(v4colour);
	}
}
void UG::GetSpriteColour(int a_uiSpriteID, SColour& a_sColour)
{
	glm::vec4 v4colour;
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		pSprite->GetColour(v4colour);
	}
	a_sColour.rgba.colours.r = (char)(255.f * v4colour.x);
	a_sColour.rgba.colours.g = (char)(255.f * v4colour.y);
	a_sColour.rgba.colours.b = (char)(255.f * v4colour.z);
	a_sColour.rgba.colours.a = (char)(255.f * v4colour.w);
}

//////////////////////////////////////////////////////////////////////////
//Blend mode settings
//////////////////////////////////////////////////////////////////////////
void UG::SetSpriteBlendMode(int a_uiSpriteID, const unsigned int& a_uiSourceFactor, const unsigned int& a_uiDestinationFactor)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		pSprite->SetBlendParameters(a_uiSourceFactor, a_uiDestinationFactor);
	}
}

void UG::GetSpriteBlendMode(int a_uiSpriteID, unsigned int& a_uiSourceFactor, unsigned int& a_uiDestinationFactor)
{
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		Sprite* pSprite = pSpriteManager->GetSprite(a_uiSpriteID);
		pSprite->GetBlendParameters(a_uiSourceFactor, a_uiDestinationFactor);
	}
}
#pragma endregion
#pragma region DrawString Functionality
/// @name Text Rendering
/**@{**/
//////////////////////////////////////////////////////////////////////////
void UG::DrawString(const char* a_pText, int a_iXPos, int a_iYPos, unsigned int a_layer, SColour a_sColour /*= SColour(0xFF,0xFF,0xFF,0xFF)*/)
{
	glm::vec4 v4Position = glm::vec4((float)a_iXPos, (float)a_iYPos, 0.f, 1.f);
	glm::vec4 v4Colour = glm::vec4(a_sColour.rgba.colours.r / 255.f, a_sColour.rgba.colours.g / 255.f, a_sColour.rgba.colours.b / 255.f, a_sColour.rgba.colours.a / 255.f);

	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		FontManager* fm = pApp->GetFontManager();
		fm->DrawString(a_pText,v4Position, a_layer,v4Colour);
	}
}
/**@}**/

int UG::AddFont(const char* a_pFontName, unsigned short a_size)
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		FontManager* fm = pApp->GetFontManager();
		return fm->AddFont(a_pFontName, a_size);
	}
	return -1;
}

void UG::SetFont(const int& a_fontID)
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		FontManager* fm = pApp->GetFontManager();
		fm->SetFont(a_fontID);
	}
}

void UG::RemoveFont(const int& a_fontID)
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		FontManager* fm = pApp->GetFontManager();
		fm->RemoveFont(a_fontID);
	}
}

#pragma endregion

#pragma region Line Drawring Functionality
////////////////////////////////////////////////////////////////////////////
///// @name Basic Line Drawing Functionality
////////////////////////////////////////////////////////////////////////////
///**@{**/

////////////////////////////////////////////////////////////////////////////
void UG::DrawLine(float a_iStartX, float a_iStartY, float a_iEndX, float a_iEndY, float a_thickness, unsigned int a_layer, SColour a_Colour)
{
	float xDiff = a_iEndX - a_iStartX;
	float yDiff = a_iEndY - a_iStartY;
	float len = glm::sqrt(xDiff * xDiff + yDiff * yDiff);
	float xDir = xDiff / len;
	float yDir = yDiff / len;

	float rot = glm::atan(yDir, xDir) * 57.295779513f;
	
	SpriteManager* pSpriteManager = SpriteManager::GetInstance();
	if (pSpriteManager)
	{
		int spriteID = pSpriteManager->GetLineSpriteID();
		SetSpritePosition(spriteID, a_iStartX, a_iStartY);
		SetSpriteScale(spriteID, len, a_thickness);
		SetSpriteColour(spriteID, a_Colour);
		SetSpriteRotation(spriteID, rot);
		SetSpriteLayer(spriteID, a_layer);
		DrawSprite(spriteID);
	}

}
///**@}**/
#pragma endregion
#pragma region Input handling functionality
//////////////////////////////////////////////////////////////////////////
/// @name Input handling functionality
//////////////////////////////////////////////////////////////////////////
/**@{**/

////////////////////////////////////////////////////////////////////////
bool UG::IsKeyDown(unsigned int a_uiKey)
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		Input* ih = pApp->GetInputHandler();
		return ih->isKeyDown(a_uiKey);
	}
	return false;
}

bool UG::IsKeyUp(unsigned int a_uiKey)
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		Input* ih = pApp->GetInputHandler();
		return ih->isKeyUp(a_uiKey);
	}
	return false;
}

bool UG::WasKeyReleased(unsigned int a_uiKey)
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		Input* ih = pApp->GetInputHandler();
		return ih->wasKeyReleased(a_uiKey);
	}
	return false;
}

bool UG::WasKeyPressed(unsigned int a_uiKey)
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		Input* ih = pApp->GetInputHandler();
		return ih->wasKeyPressed(a_uiKey);
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
void UG::GetMousePos( int& a_uiMousePosX, int& a_uiMousePosY)
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		Input* ih = pApp->GetInputHandler();
		ih->getMousePos(a_uiMousePosX, a_uiMousePosY);
	}

}

bool UG::IsMouseButtonDown(int a_uiMouseButton)
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		Input* ih = pApp->GetInputHandler();
		return ih->isMouseButtonDown(a_uiMouseButton);
	}
	return false;
}

bool UG::IsMouseButtonUp(int a_uiMouseButton)
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		Input* ih = pApp->GetInputHandler();
		return ih->isMouseButtonUp(a_uiMouseButton);
	}
	return false;
}

bool UG::WasMouseButtonReleased(int a_uiMouseButton)
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		Input* ih = pApp->GetInputHandler();
		return ih->wasMouseButtonReleased(a_uiMouseButton);
	}
	return false;
}

bool UG::WasMouseButtonPressed(int a_uiMouseButton)
{
	Application* pApp = Application::GetInstance();
	if (pApp != nullptr)
	{
		Input* ih = pApp->GetInputHandler();
		return ih->wasMouseButtonPressed(a_uiMouseButton);
	}
	return false;
}
/**@}**/
#pragma endregion
float UG::GetDeltaTime()
{
	return Application::GetInstance()->getDeltaTime();
}