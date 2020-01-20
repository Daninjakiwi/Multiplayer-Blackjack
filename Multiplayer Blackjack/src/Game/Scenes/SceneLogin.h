#pragma once
#include "Core/Scene.hpp"
#include "Core/Core.hpp"

namespace Blackjack {
	class SceneLogin : public Core::Scene {
	private:
		Core::RendererUI ui;
		Core::Button btn;
	public:
		SceneLogin();

		void Update(float delta);

		void Draw();

		static void BtnClick();
	};
}