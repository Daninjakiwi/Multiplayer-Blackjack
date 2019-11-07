#include <iostream>
#include "glad/glad.h"

#include "Window.h"

namespace Blackjack {

	GLFWwindow* Window::s_primary = nullptr;
	bool Window::s_glfw_setup = false;
	bool Window::s_glad_setup = false;

	Window::Window(unsigned int width, unsigned int height, const std::string& title) : m_window(nullptr) {
		if (!s_glfw_setup) {
			if (glfwInit()) {
				s_glfw_setup = true;
			}
		}
		if (s_glfw_setup) {
			m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
			std::cout << "Create window: " << m_window << std::endl;
		}	
	}

	Window::~Window() {
		if (m_window == s_primary) {
			s_primary = nullptr;
		}
		glfwDestroyWindow(m_window);
	}

	void Window::makePrimary() {
		if (s_primary != m_window) {
			if (s_primary != nullptr) {
				glClear(GL_COLOR_BUFFER_BIT);
				glfwSwapBuffers(s_primary);
				glClear(GL_COLOR_BUFFER_BIT);
			}
			glfwMakeContextCurrent(m_window);
			s_primary = m_window;
		}
		if (!s_glad_setup) {
			if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				s_glad_setup = true;
			}
		}
	}

	void Window::update() {
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	bool Window::shouldClose() {
		return glfwWindowShouldClose(m_window);
	}

	void Window::show() {
		glfwShowWindow(m_window);
	}

	void Window::hide() {
		glfwHideWindow(m_window);
	}


	void Window::clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}



}