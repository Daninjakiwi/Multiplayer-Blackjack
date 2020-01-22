#include "TestScene.hpp"


namespace blackjack {

	TestScene::TestScene() 
		:Scene(), ui(1280, 720), font(core::Font::Get("Monospaced", 36)), box(100, 100, 300, 100, &font, 15), btn(300,300, 200,50, "Submit", &font), btn2(700, 300, 200, 50, "Test", &font) {

		btn.SetOnClick(std::bind(&TestScene::onClick, this));
		btn2.SetOnClick(std::bind(&TestScene::onClick2, this));
	}

	void TestScene::Update(float delta) {
		box.Update();
		btn.Update();
		btn2.Update();
	}

	void TestScene::Draw() {
		box.Draw(ui);
		btn.Draw(ui);
		btn2.Draw(ui);
		ui.Render();
	}

	void TestScene::onClick() {
		COREINFO("Btn1 click");
	}

	void TestScene::onClick2() {
		COREINFO("Btn2 click");
	}

	void TestScene::BtnClick() {
		COREWARN("clicked");
		SetState(2);
	}
}