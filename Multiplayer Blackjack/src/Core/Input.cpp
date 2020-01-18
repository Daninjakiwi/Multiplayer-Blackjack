#include "Input.h"

namespace Blackjack::Core {
	std::vector<INPUT_CODE> Input::m_mouse_keys;
	std::unordered_map<INPUT_CODE, unsigned int> Input::m_key;
	int Input::m_mouse_x, Input::m_mouse_y;
	bool Input::m_mouse_moved = false;

	void Input::attachWindow(Window* window) {
		glfwSetKeyCallback(window->m_window, keyEvent);
		glfwSetCharCallback(window->m_window, charEvent);
		glfwSetCursorPosCallback(window->m_window, mouseMoveEvent);
		glfwSetMouseButtonCallback(window->m_window, mouseButtonEvent);
		glfwSetScrollCallback(window->m_window, scrollEvent);
	}

	bool Input::keyDown(INPUT_CODE code) {
		if (m_key.find(code) != m_key.end()) {
			return true;
		}
		return false;
	}

	bool Input::keyJustPressed(INPUT_CODE code) {
		auto test = m_key.find(code);
		if (test != m_key.end()) {
			if (test->second == 0) {
				test->second += 1;
				return true;
			}
		}
		return false;
	}

	bool Input::mouseDown(INPUT_CODE code) {
		for (int i = 0; i < m_mouse_keys.size(); i++) {
			if (m_mouse_keys[i] == code) {
				m_key[code] += 1;
				return true;
			}
		}
		return false;
		return 0;
	}

	bool Input::mouseJustPressed(INPUT_CODE code) {
		auto test = m_key.find(code);
		if (test != m_key.end()) {
			if (test->second == 0) {
				test->second += 1;
				return true;
			}
		}
		return false;
	}

	int Input::getMouseX() {
		m_mouse_moved = false;
		return m_mouse_x;
	}

	int Input::getMouseY() {
		m_mouse_moved = false;
		return m_mouse_y;
	}

	bool Input::mouseJustMoved() {
		return m_mouse_moved;
	}


	void Input::keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS) {
			m_key[(INPUT_CODE)key] = 0;
			return;
		}
		else if (action == GLFW_REPEAT) {
			auto test = m_key.find((INPUT_CODE)key);
			test->second += 1;
		}
		else if (action == GLFW_RELEASE) {
			auto test = m_key.find((INPUT_CODE)key);
			m_key.erase(test->first);
		}
	}

	void Input::charEvent(GLFWwindow* window, unsigned int codepoint) {
	}

	void Input::mouseMoveEvent(GLFWwindow* window, double xpos, double ypos) {
		m_mouse_x = xpos;
		m_mouse_y = ypos;
		m_mouse_moved = true;
	}

	void Input::mouseButtonEvent(GLFWwindow* window, int button, int action, int mods) {
		INPUT_CODE code = (INPUT_CODE)(button + 1000);
		if (action == GLFW_PRESS) {
			m_mouse_keys.push_back(code);
			m_key[code] = 0;
			return;
		}
		else if (action == GLFW_RELEASE) {
			for (int i = 0; i < m_mouse_keys.size(); i++) {
				if (m_mouse_keys[i] == code) {
					m_mouse_keys.erase(m_mouse_keys.begin() + i);
					auto test = m_key.find(code);
					m_key.erase(test->first);
					return;
				}
			}
		}
	}

	void Input::scrollEvent(GLFWwindow* window, double xoffset, double yoffset) {
	}
}