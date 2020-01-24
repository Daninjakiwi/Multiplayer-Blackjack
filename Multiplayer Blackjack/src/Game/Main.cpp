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
	e.base_width = 1920;
	e.base_height = 1080;
	e.window_width = 1024;
	e.window_height = 576;
	e.scale_width = (float)e.window_width/(float)e.base_width;
	e.scale_height = (float)e.window_height / (float)e.base_height;
	e.state = 0;

	e.server_url = "https://student.csc.liv.ac.uk/~sgkbaker/blackjack/blackjack.php";

	blackjack::core::Window window(e.window_width, e.window_height, "Blackjack");
	window.MakePrimary();

	blackjack::core::Input::AttachWindow(&window);

	blackjack::core::Shader::Load("text");
	blackjack::core::Shader::Load("gui");
	blackjack::core::Shader::Load("gui_texture");
	blackjack::core::Shader::Load("texture");

	blackjack::core::Font::Load("Monospaced");
	blackjack::core::Font::Load("OpenSans");

	blackjack::SceneLogin login(e);
	blackjack::SceneMainMenu menu(e);
	blackjack::SceneGame game;

	while (!window.ShouldClose()) {
		updateDelta();
		window.Clear();

		if (e.state == 0) {
			login.Update(deltaTime);
			login.Draw();
		}
		else if (e.state == 1){
			menu.Update(deltaTime);
			menu.Draw();		
		}

		window.Update();
	}
}