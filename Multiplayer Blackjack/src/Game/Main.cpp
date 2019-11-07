#include <iostream>
#include "GLFW/glfw3.h"
#include "../Core/Window.h"
#include "glad/glad.h"

#define LOG(x) std::cout << x << std::endl

int main() {


	Blackjack::Window w(640, 480, "Test window");

	w.makePrimary();

	Blackjack::Window w2(400, 400, "Window 2");

	w2.makePrimary();

	while (!w2.shouldClose()) {

		w2.clear();

		glBegin(GL_TRIANGLES);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glEnd();

		w2.update();

		if (glfwGetTime() > 3) {
			w2.show();
		}
		else {
			w2.hide();
		}
	}

}