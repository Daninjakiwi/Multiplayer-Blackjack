#pragma once
#include <string>
#include "GLFW/glfw3.h"

namespace blackjack::core {

	class Window {
		friend class Input;
	private:
		static GLFWwindow* primary_;
		static bool glfw_setup_;
		static bool glad_setup_;
		GLFWwindow* window_;
	public:

		Window(int width, int height, const std::string& title);
		~Window();

		void MakePrimary();
		void Update();

		bool ShouldClose();

		void Show();
		void Hide();
		void Clear();

		void ForceClose();

		void SetSize(int width, int height);
	};
}
