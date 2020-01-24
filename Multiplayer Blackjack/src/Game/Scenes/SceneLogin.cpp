#include "SceneLogin.hpp"

namespace blackjack {
	SceneLogin::SceneLogin(Environment& env) : Scene(), ui(env.window_width, env.window_height),env_(env),
		background(0, 0, env.window_width, env.window_height), form_background(0.3*env.window_width, 0.3*env.window_height, 768*env.scale_width, 540*env.scale_height, { 70,70,70 }),
		login(0.3 * env.window_width + (0.1 * 768 * env.scale_width), 0.3 * env.window_height + (0.3 * 540 * env.scale_height), 0.8 * 768 * env.scale_width, 95 * env.scale_height, "Login", &core::Font::Get("Monospaced", 72 * env.scale_width, { 255,255,255 })),
		create_account(0.3 * env.window_width + (0.1 * 768 * env.scale_width), 0.3 * env.window_height + (0.3 * 540 * env.scale_height) + (95 * env.scale_height) + (0.04 * env.scale_height * 540), 0.8 * 768 * env.scale_width, 95 * env.scale_height, "Create account", &core::Font::Get("Monospaced", 72 * env.scale_width, { 255,255,255 })), selected(0),
		username_input(0.3 * env.window_width + (0.1 * 768 * env.scale_width), 0.3 * env.window_height + (0.2 * 540 * env.scale_height), 0.8 * 768 * env.scale_width, 95 * env.scale_height, &core::Font::Get("Monospaced", 50 * env.scale_width, { 255,255,255 }), 15, "Username"), 
		password_input(0.3 * env.window_width + (0.1 * 768 * env.scale_width), 0.3 * env.window_height + (0.2 * 540 * env.scale_height) + (133 * env.scale_height), 0.8 * 768 * env.scale_width, 95 * env.scale_height, &core::Font::Get("Monospaced", 50 * env.scale_width, { 255,255,255 }), 15, "Password", true),
		net(), btn_back(600*env.scale_width,345*env.scale_width,75*env.scale_width,75*env.scale_width,"",&core::Font::Get("Monospaced",0)){
		
		net.SetUrl(env.server_url);

		username_input.SetMaterial({30,30,30 });
		username_input.Hide();
		username_input.SetPadX(60 * env.scale_width);

		password_input.SetMaterial({ 30,30,30 });
		password_input.Hide();
		password_input.SetPadX(60 * env.scale_width);

		btn_back.Hide();


		login.SetMaterial({ 50,50,50});
		login.SetHoverMaterial({ 35,35,35 });
		login.SetClickMaterial({ 25,25,25 });

		create_account.SetMaterial({ 50,50,50 });
		create_account.SetHoverMaterial({ 35,35,35});
		create_account.SetClickMaterial({ 25,25,25 });
		login.SetPadX(0.31 * login.GetWidth());
		create_account.SetPadX(0.005 * create_account.GetWidth());

		core::Texture::Load("background.png");
		core::Texture::Load("button.png");
		core::Texture::Load("button_hover.png");
		core::Texture::Load("button_click.png");
		core::Texture::Load("back.png");
		core::Texture::Load("back_hover.png");
		core::Texture::Load("back_click.png");

		core::Material* mat = core::Material::Create("login_background", "gui_texture");
		mat->SetUniform("u_texture", core::UniformType::TEXTURE2D, core::Texture::Get("background.png"));
		background.SetMaterial(mat);

		mat = core::Material::Create("btn_default", "gui_texture");
		mat->SetUniform("u_texture", core::UniformType::TEXTURE2D, core::Texture::Get("button.png"));
		login.SetMaterial(mat);
		create_account.SetMaterial(mat);

		mat = core::Material::Create("btn_hover", "gui_texture");
		mat->SetUniform("u_texture", core::UniformType::TEXTURE2D, core::Texture::Get("button_hover.png"));
		login.SetHoverMaterial(mat);
		create_account.SetHoverMaterial(mat);

		mat = core::Material::Create("btn_click", "gui_texture");
		mat->SetUniform("u_texture", core::UniformType::TEXTURE2D, core::Texture::Get("button_click.png"));
		login.SetClickMaterial(mat);
		create_account.SetClickMaterial(mat);

		mat = core::Material::Create("btn_back", "gui_texture");
		mat->SetUniform("u_texture", core::UniformType::TEXTURE2D, core::Texture::Get("back.png"));
		btn_back.SetMaterial(mat);

		mat = core::Material::Create("btn_back_hover", "gui_texture");
		mat->SetUniform("u_texture", core::UniformType::TEXTURE2D, core::Texture::Get("back_hover.png"));
		btn_back.SetHoverMaterial(mat);

		mat = core::Material::Create("btn_back_click", "gui_texture");
		mat->SetUniform("u_texture", core::UniformType::TEXTURE2D, core::Texture::Get("back_click.png"));
		btn_back.SetClickMaterial(mat);

		create_account.SetOnClick(std::bind(&SceneLogin::CreateAccountClicked, this));
		login.SetOnClick(std::bind(&SceneLogin::LoginClicked, this));
		btn_back.SetOnClick(std::bind(&SceneLogin::BtnBackClicked, this));
	}

	void SceneLogin::Update(float delta) {
		btn_back.Update();
		create_account.Update();
		password_input.Update();
		login.Update();
		username_input.Update();

		if (selected > 0) {
			if (username_input.GetSelected() && core::Input::KeyDown(core::InputCode::TAB)) {
				username_input.SetSelected(false);
				password_input.SetSelected();
			}
		}

		if (selected == 1) {
			if (core::Input::KeyDown(core::InputCode::ENTER)) {
				CreateAccountClicked();
			}
		}

		if (selected == 2) {
			if (core::Input::KeyDown(core::InputCode::ENTER)) {
				LoginClicked();
			}
		}
	}

	void SceneLogin::Draw() {
		btn_back.Draw(ui);
		create_account.Draw(ui);
		login.Draw(ui);
		username_input.Draw(ui);
		password_input.Draw(ui);
		form_background.Draw(ui);
		background.Draw(ui);
		ui.Render();
	}

	void SceneLogin::CreateAccountClicked() {
		if (selected == 0) {
			create_account.SetY(create_account.GetY() + (120 * env_.scale_height));
			login.Hide();
			username_input.Show();
			password_input.Show();
			btn_back.Show();
			selected = 1;
		} else if (selected == 1) {
			core::RequestData r;
			r.add("action", "register");
			r.add("username", username_input.GetText());
			r.add("password", password_input.GetText());
			std::string request = net.MakeRequest(r);
			if (request.substr(0,2).compare("01") == 0) {
				env_.token = request.substr(2);
				env_.username = username_input.GetText();
				env_.password = password_input.GetText();
				env_.state = 1;
			}
			else if (request.substr(0, 2).compare("02") == 0) {
				COREWARN("Error creating account.");
			}
			else if (request.substr(0, 2).compare("03") == 0) {
				COREWARN("Username invalid.");
			}
			else if (request.substr(0, 2).compare("04") == 0) {
				COREWARN("Username taken.");
			}
		}

	}

	void SceneLogin::LoginClicked() {
		if (selected == 0) {
			login.SetY(login.GetY() + (120 * env_.scale_height) + (95 * env_.scale_height));
			create_account.Hide();
			username_input.Show();
			password_input.Show();
			btn_back.Show();
			selected = 2;
		}
		else if (selected == 2) {
			core::RequestData r;
			r.add("action", "login");
			r.add("username", username_input.GetText());
			r.add("password", password_input.GetText());
			std::string request = net.MakeRequest(r);
			if (request.substr(0, 2).compare("05") == 0) {
				env_.token = request.substr(2);
				env_.username = username_input.GetText();
				env_.password = password_input.GetText();
				env_.state = 1;
			}
			else if (request.substr(0, 2).compare("06") == 0) {
				COREWARN("Invalid username/password.");
			}
		}
	}

	void SceneLogin::BtnBackClicked() {
		if (selected == 1) {
			login.Show();
			create_account.SetY(create_account.GetY() - (120 * env_.scale_height));
		}
		else if (selected == 2) {
			create_account.Show();
			login.SetY(login.GetY() - (120 * env_.scale_height) - (95 * env_.scale_height));
		}
		selected = 0;
		username_input.Reset();
		password_input.Reset();
		username_input.Hide();
		password_input.Hide();
		btn_back.Hide();
	}
}