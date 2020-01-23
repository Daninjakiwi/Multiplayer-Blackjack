#include <iostream>
#include "Log.hpp"
#include "glad/glad.h"

#include "Window.hpp"
#include "Resources.hpp"

namespace blackjack::core {

	GLFWwindow* Window::primary_ = nullptr;
	bool Window::glfw_setup_ = false;
	bool Window::glad_setup_ = false;

	void Window::ForceClose() {
		glfwSetWindowShouldClose(window_, true);
	}

	Window::Window(int width, int height, const std::string& title) : window_(nullptr) {
		if (!glfw_setup_) {
			if (glfwInit()) {
				glfw_setup_ = true;
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			}
			else {
				COREFATAL("Failed to initialise glfw.");
			}
		}
		if (glfw_setup_) {
			window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		}	
	}

	Window::~Window() {
		if (window_ == primary_) {
			primary_ = nullptr;
		}
		glfwDestroyWindow(window_);
	}

	void Window::MakePrimary() {
		if (primary_ != window_) {
			if (primary_ != nullptr) {
				glClear(GL_COLOR_BUFFER_BIT);
				glfwSwapBuffers(primary_);
				glClear(GL_COLOR_BUFFER_BIT);
			}
			glfwMakeContextCurrent(window_);
			primary_ = window_;
		}
		if (!glad_setup_) {
			if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				//glfwSwapInterval(0);
				glad_setup_ = true;
				glClearColor(0, 0, 0, 0);
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else {
				COREFATAL("Failed to initialise glad.");
			}
		}
	}

	void Window::Update() {
		glfwPollEvents();
		glfwSwapBuffers(window_);
	}

	bool Window::ShouldClose() {
		return glfwWindowShouldClose(window_);
	}

	void Window::Show() {
		glfwShowWindow(window_);
	}

	void Window::Hide() {
		glfwHideWindow(window_);
	}


	void Window::Clear() {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}

	void Window::SetSize(int width, int height) {
		glfwSetWindowSize(window_, width, height);
		glViewport(0, 0, width, height);
	}
}