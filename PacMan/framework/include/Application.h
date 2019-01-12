#pragma once

#ifndef __APPLICATION_H_
#define __APPLICATION_H_



#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>


struct GLFWwindow;

namespace UG {

	class TextureManager;
	class FontManager;
	class SpriteManager;
	class Input;

	class Application
	{
	protected:
		Application();
		virtual ~Application();
	public:
		static Application* CreateInstance();
		static Application* GetInstance();
		static void			DestroyInstance();

		
		
		bool	onCreate(int a_iWidth, int a_iHeight, bool a_bFullscreen = false, const char* a_pWindowTitle = nullptr, int a_xPosition = 0, int a_yPosition = 0);
		bool	process();
		void	destroy() { m_running = false; }

	
		GLFWwindow* GetWindow() { return m_window; }

		void GetWindowSize(  int& a_width,  int& a_height) const;
		void SetWindowSize(const int& a_width, const int& a_height);

		void	ClearScreen();
		void	SetBackgroundColour(glm::vec4 a_backgrounColor);
		void	GetCameraMatrix(glm::mat4& a_cameraMatrix)const { a_cameraMatrix = m_CameraMatrix; }
		void	ResizeProjectionMatrix(int a_w, int a_h);
		void	GetProjectionMatrix(glm::mat4& a_projectionMatrix)const { a_projectionMatrix = m_ProjectionMatrix; }
		void	GetViewMatrix(glm::mat4& a_viewMatrix) const { a_viewMatrix = m_ViewMatrix; }


		Input*	GetInputHandler() { return m_inputHandler; }
		FontManager* GetFontManager() { return m_FontManager; }
		

		// utilities for timing; Get() updates timers and returns time since last Get call
		void	resetTimer();
		
		float	getDeltaTime();
		float	getTotalTime();

	private:
		
		static Application* m_pInstance;
		//private function for calculating frame/delta time
		float			tickTimer();

		GLFWwindow*		m_window;
		bool			m_running;

		char			m_ApplicationTitle[256];

		TextureManager* m_TextureManager;
		SpriteManager*	m_SpriteManager;
		FontManager*	m_FontManager;
		Input*			m_inputHandler;

		//Variables for Shaders and camera matrices
		unsigned int	m_ShaderID;
		glm::mat4		m_ProjectionMatrix;
		glm::mat4		m_ViewMatrix;
		glm::mat4		m_CameraMatrix;

		//variable holding the time taken each frame
		double	m_prevTime = 0;
		float	m_totalTime = 0;
		float	m_deltaTime = 0;

	};


}//end namespace UG

#endif // __APPLICATION_H_