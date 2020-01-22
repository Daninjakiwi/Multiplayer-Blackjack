#include <iostream>
#include "Input.hpp"

namespace blackjack::core {
	std::vector<InputCode> Input::mouse_buttons_;
	std::unordered_map<InputCode, int> Input::keys_;
	int Input::mouse_x_, Input::mouse_y_;
	Input::CallbackFunction Input::input_callback_ = nullptr;

	void Input::AttachWindow(Window* window) {
		glfwSetKeyCallback(window->window_, KeyEvent);
		glfwSetCharCallback(window->window_, CharEvent);
		glfwSetCursorPosCallback(window->window_, MouseMoveEvent);
		glfwSetMouseButtonCallback(window->window_, MouseButtonEvent);
		glfwSetScrollCallback(window->window_, ScrollEvent);
	}

	bool Input::KeyDown(InputCode code) {
		if (keys_.find(code) != keys_.end()) {
			return true;
		}
		return false;
	}

	bool Input::KeyJustPressed(InputCode code) {
		auto test = keys_.find(code);
		if (test != keys_.end()) {
			if (test->second == 0) {
				test->second += 1;
				return true;
			}
		}
		return false;
	}

	bool Input::MouseDown(InputCode code) {
		for (int i = 0; i < mouse_buttons_.size(); i++) {
			if (mouse_buttons_[i] == code) {
				keys_[code] += 1;
				return true;
			}
		}
		return false;
	}

	int Input::GetMouseX() {
		return mouse_x_;
	}

	int Input::GetMouseY() {
		return mouse_y_;
	}

	void Input::SetInputCallback(CallbackFunction function) {
		input_callback_ = function;
	}


	void Input::KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (scancode == 14) {
			CharEvent(window, scancode);
		}
		else {
			if (action == GLFW_PRESS) {
				keys_[(InputCode)key] = 0;
				return;
			}
			else if (action == GLFW_REPEAT) {
				auto test = keys_.find((InputCode)key);
				test->second += 1;
			}
			else if (action == GLFW_RELEASE) {
				auto test = keys_.find((InputCode)key);
				keys_.erase(test->first);
			}
		}
	}

	void Input::CharEvent(GLFWwindow* window, unsigned int codepoint) {
		if (input_callback_ != nullptr) {
			input_callback_(codepoint);
		}

	}

	void Input::MouseMoveEvent(GLFWwindow* window, double xpos, double ypos) {
		mouse_x_ = xpos;
		mouse_y_ = ypos;
	}

	void Input::MouseButtonEvent(GLFWwindow* window, int button, int action, int mods) {
		InputCode code = (InputCode)(button + 1000);
		if (action == GLFW_PRESS) {
			mouse_buttons_.push_back(code);
			keys_[code] = 0;
			return;
		}
		else if (action == GLFW_RELEASE) {
			for (int i = 0; i < mouse_buttons_.size(); i++) {
				if (mouse_buttons_[i] == code) {
					mouse_buttons_.erase(mouse_buttons_.begin() + i);
					auto test = keys_.find(code);
					keys_.erase(test->first);
					return;
				}
			}
		}
	}

	void Input::ScrollEvent(GLFWwindow* window, double xoffset, double yoffset) {
	}
}