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

	Core::Window window(width, height, "Test window");
	window.makePrimary();

	Core::Input::attachWindow(&window);

	Core::Renderer3D renderer;
	Core::ResourceManager::createShader("Flat", "res/flat_colour");
	Core::ResourceManager::createShader("Texture", "res/texture");
	Core::Shader* s = Core::ResourceManager::getShader("Flat");

	Core::Texture t("res/Logo.png");

	renderer.bind();
	s->bind();

	t.bind();

	camera.translateZ(-3);
	camera.translateX(0.5f);

	//s->setVec3("u_colour",1.0f,0.0f,0.0f);
	//s->setUInt("u_texture", *t.getId());
	s->setVec3("u_light.position", -1.2f, 1.5f, 1.2f);

	s->setVec3("u_light.ambient", 0.2f, 0.2f, 0.2f);
	s->setVec3("u_light.diffuse", 0.5f, 0.5f, 0.5f);
	s->setVec3("u_light.specular", 1.0f, 1.0f, 1.0f);

	s->setVec3("u_material.ambient", 1.0f, 0.0f, 0.0f);
	s->setVec3("u_material.diffuse", 1.0f, 0.0f, 0.0f);
	s->setVec3("u_material.specular", 0.5f, 0.5f, 0.5f);
	s->setFloat("u_material.shininess", 1.0f);

	Core::RenderObject obj;
	Core::Cube table;
	Core::CircleSegment c(1, 360);

	obj.setMesh(&table);

	while (!window.shouldClose()) {
		updateDelta();
		window.clear();

		updateCamera();

		//obj.getTransform().setRotation(0, 90, 0);
		obj.getTransform().setScale(2, 0.2f, 1);

		glm::vec3 pos = camera.getPosition();

		s->setVec3("u_view_pos", pos.x, pos.y, pos.z);

		s->setMat4("u_camera", camera.getView());
		s->setMat4("u_transform", obj.getTransform().getMatrix());
		renderer.draw(obj);

		renderer.flush();

		window.update();

	}

}