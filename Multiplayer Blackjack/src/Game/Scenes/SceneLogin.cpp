#include "SceneLogin.hpp"

namespace blackjack {
	SceneLogin::SceneLogin(Environment& env) : Scene(), ui(env.window_width, env.window_height), input_font(core::Font::Get("Monospaced", 24)), btn_font(core::Font::Get("Monospaced", 36))
		, username(490, 290, 300, 50, &input_font, 10), password(490, 390, 300, 50, &input_font, 10,{ 255,255,255 }, true), submit(540, 490, 200, 50, "Login", &btn_font), env_(env),
		background(0,0,env.window_width,env.window_height), title(320,50,"BLACKJACK", core::Font::Get("Monospaced", 120)) {
		core::Material* mat = core::Resources::CreateMaterial("login_background", core::Resources::GetShader("gui_texture"));
		mat->SetUniform("u_texture", core::UniformType::TEXTURE2D, core::Resources::CreateTexture("background_texture", "res/background.png"));
		background.SetMaterial(mat);
		submit.SetOnClick(std::bind(&SceneLogin::SubmitClicked, this));
	}

	void SceneLogin::Update(float delta) {
		username.Update();
		password.Update();
		submit.Update();
		if (username.GetSelected() && core::Input::KeyDown(core::InputCode::TAB)) {
			username.SetSelected(false);
			password.SetSelected();
		}

		if (core::Input::KeyJustPressed(core::InputCode::ENTER)) {
			username.SetSelected(false);
			password.SetSelected(false);
			SubmitClicked();
		}
	}
	void SceneLogin::Draw() {
		username.Draw(ui);
		password.Draw(ui);
		submit.Draw(ui);
		title.Draw(ui);
		background.Draw(ui);
		ui.Render();
	}

	void SceneLogin::SubmitClicked() {
		env_.username = username.GetText();
		env_.password = password.GetText();
		SetState(1);
	}
}