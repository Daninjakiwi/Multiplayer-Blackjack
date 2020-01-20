#include "Core/Window.hpp"
#include "Core/Network/Network.h"
#include "Scenes/TestScene.h"
#include "Scenes/SceneLogin.h"
#include "Scenes/SceneGame.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

CURL* curl;

void updateDelta() {
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

int main() {
	int width = 1280;
	int height = 720;

	curl = init();

	Blackjack::Core::Window window(width, height, "Blackjack");
	window.MakePrimary();

	Blackjack::Core::Input::AttachWindow(&window);

	Blackjack::TestScene test;
	Blackjack::SceneLogin login;
	Blackjack::SceneGame game;

	while (!window.ShouldClose()) {
		updateDelta();
		window.Clear();

		switch (Blackjack::Core::Scene::GetState()) {
		case 0:
			test.Update(deltaTime);
			test.Draw();
			break;
		case 1:
			login.Update(deltaTime);
			login.Draw();
			break;
		case 2:
			game.Update(deltaTime);
			game.Draw();
			break;
		case -1:
			window.ForceClose();
			break;
		}

		window.Update();
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