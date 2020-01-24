#include "SceneMainMenu.hpp"

namespace blackjack {
	Split::Split(const std::string& str) {
		std::size_t current, previous = 0;
		current = str.find("#");
		while (current != std::string::npos) {
			values.push_back(str.substr(previous, current - previous));
			previous = current + 1;
			current = str.find("#", previous);
		}
		values.push_back(str.substr(previous, current - previous));
	}

	Split::~Split() {

	}

	std::string Split::Get(int index) {
		return values[index];
	}



	SceneMainMenu::SceneMainMenu(Environment& e) : Scene(), env(e), ui(e.window_width, e.window_height),
	background(0, 0, env.window_width, env.window_height), form_background(0.3 * env.window_width, 0.3 * env.window_height, 768 * env.scale_width, 540 * env.scale_height, { 70,70,70 }),
	btn_play(0.3 * env.window_width + (0.1 * 768 * env.scale_width), 0.3 * env.window_height + (60 * env.scale_height), 0.8 * 768 * env.scale_width, 95 * env.scale_height,"Play", &core::Font::Get("Monospaced", 72*env.scale_width, { 255,255,255 })),
	btn_shop(0.3 * env.window_width + (0.1 * 768 * env.scale_width), 0.3 * env.window_height + (223 * env.scale_height), 0.8 * 768 * env.scale_width, 95 * env.scale_height, "Shop", &core::Font::Get("Monospaced", 72*env.scale_width, { 255,255,255 })),
		btn_help(0.3 * env.window_width + (0.1 * 768 * env.scale_width), 0.3 * env.window_height + (386 * env.scale_height), 0.8 * 768 * env.scale_width, 95 * env.scale_height, "Help", &core::Font::Get("Monospaced", 72 * env.scale_width, { 255,255,255 })),
		player_name(0+(0.01*env.window_height), 0 + (0.01 * env.window_height), 720 * env.scale_width + (0.1 * env.window_height), (0.1 * env.window_height), "WWWWWWWWWWWWWWW", &core::Font::Get("Monospaced", 72 * env.scale_width, { 255,255,255 }), { 50,50,50 }), net(),
		player_icon(0.02 * env.window_height, 0.02 * env.window_height, 0.08 * env.window_height, 0.08 * env.window_height, { 255,0,0 }),
		player_balance(720 * env.scale_width + (0.1 * env.window_height) + (0.03 * env.window_width), 0.01 * env.window_height, 0.3 * env.window_width, 0.1 * env.window_height, "2147483647", &core::Font::Get("Monospaced", 72 * env.scale_width, { 255,255,255 }), { 50,50,50 }),
		balance_icon(720 * env.scale_width + (0.1 * env.window_height) + (0.03 * env.window_width) + 0.3 * env.window_width - (0.09 * env.window_height), 0.02 * env.window_height, 0.08 * env.window_height, 0.08 * env.window_height, { 255,255,0 }), current_user(e.username) {

		player_name.SetPadX((0.1*env.window_height) + 10 * env.scale_width);
		player_balance.SetPadX(10 * env.scale_width);

		btn_play.SetPadX(210 * env.scale_width);
		btn_shop.SetPadX(210 * env.scale_width);
		btn_help.SetPadX(210 * env.scale_width);

		net.SetUrl(env.server_url);

		core::Texture::Load("icon_0.png");
		core::Texture::Load("icon_1.png");
		core::Texture::Load("chip_red.png");

		background.SetMaterial(core::Material::Get("login_background"));
		form_background.SetMaterial(core::Material::Get("form_background"));

		core::Material* mat = core::Material::Create("chip_red", "gui_texture");
		mat->SetUniform("u_texture", core::UniformType::TEXTURE2D, core::Texture::Get("chip_red.png"));
		balance_icon.SetMaterial(mat);


		player_name.SetMaterial(core::Material::Get("btn_default"));
		player_balance.SetMaterial(core::Material::Get("btn_default"));

		btn_play.SetMaterial(core::Material::Get("btn_default"));
		btn_shop.SetMaterial(core::Material::Get("btn_default"));
		btn_help.SetMaterial(core::Material::Get("btn_default"));

		btn_play.SetHoverMaterial(core::Material::Get("btn_hover"));
		btn_shop.SetHoverMaterial(core::Material::Get("btn_hover"));
		btn_help.SetHoverMaterial(core::Material::Get("btn_hover"));

		btn_play.SetClickMaterial(core::Material::Get("btn_click"));
		btn_shop.SetClickMaterial(core::Material::Get("btn_click"));
		btn_help.SetClickMaterial(core::Material::Get("btn_click"));

		btn_play.SetOnClick(std::bind(&SceneMainMenu::PlayClicked, this));
	
	}

	void SceneMainMenu::Update(float delta) {
		if (current_user != env.username) {
			core::RequestData r;
			r.add("action", "get_user");
			r.add("username", env.username);
			std::string result = net.MakeRequest(r);
			result = result.substr(2);
			Split s(result);
			player_name.SetText(s.Get(0));
			player_balance.SetText(s.Get(1));

			core::Material* mat = core::Material::Create("player_icon", "gui_texture");
			mat->SetUniform("u_texture", core::UniformType::TEXTURE2D, core::Texture::Get("icon_" + s.Get(2) + ".png"));

			player_icon.SetMaterial(mat);
			current_user = env.username;
		}

		btn_play.Update();
		btn_shop.Update();
		btn_help.Update();
	}

	void SceneMainMenu::Draw() {
		btn_play.Draw(ui);
		btn_shop.Draw(ui);
		btn_help.Draw(ui);
		player_icon.Draw(ui);
		player_name.Draw(ui);
		balance_icon.Draw(ui);
		player_balance.Draw(ui);
		form_background.Draw(ui);
		background.Draw(ui);
		ui.Render();
	}

	void SceneMainMenu::PlayClicked() {
		env.state = 2;
	}


}