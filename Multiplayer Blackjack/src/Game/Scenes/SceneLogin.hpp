#pragma once
#include "Core/Core.hpp"
#include "Core/Scene.hpp"
#include "../Environment.hpp"
#include "Core/Network/Network.h"
#include <thread>

namespace blackjack {
	class SceneLogin : public core::Scene {
	private:
		core::RendererUI ui;
		core::GuiElement background;
		core::GuiElement form_background;
		core::Button login;
		core::Button create_account;
		core::InputBox username_input;
		core::InputBox password_input;
		core::Button btn_back;
		Environment& env_;
		unsigned char selected;
		core::Network net;
	public:
		SceneLogin(Environment& env);

		void Update(float delta);
		void Draw();

		void CreateAccountClicked();
		void LoginClicked();

		void BtnBackClicked();

	};
}
