#include "Core/Window.hpp"
#include "Core/Network/Network.h"
#include "Scenes/TestScene.h"
#include "Scenes/SceneGame.h"
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
	CORE_LOG("Clicked");
}

int main() {
	int width = 1280;
	int height = 720;

	bool flag = false;

	curl = init();

	Blackjack::Core::Window window(width, height, "Blackjack");
	window.MakePrimary();

	Blackjack::Core::Input::AttachWindow(&window);

	Blackjack::TestScene test;
	Blackjack::SceneGame game;

	Blackjack::Core::Resources::CreateShader("text", "res/text");
	Blackjack::Core::Resources::CreateShader("gui", "res/ui");

	Blackjack::Core::Font::Load("Monospaced");
	Blackjack::Core::Font font = Blackjack::Core::Font::Get("Monospaced", 40, { 0,0,0 });

	Blackjack::Core::InputBox box = Blackjack::Core::InputBox(200, 300, 500, 200, &font, { 0,150,0 }, 10);

	Blackjack::Core::Label label(0, 0, 200, 100, "Test", &font);

	Blackjack::Core::Slider2 slider(100, 100, 200, 100);

	Blackjack::Core::GuiElement element(100, 100, 100, 100);

	Blackjack::Core::Button btn(100, 100, 300, 50, "Click me", &font);

	Blackjack::Core::RendererUI ui(width,height);

	btn.SetOnClick(btnClick);

	while (!window.ShouldClose()) {
		updateDelta();
		window.Clear();

		box.Update();

		box.Draw(ui);
		ui.render();

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