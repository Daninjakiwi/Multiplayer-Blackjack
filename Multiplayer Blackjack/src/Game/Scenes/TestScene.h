#pragma once
#include "Core/Scene.hpp"
#include "Core/Core.hpp"

namespace Blackjack {
	class TestScene : public Core::Scene {
	private:
		Core::RendererUI ui;
		Core::Font font;

		Core::Button btn;
		Core::TextField field;

	public:
		TestScene();

		void Update(float delta);

		void Draw();

		static void BtnClick();
	};
}
