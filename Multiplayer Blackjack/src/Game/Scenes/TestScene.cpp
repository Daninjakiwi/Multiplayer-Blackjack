#include "TestScene.hpp"


namespace blackjack {
	TestScene::TestScene() 
		:Scene(), ui(1280, 720) {
	}

	void TestScene::Update(float delta) {
	}

	void TestScene::Draw() {
	}

	void TestScene::BtnClick() {
		SetState(2);
	}
}