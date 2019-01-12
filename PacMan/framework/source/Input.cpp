
#include "Input.h"
#include <GLFW/glfw3.h>
#include "Application.h"


using namespace UG;

Input::Input() 
{
	for (unsigned int i = 0; i < GLFW_KEY_LAST; ++i)
	{
		m_keyStatus[i] = UP;
	}

	for (unsigned int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i)
	{
		m_mouseState[i] = UP;
	}

	auto KeyPressCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Application* app = Application::GetInstance();
		Input* inputHandler = app->GetInputHandler();
		switch (action)
		{
		case(GLFW_PRESS):
			inputHandler->onKeyPressed((unsigned int)key);
			break;
		case(GLFW_RELEASE):
			inputHandler->onKeyReleased((unsigned int)key);
			break;
		case(GLFW_REPEAT):
			inputHandler->onKeyRepeated((unsigned int)key);
			break;
		default:
			break;
		}
	};

	auto MouseMoveCallback = [](GLFWwindow* window, double x, double y) 
	{
		int w = 0, h = 0;
		glfwGetWindowSize(window, &w, &h);
		Application* app = Application::GetInstance();
		Input* inputHandler = app->GetInputHandler();

		inputHandler->onMouseMove((int)x, h - (int)y);

	};

	auto MouseInputCallback = [](GLFWwindow* window, int button, int action, int mods)
	{

		Application* app = Application::GetInstance();
		Input* inputHandler = app->GetInputHandler();

		switch (action)
		{
		case(GLFW_PRESS):
			inputHandler->onMousePressed((unsigned int)button);
			break;
		case(GLFW_RELEASE):
			inputHandler->onMouseReleased((unsigned int)button);
			break;
		default:
			break;
		}

		
	};

	auto MouseScrollCallback = [](GLFWwindow* window, double xoffset, double yoffset)
	{

		Application* app = Application::GetInstance();
		Input* inputHandler = app->GetInputHandler();

		inputHandler->m_mouseScroll += yoffset;

	};

	GLFWwindow* window = glfwGetCurrentContext();
	//Set GLFW Callback functions to those created above
	glfwSetKeyCallback(window, KeyPressCallback);
	glfwSetMouseButtonCallback(window, MouseInputCallback);
	glfwSetCursorPosCallback(window, MouseMoveCallback);
	glfwSetScrollCallback(window, MouseScrollCallback);

	m_mouseX = 0;
	m_mouseY = 0;
	m_mouseScroll = 0;
}

Input::~Input() 
{

}

void Input::onKeyPressed(unsigned int keyID)
{
	m_keyStatus[keyID] = PRESSED;
	m_keysToUpdate.push_back(keyID);
	m_pressedKeys.push_back(keyID);
}

void Input::onKeyReleased(unsigned int keyID)
{
	m_keyStatus[keyID] = RELEASED;
	m_keysToUpdate.push_back(keyID);
}

void Input::onKeyRepeated(unsigned int key)
{
	m_pressedKeys.push_back(key);
}

void Input::onMouseMove(int newXPos, int newYPos) 
{
	m_mouseX = newXPos;
	m_mouseY = newYPos;
}

void Input::onMousePressed(unsigned int mouseButtonID)
{
	m_mouseState[mouseButtonID] = PRESSED;
	m_mouseToUpdate.push_back(mouseButtonID);
}

void Input::onMouseReleased(unsigned int mouseButtonID)
{
	m_mouseState[mouseButtonID] = RELEASED;
	m_mouseToUpdate.push_back(mouseButtonID);
}

void Input::clearStatus() 
{
	for (auto& key : m_keysToUpdate)
		m_keyStatus[key] += 1;

	for (auto& state : m_mouseToUpdate)
		m_mouseState[state] += 1;

	m_mouseToUpdate.clear();
	m_keysToUpdate.clear();

	m_pressedKeys.clear();
}

bool Input::isKeyDown(unsigned int inputKeyID)
{
	return m_keyStatus[inputKeyID] == PRESSED || m_keyStatus[inputKeyID] == DOWN;
}

bool Input::isKeyUp(unsigned int inputKeyID)
{
	return m_keyStatus[inputKeyID] == RELEASED || m_keyStatus[inputKeyID] == UP;
}

bool Input::wasKeyPressed(unsigned int inputKeyID)
{
	return m_keyStatus[inputKeyID] == PRESSED;
}

bool Input::wasKeyReleased(unsigned int inputKeyID)
{
	return m_keyStatus[inputKeyID] == RELEASED;
}

const std::vector<unsigned int> &Input::getPressedKeys() const
{
	return m_pressedKeys;
}

bool Input::isMouseButtonDown(unsigned int inputMouseID)
{
	return m_mouseState[inputMouseID] == DOWN;
}

bool Input::isMouseButtonUp(unsigned int inputMouseID)
{
	return m_mouseState[inputMouseID] == UP || m_mouseState[inputMouseID] == RELEASED;
}

bool Input::wasMouseButtonPressed(unsigned int inputMouseID)
{
	return m_mouseState[inputMouseID] == PRESSED;
}

bool Input::wasMouseButtonReleased(unsigned int inputMouseID)
{
	return m_mouseState[inputMouseID] == RELEASED;
}

double Input::getMouseScroll() 
{
	return m_mouseScroll;
}

void Input::getMousePos(int& x, int& y)
{
	x = m_mouseX;
	y = m_mouseY;
}