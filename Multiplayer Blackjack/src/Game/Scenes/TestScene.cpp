#include "TestScene.h"


namespace Blackjack {
	TestScene::TestScene() 
		:Scene(), ui(1280, 720), 
		btn(200, 200, 250, 150, Core::Colour::getColour(150,150,150), Core::Colour::getColour(180, 180, 180), Core::Colour::getColour(80, 80, 80)),
		font("res/OpenSans.fnt"), field(100, 100, 300, 80, Core::Colour::getColour(40, 40, 40), font, 40, 30,false, 15, 30) {

		btn.setOnClickFunc(BtnClick);
		//field.setTextColour(255, 0, 0);
	}

	void TestScene::Update(float delta) {
		btn.update();
		field.update();
		//LOG(field.getText());
	}

	void TestScene::Draw() {
		Core::GuiElement e(Core::Colour::getColour(0,180,200), 500,100,300,100);
		ui.draw(e);
		ui.draw(field);
		ui.draw(btn);
		ui.flush();
	}

	void TestScene::BtnClick() {
		SetState(2);
	}
}