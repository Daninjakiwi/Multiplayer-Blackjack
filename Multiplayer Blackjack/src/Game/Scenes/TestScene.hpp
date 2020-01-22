#pragma once
#include "Core/Scene.hpp"
#include "Core/Core.hpp"

namespace blackjack {
	class TestScene : public core::Scene {
	private:
		core::RendererUI ui;
		core::Font font;
		core::InputBox box;
		core::Button btn;
		core::Button btn2;
	public:
		TestScene();

		void Update(float delta);

		void Draw();

		void onClick();
		void onClick2();

		static void BtnClick();
	};
}
