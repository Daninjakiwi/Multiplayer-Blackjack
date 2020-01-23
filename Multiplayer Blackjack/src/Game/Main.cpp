#include "Core/Window.hpp"
#include "Core/Network/Network.h"
#include "Scenes/SceneGame.hpp"
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
	blackjack::Environment e;
	e.window_width = 1280;
	e.window_height = 720;

	blackjack::core::Window window(e.window_width, e.window_height, "Blackjack");
	window.MakePrimary();

	blackjack::core::Input::AttachWindow(&window);

	blackjack::core::Resources::LoadShader("text");
	blackjack::core::Resources::LoadShader("gui");
	blackjack::core::Resources::LoadShader("gui_texture");

	blackjack::core::Font::Load("Monospaced");

	blackjack::SceneLogin login(e);
	blackjack::SceneMainMenu menu(e);
	blackjack::SceneGame game;

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
				COREINFO("Logged in as '" + e.username + "'.");
			}
			else {
				blackjack::core::Scene::SetState(0);
				COREERROR("Invalid login entered.");
			}
		}
		else if (blackjack::core::Scene::GetState() == 2) {
			menu.Update(deltaTime);
			menu.Draw();
		}


		window.Update();
	}
}