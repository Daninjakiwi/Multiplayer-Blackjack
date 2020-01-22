#include "Core/Window.hpp"
#include "Core/Network/Network.h"
#include "Scenes/TestScene.hpp"
#include "Scenes/SceneGame.hpp"
#include "Core/gui/Label.hpp"
#include "Core/gui/InputBox.hpp"
#include "Core/gui/Colour.hpp"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

CURL* curl;

void updateDelta() {
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void btnClick() {
	CORETRACE("clicked");
}

int main() {
	int width = 1280;
	int height = 720;

	bool flag = false;

	curl = init();

	blackjack::core::Window window(width, height, "Blackjack");
	window.MakePrimary();

	blackjack::core::Input::AttachWindow(&window);

	blackjack::TestScene test;
	blackjack::SceneGame game;

	blackjack::core::Resources::CreateShader("text", "res/text");
	blackjack::core::Resources::CreateShader("gui", "res/ui");

	blackjack::core::Font::Load("Monospaced");
	blackjack::core::Font font = blackjack::core::Font::Get("Monospaced", 40, { 0,0,0 });

	blackjack::core::InputBox box = blackjack::core::InputBox(200, 300, 500, 200, &font, { 0,150,0 }, 10);

	blackjack::core::Label label(0, 0, 200, 100, "Test", &font);

	blackjack::core::Slider2 slider(100, 100, 200, 100);

	blackjack::core::GuiElement element(100, 100, 100, 100);

	blackjack::core::Button btn(100, 100, 300, 50, "Click me", &font);

	blackjack::core::RendererUI ui(width,height);

	btn.SetOnClick(btnClick);

	while (!window.ShouldClose()) {
		updateDelta();
		window.Clear();

		box.Update();
		btn.Update();

		box.Draw(ui);
		btn.Draw(ui);
		ui.Render();

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