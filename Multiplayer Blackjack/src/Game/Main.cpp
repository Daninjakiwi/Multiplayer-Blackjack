#include "Core/Window.hpp"
#include "Core/Network/Network.h"
#include "Scenes/TestScene.hpp"
#include "Scenes/SceneGame.hpp"
#include "Core/gui/Label.hpp"
#include "Core/gui/InputBox.hpp"
#include "Core/gui/Colour.hpp"
#include "Scenes/SceneLogin.hpp"
#include "Scenes/SceneMainMenu.hpp"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void updateDelta() {
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

int main() {
	int width = 1280;
	int height = 720;


	blackjack::core::Window window(width, height, "Blackjack");
	window.MakePrimary();

	blackjack::core::Input::AttachWindow(&window);

	blackjack::core::Resources::CreateShader("text", "res/text");
	blackjack::core::Resources::CreateShader("gui", "res/ui");

	blackjack::core::Font::Load("Monospaced");

	blackjack::Environment e;

	blackjack::SceneLogin login(e);
	blackjack::SceneMainMenu menu(e);

	blackjack::core::Network net;
	net.SetUrl("https://student.csc.liv.ac.uk/~sgkbaker/blackjack/blackjack.php");

	while (!window.ShouldClose()) {
		updateDelta();
		window.Clear();

		if (blackjack::core::Scene::GetState() == 0) {
			login.Update(deltaTime);
			login.Draw();
		}
		else if (blackjack::core::Scene::GetState() == 1){
			blackjack::core::RequestData r;
			r.add("action", "login");
			r.add("username", e.username);
			r.add("password", e.password);
			e.token = net.MakeRequest(r);
			if (e.token.compare("invlogin")) {
				blackjack::core::Scene::SetState(2);
			}
			else {
				blackjack::core::Scene::SetState(0);
			}
		}
		else if (blackjack::core::Scene::GetState() == 2) {
			menu.Update(deltaTime);
			menu.Draw();
		}


		window.Update();
	}
}