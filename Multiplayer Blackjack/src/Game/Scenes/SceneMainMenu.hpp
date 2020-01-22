#pragma once
#include "Core/Scene.hpp"
#include "Core/Core.hpp"
#include "../Environment.hpp"

namespace blackjack {
	class SceneMainMenu : core::Scene {
	private:
		Environment& env;
		core::RendererUI ui;
		core::Font font;
		core::Label name;
	public:
		SceneMainMenu(Environment& e);

		void Update(float delta);
		void Draw();
	};
}
