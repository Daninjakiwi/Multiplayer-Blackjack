#include "Core/Window.h"
#include "Core/Network/Network.h"
#include "Scenes/TestScene.h"
#include "Scenes/SceneLogin.h"
#include "Scenes/SceneGame.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

CURL* curl;

void updateDelta() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

int main() {
	float width = 1280;
	float height = 720;

	curl = init();

	Blackjack::Core::Window window(width, height, "Blackjack");
	window.makePrimary();

	Blackjack::Core::Input::attachWindow(&window);

	Blackjack::TestScene test;
	Blackjack::SceneLogin login;
	Blackjack::SceneGame game;

	while (!window.shouldClose()) {
		updateDelta();
		window.clear();

		switch (Blackjack::Core::Scene::state) {
		case 0:
			test.update(deltaTime);
			test.draw();
			break;
		case 1:
			login.update(deltaTime);
			login.draw();
			break;
		case 2:
			game.update(deltaTime);
			game.draw();
			break;
		case -1:
			window.forceClose();
			break;
		}

		window.update();
	}

	destroy(curl);
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
			cards.push_back(data.substr(found + 12, 2));
			start = found + 14;
		}
	}

	for (auto c : cards) {
		std::cout << toCard(c) << ", ";
	}

	std::cout << std::endl;
}