#pragma once
#include "GLFW/glfw3.h"
#include <vector>
#include <unordered_map>
#include "Window.h"

namespace Blackjack::Core {
	enum INPUT_CODE {
		VOLT_A = 65, VOLT_B = 66, VOLT_C = 67, VOLT_D = 68, VOLT_E = 69,
		VOLT_F = 70, VOLT_G = 71, VOLT_H = 72, VOLT_I = 73, VOLT_J = 74,
		VOLT_K = 75, VOLT_L = 76, VOLT_M = 77, VOLT_N = 78, VOLT_O = 79,
		VOLT_P = 80, VOLT_Q = 81, VOLT_R = 82, VOLT_S = 83, VOLT_T = 84,
		VOLT_U = 85, VOLT_V = 86, VOLT_W = 87, VOLT_X = 88, VOLT_Y = 89,
		VOLT_Z = 90,
		VOLT_MOUSE_LEFT = 1000, VOLT_MOUSE_RIGHT = 1001
	};

	class Input {
	public:
		typedef void (*CallbackFunc)(unsigned int code);
	private:
		static std::unordered_map<INPUT_CODE, unsigned int> m_key;
		static std::vector<INPUT_CODE> m_mouse_keys;
		static int m_mouse_x, m_mouse_y;
		static bool m_mouse_moved;
		static CallbackFunc m_callback;
	public:

		static void attachWindow(Window* window);
		static bool keyDown(INPUT_CODE code);
		static bool keyJustPressed(INPUT_CODE code);
		static bool mouseDown(INPUT_CODE code);
		static bool mouseJustPressed(INPUT_CODE code);
		static int getMouseX();
		static int getMouseY();
		static bool mouseJustMoved();
		static void setInputCallback(CallbackFunc func);
	private:
		static void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void charEvent(GLFWwindow* window, unsigned int codepoint);
		static void mouseMoveEvent(GLFWwindow* window, double xpos, double ypos);
		static void mouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
		static void scrollEvent(GLFWwindow* window, double xoffset, double yoffset);
	};
}
