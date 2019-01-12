#include "Application.h"


#include <iostream>
#include "gl_core_4_4.h"

#include <GLFW/glfw3.h>

#include "UG_Assert.h"
#include "UG_Defines.h"

#include "TextureManager.h"
#include "FontManager.h"
#include "SpriteManager.h"
#include "Input.h"

#define BUILD_VERSION_MAJOR 1
#define BUILD_VERSION_MINOR 0
#define BULID_VERSION_REVISION 1

#define GLSL(src) "#version 330 core\n" #src

namespace UG
{
	//////////////////////////////////////////////////////////////////////////
	// Singleton Implementation of Font Manager Class
	//////////////////////////////////////////////////////////////////////////
	Application* Application::m_pInstance = nullptr;
	//////////////////////////////////////////////////////////////////////////
	Application* Application::CreateInstance()
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new Application();
		}
		return m_pInstance;
	}
	//////////////////////////////////////////////////////////////////////////
	Application* Application::GetInstance()
	{
		return m_pInstance;
	}
	//////////////////////////////////////////////////////////////////////////
	void Application::DestroyInstance()
	{
		delete m_pInstance;
	}

	Application::Application() : m_running(false) {}
	//////////////////////////////////////////////////////////////////////////////
	//Destructor for the Application
	//////////////////////////////////////////////////////////////////////////
	Application::~Application()
	{
		delete m_FontManager;
		m_SpriteManager->DestroyInstance();
		m_TextureManager->DestroyInstance();
		delete m_inputHandler;

		glDeleteShader(m_ShaderID);
		glfwTerminate();
	}

	bool Application::onCreate(int a_iWidth, int a_iHeight, bool a_bFullscreen /*= false*/, const char* a_pWindowTitle /*= nullptr*/, int a_xPosition /*= 0*/, int a_yPosition /*= 0*/)
	{
#pragma region CreateGLFWWindow
		// initialise glfw systems
		if (glfwInit() != GL_TRUE)
		{
			std::cout << "Unable to initialize GLFW" << std::endl;
			return false;
		}

		// create a windowed mode window and its OpenGL context
		glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
		GLFWmonitor* m_pMonitor = (a_bFullscreen) ? glfwGetPrimaryMonitor() : NULL;
		m_window = glfwCreateWindow(a_iWidth, a_iHeight, a_pWindowTitle, m_pMonitor, nullptr);
		if (m_window == nullptr)
		{
			std::cout << "Unable to create a GLFW Window" << std::endl;
			glfwTerminate();
			return false;
		}

		if (m_pMonitor != nullptr)
		{
			glfwSetWindowPos(m_window, a_xPosition, a_yPosition);
		}
		glfwShowWindow(m_window);

		std::cout << "UG Framework Version " << BUILD_VERSION_MAJOR << "." << BUILD_VERSION_MINOR << "." << BULID_VERSION_REVISION << std::endl;

		int major = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MAJOR);
		int minor = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MINOR);
		int revision = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_REVISION);
		std::cout << "OpenGL Version " << major << "." << minor << "." << revision << std::endl;

		// make the window's context current
		glfwMakeContextCurrent(m_window);

		if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
			glfwDestroyWindow(m_window);
			glfwTerminate();
			return false;
		}

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow*, int w, int h) 
		{ 
			glViewport(0, 0, w, h); 
			Application::GetInstance()->ResizeProjectionMatrix(w, h);
		});
		
#pragma endregion

		//Set up the camera, load and link default shaders and set up view space
		// setup camera and view matrices
		m_CameraMatrix = glm::mat4(1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 1.f, 1.f);
		int iScreenWidth = 0, iScreenHeight = 0;
		glfwGetWindowSize(m_window, &iScreenWidth, &iScreenHeight);
		m_ProjectionMatrix = glm::ortho(0.f, (float)iScreenWidth, 0.f, (float)iScreenHeight, 0.01f, 1000.f);
		m_ViewMatrix = glm::inverse(m_CameraMatrix);


		// load shaders
		
		char* vertexShader = GLSL(
			
			in vec4 position;
			in vec2 uv;
			uniform samplerBuffer data_tbo;
			uniform mat4 Projection;
			uniform mat4 View;
			out VERTEX	
			{
				vec2 UV;
				vec4 Color;
				float isFont;
			}vertex;

			void main()	
			{
				int texelLocation = gl_InstanceID * 7;
				vec4 xAxis = texelFetch(data_tbo, texelLocation);
				vec4 yAxis = texelFetch(data_tbo, texelLocation + 1);
				vec4 zAxis = texelFetch(data_tbo, texelLocation + 2);
				vec4 trans = texelFetch(data_tbo, texelLocation + 3);
				vertex.isFont = trans.w;
				trans.w = 1.0;
				mat4 m4Model = mat4(xAxis, yAxis, zAxis, trans);
				
				vec4 uvData = texelFetch(data_tbo, texelLocation + 4);
				vec4 color = texelFetch(data_tbo, texelLocation + 5);
				vec4 origin_scale = texelFetch(data_tbo, texelLocation + 6);
				
				vertex.UV = uv * uvData.zw + uvData.xy;
				vertex.Color = color;
				
				vec4 adjustedPos = ((position - vec4(origin_scale.x, origin_scale.y, 0.0, 0.0)) * vec4(origin_scale.z, origin_scale.w, 0.0, 1.0));
				gl_Position = Projection * View * m4Model * adjustedPos;
			}
		);

		char* fragmentShader = GLSL(
			in VERTEX
			{
				vec2 UV;
				vec4 Color;
				float isFont;
			}vertex;

			out vec4 outColour;

			uniform sampler2D diffuseTexture;
			void main()
			{
				vec4 texColor;
				if (vertex.isFont < 0.f)
					texColor = texture2D(diffuseTexture, vertex.UV).rrrr;
				else
					texColor = texture2D(diffuseTexture, vertex.UV);

				outColour = texColor * vertex.Color;
			}
		);


		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
		int success = GL_FALSE;
		char acLog[256];

		glShaderSource(vs, 1, (const char**)&vertexShader, 0);
		glCompileShader(vs);
		glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
		if(success != GL_TRUE)
		{
			glGetShaderInfoLog(vs, sizeof(acLog), 0, acLog);
			std::cout << "Error: Failed to compile vertex shader!" << std::endl;
			std::cout << acLog << std::endl;
		}

		glShaderSource(fs, 1, (const char**)&fragmentShader, 0);
		glCompileShader(fs);
		glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
		if (success != GL_TRUE)
		{
			glGetShaderInfoLog(fs, sizeof(acLog), 0, acLog);
			std::cout << "Error: Failed to compile fragment shader!" << std::endl;
			std::cout << acLog << std::endl;
		}

		m_ShaderID = glCreateProgram();
		glAttachShader(m_ShaderID, vs);
		glAttachShader(m_ShaderID, fs);
		glBindAttribLocation(m_ShaderID, 0, "position");
		glBindAttribLocation(m_ShaderID, 1, "uv");
		glLinkProgram(m_ShaderID);

		
		glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);
		if (success == GL_FALSE) {
			int infoLogLength = 0;
			glGetProgramiv(m_ShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
			char* infoLog = new char[infoLogLength];

			glGetProgramInfoLog(m_ShaderID, infoLogLength, 0, infoLog);
			printf("Error: Failed to link Sprite shader program!\n%s\n", infoLog);
			delete[] infoLog;
		}

		glUseProgram(m_ShaderID);

		// set matrix uniforms within the shaders
		GLint ProjectionID = glGetUniformLocation(m_ShaderID, "Projection");
		GLint ViewID = glGetUniformLocation(m_ShaderID, "View");

		glUniformMatrix4fv(ProjectionID, 1, false, glm::value_ptr(m_ProjectionMatrix));
		glUniformMatrix4fv(ViewID, 1, false, glm::value_ptr(m_ViewMatrix));

		// set the texture to use slot 0 in the shader
		GLuint texUniformID = glGetUniformLocation(m_ShaderID, "diffuseTexture");
		glUniform1i(texUniformID, 0);
		

		glUseProgram(0);

		glDeleteShader(vs);
		glDeleteShader(fs);		

		// set clear colour
		glClearColor(0.25f, 0.25f, 0.25f, 1);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// start our timer
		resetTimer();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		m_TextureManager = TextureManager::CreateInstance();
		m_SpriteManager = SpriteManager::CreateInstance();
		m_FontManager = new FontManager();

		m_inputHandler = new Input();

		m_running = true;
		return m_running;
	}

	void Application::ResizeProjectionMatrix(int a_w, int a_h)
	{
		m_ProjectionMatrix = glm::ortho(0.f, (float)a_w, 0.f, (float)a_h, 0.01f, 1000.f);
	}

	bool Application::process()
	{
		
		tickTimer();

		double mX; double mY;
		glfwGetCursorPos(GetWindow(), &mX, &mY);

		// convert camera's world matrix to a view matrix
		m_ViewMatrix = glm::inverse(m_CameraMatrix);
		//\=============================================================================
		//Draw lines
		// set active shader
		// set active shader
		glUseProgram(m_ShaderID);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(m_uSourceBlendMode, m_uDestinationBlendMode);
		// set matrix uniforms within the shaders
		GLint ProjectionID = glGetUniformLocation(m_ShaderID, "Projection");
		glUniformMatrix4fv(ProjectionID, 1, false, glm::value_ptr(m_ProjectionMatrix));
		
		// set current transforms in the shader
		GLuint ViewID = glGetUniformLocation(m_ShaderID, "View");
		glUniformMatrix4fv(ViewID, 1, false, glm::value_ptr(m_ViewMatrix));

		// set the texture to use slot 0 in the shader
		GLuint texUniformID = glGetUniformLocation(m_ShaderID, "diffuseTexture");
		glUniform1i(texUniformID, 0);

		//switch blending draw the font
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//draw any lines that we have in the scene
		//\=============================================================================
		//call to draw sprites
		SpriteManager::GetInstance()->Draw(m_ShaderID);

		//\=============================================================================
				
		// bring the back-buffer to the monitor
		glfwSwapBuffers(m_window);
		m_inputHandler->clearStatus();
		glfwPollEvents();

		
		return (m_running == true && glfwWindowShouldClose(m_window) == 0);
	}

	void Application::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void	Application::SetBackgroundColour(glm::vec4 a_backgrounColor)
	{
		glClearColor(a_backgrounColor.r, a_backgrounColor.g, a_backgrounColor.b, a_backgrounColor.a);
	}

	void Application::GetWindowSize( int& a_width,  int& a_height) const
	{
		glfwGetWindowSize(m_window, &a_width, &a_height);
	}

	void Application::SetWindowSize(const int& a_width, const int& a_height) 
	{
		glfwSetWindowSize(m_window, a_width, a_height);
	}
	
	void Application::resetTimer()
	{
		m_prevTime = glfwGetTime();
		m_totalTime = 0;
		m_deltaTime = 0;
	}

	float Application::tickTimer()
	{
		double currentTime = glfwGetTime();
		m_deltaTime = (float)(currentTime - m_prevTime);
		m_totalTime += m_deltaTime;
		m_prevTime = currentTime;
		return m_deltaTime;
	}

	float Application::getDeltaTime()
	{
		return m_deltaTime;
	}

	float Application::getTotalTime()
	{
		return m_totalTime;
	}
}//end namespace UG
