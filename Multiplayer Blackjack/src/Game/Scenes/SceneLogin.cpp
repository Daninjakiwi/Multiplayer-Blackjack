#include "SceneLogin.hpp"

namespace blackjack {
	SceneLogin::SceneLogin(Environment& env) : Scene(), ui(1280,720), input_font(core::Font::Get("Monospaced", 24)), btn_font(core::Font::Get("Monospaced", 36))
		, username(490, 310, 300, 50, &input_font, 10), password(490, 410, 300, 50, &input_font, 10,{ 255,255,255 }, true), submit(490, 550, 300, 50, "Login", &btn_font), env_(env) {
		//password.SetTextHidden(true);
		submit.SetOnClick(std::bind(&SceneLogin::SubmitClicked, this));
	}

	void SceneLogin::Update(float delta) {
		username.Update();
		password.Update();
		submit.Update();
	}
	void SceneLogin::Draw() {
		username.Draw(ui);
		password.Draw(ui);
		submit.Draw(ui);
		ui.Render();
	}

	void SceneLogin::SubmitClicked() {
		env_.username = username.GetText();
		env_.password = password.GetText();
		SetState(1);
	}
}