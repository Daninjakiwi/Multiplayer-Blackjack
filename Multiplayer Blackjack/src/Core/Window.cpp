#include <iostream>
#include "glad/glad.h"

#include "Window.h"
#include "ResourceManager.h"

namespace Blackjack::Core {

	GLFWwindow* Window::s_primary = nullptr;
	bool Window::s_glfw_setup = false;
	bool Window::s_glad_setup = false;

	Window::Window(unsigned int width, unsigned int height, const std::string& title) : m_window(nullptr) {
		if (!s_glfw_setup) {
			if (glfwInit()) {
				s_glfw_setup = true;
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				//glfwWindowHint(GLFW_SAMPLES, 4);
			}
		}
		if (s_glfw_setup) {
			m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
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
				glClearColor(0, 0, 0, 0);
				glEnable(GL_DEPTH_TEST);
				//glEnable(GL_BLEND);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}

	void Window::setSize(int width, int height) {
		glfwSetWindowSize(m_window, width, height);
		glViewport(0, 0, width, height);
	}
}