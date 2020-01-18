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
#include "Core/Network/Network.h"
#include "Core/Render/Material.h"
#include "Card.h"
#include "Core/gui/Colour.h"
#include "Core/gui/Button.h"
#include "Core/gui/Slider.h"
#include "Core/gui/Font.h"
#include "Core/gui/Text.h"

#include <cstdlib>
#include <thread>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float width = 1280;
float height = 720;

Blackjack::Core::Camera camera(45.0f,16.0f/9.0f);

int num = 0;

CURL* curl;

std::string token;

void button_click() {
	LOG("Hello world");
}

void updateDelta() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

std::string toCard(const std::string value) {
	int val = std::stoi(value);

	std::string out = "";

	if (val % 13 == 0) {
		out += "A";
	}
	else if (val % 13 < 10) {
		out += std::to_string((val % 13) + 1);
	}
	else {
		out += "10";
	}

	return out;
}

void interpret(std::string data) {
	int start = 0;
	auto found = 0;

	std::vector<std::string> cards;

	while (found != std::string::npos) {
		found = data.find("DRAW#Kieran", start);
		if (found != std::string::npos) {
			//LOG(data.substr(found, 13));
			cards.push_back(data.substr(found+12, 2));
			start = found + 14;
		}
	}

	//std::cout << std::endl << std::endl;

	for (auto c : cards) {
		std::cout << toCard(c) << ", ";
	}

	std::cout << std::endl;
}

void updateCamera() {
	using namespace Blackjack::Core;

	if (Input::keyDown(VOLT_L)) {
		std::unordered_map<std::string, std::string> data;
		data["action"] = "login";
		data["username"] = "Kieran";
		data["password"] = "test";

		token = makeRequest(curl, data);

	}

	if (Input::keyDown(VOLT_J)) {
		std::unordered_map<std::string, std::string> data;
		data["action"] = "join_room";
		data["token"] = token;
		data["room_id"] = "280548258";

		makeRequest(curl, data);
	}

	if (Input::keyDown(VOLT_O)) {
		std::unordered_map<std::string, std::string> data;
		data["action"] = "make_bet";
		data["token"] = token;
		data["room_id"] = "280548258";
		data["amount"] = "10";

		makeRequest(curl, data);
	}

	if (Input::keyDown(VOLT_K)) {
		std::unordered_map<std::string, std::string> data;
		data["action"] = "draw";
		data["token"] = token;
		data["room_id"] = "280548258";

		makeRequest(curl, data);
	}

	if (Input::keyDown(VOLT_P)) {
		std::unordered_map<std::string, std::string> data;
		data["action"] = "leave_room";
		data["token"] = token;
		data["room_id"] = "280548258";

		makeRequest(curl, data);
	}

	std::unordered_map<std::string, std::string> data;
	data["action"] = "update";
	data["token"] = token;
	data["room_id"] = "280548258";
	data["seed"] = "ClientSeed";

	//std::string result = makeRequest(curl, data);

	//LOG(result);

	//interpret(makeRequest(curl, data));


}

int main() {
	using namespace Blackjack::Core;

	curl = init();

	Window window(width, height, "Blackjack");
	window.makePrimary();

	Input::attachWindow(&window);

	camera.translateX(1.66f);
	camera.translateY(8.63f);
	camera.translateZ(14.7f);
	camera.pitch(-40);

	Light light;
	light.setAmbient(0.2f, 0.2f, 0.2f);
	light.setDiffuse(0.4f, 0.4f, 0.4f);
	light.setSpecular(0.3f, 0.3f, 0.3f);
	light.setPosition(2.5f, 10, -10.0f);

	Renderer3D renderer;
	RendererUI ui(width, height);

	renderer.setLight(light);
	renderer.setCamera(camera);

	Blackjack::Card card_mesh;

	Material* card_material = ResourceManager::createMaterial("CardMaterial", ResourceManager::createShader("Texture", "res/texture"));
	card_material->setUniform("u_material.diffuse", UniformType::TEXTURE2D, ResourceManager::createTexture("cards", "res/Cards.png"));
	card_material->setUniform1f("u_material.shininess", 32.0f);

	RenderObject card(&card_mesh, card_material);
	card.getTransform().setRotation(-90, 0, 0);
	card.getTransform().setPosition(3, 0.15f, 5);

	CircleSegment table_mesh(1, 180);

	Material* table_material = ResourceManager::createMaterial("TableMaterial", ResourceManager::getShader("Texture"));
	table_material->setUniform("u_material.diffuse", UniformType::TEXTURE2D, ResourceManager::createTexture("felt", "res/table.png"));
	table_material->setUniform1f("u_material.shininess", 64.0f);

	RenderObject table(&table_mesh, table_material);
	table.getTransform().setPosition(2, 0, 0);
	table.getTransform().setScale(10, 0.1f, 10);
	table.getTransform().setRotation(0, 180, 0);

	Colour yellow(255, 178, 0);
	Colour red(255, 0, 0);
	Colour blue(100, 50, 220);

	Colour gray(40, 40, 40);

	Button btn(30, 30, 100, 100, yellow.getMaterial(), red.getMaterial(), blue.getMaterial());

	Slider slider(200, 200, 300, 300, gray.getMaterial(), yellow.getMaterial());

	btn.setOnClickFunc(&button_click);


	Font f("res/test.fnt");

	Text t("Hello World", 200,300,100, f);

	while (!window.shouldClose()) {
		updateDelta();
		window.clear();

		updateCamera();

		//btn.update();

		//slider.update();

		//ui.draw(btn);
		//ui.draw(slider);

		ui.draw(t);
		//ui.draw(btn);

		ui.flush();

		renderer.draw(table);

		renderer.draw(card);

		renderer.flush();

		window.update();
	}

	destroy(curl);
}