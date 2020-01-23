#pragma once
#include "Core/Core.hpp"
#include "Core/Scene.hpp"
#include "../Environment.hpp"

namespace blackjack {
	class SceneLogin : public core::Scene {
	private:
		core::RendererUI ui;
		core::Font input_font;
		core::Font btn_font;
		core::InputBox username;
		core::InputBox password;
		core::GuiElement background;
		core::Text title;
		core::Button submit;
		Environment& env_;
	public:
		SceneLogin(Environment& env);

		void Update(float delta);
		void Draw();

		void SubmitClicked();
	};
}
