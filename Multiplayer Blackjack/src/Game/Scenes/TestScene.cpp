#include "TestScene.h"


namespace Blackjack {
	TestScene::TestScene() :Scene(), ui(1280, 720), btn(200, 200, 250, 150, Core::Colour::getColour(150,150,150), Core::Colour::getColour(180, 180, 180), Core::Colour::getColour(80, 80, 80)), font("res/test.fnt"), field(100, 100, 300, 80, Core::Colour::getColour(40, 40, 40), font, 40, 10, 15, 30) {
		btn.setOnClickFunc(btnClick);
	}

	void TestScene::update(float delta) {
		btn.update();
		field.update();
	}

	void TestScene::draw() {
		ui.draw(field);
		ui.draw(btn);
		ui.flush();
	}

	void TestScene::btnClick() {
		state = 2;
	}
}