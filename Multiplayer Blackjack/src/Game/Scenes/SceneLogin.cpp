#include "SceneLogin.h"

namespace Blackjack {
	SceneLogin::SceneLogin() : Scene(), ui(1280, 720), btn(300, 300, 250, 150, Core::Colour::getColour(200, 150, 150), Core::Colour::getColour(180, 0, 180), Core::Colour::getColour(0, 120, 120)) {
		btn.setOnClickFunc(btnClick);
	}

	void SceneLogin::update(float delta) {
		btn.update();
	}

	void SceneLogin::draw() {
		ui.draw(btn);
		ui.flush();
	}

	void SceneLogin::btnClick() {
		state = -1;
	}
}