#include <iostream>

#include "Core/Window.h"
#include "Core/Render/Renderer.h"
#include "Core/ResourceManager.h"

int main() {

	Core::Renderer r;

	Core::Window w(400, 400, "Test window");

	w.makePrimary();

	w.setSize(640, 640);

	Core::Shader* s = Core::ResourceManager::createShader("Flat", "res/flat_colour");

	while (!w.shouldClose()) {

		w.clear();

		r.drawTriangleLegacy(1,1, 0,0);

		w.update();
	}

}