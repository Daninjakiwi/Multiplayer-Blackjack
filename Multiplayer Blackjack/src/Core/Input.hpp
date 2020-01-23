#pragma once
#include <vector>
#include <unordered_map>
#include "GLFW/glfw3.h"
#include "Window.hpp"

namespace blackjack::core {
	enum class InputCode {
		A = 65, B = 66, C = 67, D = 68, E = 69,
		F = 70, G = 71, H = 72, I = 73, J = 74,
		K = 75, L = 76, M = 77, N = 78, O = 79,
		P = 80, Q = 81, R = 82, S = 83, T = 84,
		U = 85, V = 86, W = 87, X = 88, Y = 89,
		Z = 90, ENTER=257,TAB=258,
		MOUSE_LEFT = 1000, MOUSE_RIGHT = 1001
	};

	class Input {
	public:
		typedef void (*CallbackFunction)(unsigned int code);
	private:
		static std::unordered_map<InputCode, int> keys_;
		static std::vector<InputCode> mouse_buttons_;
		static int mouse_x_, mouse_y_;
		static CallbackFunction input_callback_;
	public:

		static void AttachWindow(Window* window);
		static bool KeyDown(InputCode code);
		static bool KeyJustPressed(InputCode code);
		static bool MouseDown(InputCode code);
		static int GetMouseX();
		static int GetMouseY();
		static void SetInputCallback(CallbackFunction function);
	private:
		static void KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void CharEvent(GLFWwindow* window, unsigned int codepoint);
		static void MouseMoveEvent(GLFWwindow* window, double xpos, double ypos);
		static void MouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
		static void ScrollEvent(GLFWwindow* window, double xoffset, double yoffset);
	};
}
