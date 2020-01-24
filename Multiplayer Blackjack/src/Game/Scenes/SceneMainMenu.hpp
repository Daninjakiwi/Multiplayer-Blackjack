#pragma once
#include "Core/Scene.hpp"
#include "Core/Core.hpp"
#include "../Environment.hpp"
#include "Core/Network/Network.h"


namespace blackjack {
	class SceneMainMenu : core::Scene {
	private:
		Environment& env;
		core::RendererUI ui;
		core::GuiElement background;
		core::GuiElement form_background;
		core::Button btn_play;
		core::Button btn_shop;
		core::Button btn_help;
		core::Label player_name;
		core::Network net;
		core::GuiElement player_icon;
		core::Label player_balance;
		core::GuiElement balance_icon;
		std::string current_user;
	public:
		SceneMainMenu(Environment& e);

		void Update(float delta);
		void Draw();

		void PlayClicked();
	};

	class Split {
	private:
		std::vector<std::string> values;
	public:
		Split(const std::string& str);
		~Split();

		std::string Get(int index);
	};
}
