#pragma once
#include "Core/Scene.h"
#include "Core/Core.h"

namespace Blackjack {
	class SceneLogin : public Core::Scene {
	private:
		Core::RendererUI ui;
		Core::Button btn;
	public:
		SceneLogin();

		void update(float delta);

		void draw();

		static void btnClick();
	};
}