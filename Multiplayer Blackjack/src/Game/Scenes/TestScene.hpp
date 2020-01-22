#pragma once
#include "Core/Scene.hpp"
#include "Core/Core.hpp"

namespace blackjack {
	class TestScene : public core::Scene {
	private:
		core::RendererUI ui;

	public:
		TestScene();

		void Update(float delta);

		void Draw();

		static void BtnClick();
	};
}
