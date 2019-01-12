#pragma once

#ifndef __UG_INPUT_H__
#define __UG_INPUT_H__

#include <vector>
#include <map>

struct GLFWwindow;

namespace UG
{
	class Input 
	{
	public:
		
		Input();
		~Input();
		
		// should be called once by the application each frame after the current update
		// or before glfwPollEvents
		void clearStatus();

		// query the keyboard state
		bool isKeyDown(unsigned int inputKeyID);
		bool isKeyUp(unsigned int inputKeyID);

		// returns true if the key was pressed / released this frame
		bool wasKeyPressed(unsigned int inputKeyID);
		bool wasKeyReleased(unsigned int inputKeyID);

		// returns access to all keys that are currently pressed
		const std::vector<unsigned int>& getPressedKeys() const;
		
		// query the mouse button state
		bool isMouseButtonDown(unsigned int inputMouseID);
		bool isMouseButtonUp(unsigned int inputMouseID);

		// returns true if the button was pressed / released this frame
		bool wasMouseButtonPressed(unsigned int inputMouseID);
		bool wasMouseButtonReleased(unsigned int inputMouseID);

		// query the mouse position
		void getMousePos(int& x, int& y);

		// query how far the mouse wheel has been moved 
		double getMouseScroll();


	protected:

		
	private:

		enum EKeyStatus : unsigned int{
			RELEASED,
			UP,
			PRESSED,
			DOWN,
		};

		std::vector<unsigned int>			m_keysToUpdate;
		std::map<unsigned int, unsigned int>			m_keyStatus;

		std::vector<unsigned int>			m_pressedKeys;
		
		std::vector<unsigned int>			m_mouseToUpdate;
		std::map<unsigned int, unsigned int>			m_mouseState;

		int		m_mouseX;
		int		m_mouseY;
		double	m_mouseScroll;

		// These methods are called by glfw function pointers
		// The function pointers are called during the GLFWPollEvents function
		// which is called at the end of the game loop after SwapBuffers
		void onKeyPressed(unsigned  int keyID);
		void onKeyReleased(unsigned  int keyID);
		void onKeyRepeated(unsigned  int key);

		void onMouseMove(int newXPos, int newYPos);

		void onMousePressed(unsigned  int mouseButtonID);
		void onMouseReleased(unsigned  int mouseButtonID);

	};
}//namespace UG

#endif //__UG_INPUT_H__
