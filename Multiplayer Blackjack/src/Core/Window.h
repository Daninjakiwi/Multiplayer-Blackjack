#pragma once
#include <string>

#include "GLFW/glfw3.h"


namespace Blackjack::Core {

	class Window {
		friend class Input;
	private:
		static GLFWwindow* s_primary;
		static bool s_glfw_setup;
		static bool s_glad_setup;
		GLFWwindow* m_window;
	public:

		Window(unsigned int width, unsigned int height, const std::string& title);
		~Window();

		void makePrimary();
		void update();

		bool shouldClose();

		void show();
		void hide();
		void clear();

		void forceClose();

		void setSize(int width, int height);
	};
}
