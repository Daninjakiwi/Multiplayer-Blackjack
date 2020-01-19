#pragma once
#include "Core/Scene.h"
#include "Core/Core.h"

namespace Blackjack {
	class TestScene : public Core::Scene {
	private:
		Core::RendererUI ui;
		Core::Font font;

		Core::Button btn;
		Core::TextField field;

	public:
		TestScene();

		void update(float delta);

		void draw();

		static void btnClick();
	};
}
