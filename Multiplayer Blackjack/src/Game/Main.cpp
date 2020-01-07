#include "Core/Window.h"
#include "Core/Render/Renderer.h"
#include "Core/ResourceManager.h"
#include "Core/Render/Meshes/Quad.h"
#include "Core/Render/Meshes/Cube.h"
#include "Core/Render/Meshes/CircleSegment.h"
#include "Core/Render/Texture.h"
#include "Core/Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Core/Log.h"
#include "Core/Input.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float width = 640;
float height = 640;

Core::Camera camera(45.0f, 1);

void updateDelta() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void updateCamera() {
	if (Core::Input::keyDown(Core::VOLT_A)) {
		camera.translateX(2.5f * -deltaTime);
	}
	if (Core::Input::keyDown(Core::VOLT_D)) {
		camera.translateX(2.5f * deltaTime);
	}
	if (Core::Input::keyDown(Core::VOLT_W)) {
		camera.translateY(2.5f * deltaTime);
	}
	if (Core::Input::keyDown(Core::VOLT_S)) {
		camera.translateY(2.5f * -deltaTime);
	}

	if (Core::Input::keyDown(Core::VOLT_Z)) {
		camera.translateZ(2.5f * deltaTime);
	}

	if (Core::Input::keyDown(Core::VOLT_X)) {
		camera.translateZ(2.5f * -deltaTime);
	}
	if (Core::Input::keyDown(Core::VOLT_Q)) {
		camera.pitch(30 * deltaTime);
	}
	if (Core::Input::keyDown(Core::VOLT_E)) {
		camera.pitch(30 * -deltaTime);
	}
	if (Core::Input::keyDown(Core::VOLT_C)) {
		camera.yaw(30 * deltaTime);
	}

	if (Core::Input::keyDown(Core::VOLT_V)) {
		camera.yaw(30 * -deltaTime);
	}

	if (Core::Input::keyDown(Core::VOLT_G)) {
		camera.translateY(2.5f * deltaTime);
		camera.pitch(30 * -deltaTime);
	}
}

int main() {

	Core::Texture t("Logo.png");

	Core::Window window(width, height, "Test window");
	window.makePrimary();

	Core::Input::attachWindow(&window);

	Core::Renderer3D renderer;
	Core::Shader* s = Core::ResourceManager::createShader("Flat", "res/flat_colour");

	renderer.bind();
	s->bind();

	s->setVec3("u_colour",0.2f, 0.35f, 0.43f);

	Core::RenderObject obj;
	Core::Cube table;
	Core::CircleSegment c(1, 360);

	obj.setMesh(&c);

	while (!window.shouldClose()) {
		updateDelta();
		window.clear();

		updateCamera();

		obj.getTransform().setRotation(0, 90, 0);
		obj.getTransform().setScale(2, 0.2f, 1);


		s->setMat4("u_camera", camera.getView());
		s->setMat4("u_transform", obj.getTransform().getMatrix());
		renderer.draw(obj);

		renderer.flush();

		window.update();

	}

}