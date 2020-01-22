#include "SceneMainMenu.hpp"

namespace blackjack {
	SceneMainMenu::SceneMainMenu(Environment& e) : Scene(), env(e), ui(1280, 720), font(core::Font::Get("Monospaced", 36)), name(100, 100, 500, 100, "", &font) {

	}

	void SceneMainMenu::Update(float delta) {
		name.Update();
		name.SetText(env.username);
	}

	void SceneMainMenu::Draw() {
		name.Draw(ui);
		ui.Render();
	}
}