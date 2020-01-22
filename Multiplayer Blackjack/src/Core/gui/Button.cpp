#include <iostream>
#include "Core/Input.hpp"
#include "Button.hpp"

namespace blackjack::core {
	Button::Button(float x, float y, float width, float height, const std::string& text, Font* font) : Label(x,y,width,height, text,font), default_(nullptr), hover_(nullptr), click_(nullptr), is_clicked_(false), on_click_(nullptr) {
		SetMaterial({255,255,255});
		SetHoverMaterial({ 200,200,200 });
		SetClickMaterial({ 120,120,120 });
	}

	void Button::Update() {
		if (MouseIntersect()) {
			material_ = hover_;
			if (Input::MouseDown(InputCode::MOUSE_LEFT)) {
				material_ = click_;
				if (!is_clicked_) {
					if (on_click_ != nullptr) {
						on_click_();
					}
					is_clicked_ = true;
				}
			}
			else {
				is_clicked_ = false;
			}
		}
		else {
			material_ = default_;
		}
	}

	void Button::SetMaterial(const Colour colour) {
		default_ = Resources::CreateMaterial("gui_" + colour, Resources::GetShader("gui"));
		default_->SetUniform4f("u_colour", (float)colour.r / 255, (float)colour.g / 255, (float)colour.b / 255, (float)colour.a / 255);
	}
	void Button::SetMaterial(Material* material) {
		default_ = material;
	}
	void Button::SetHoverMaterial(const Colour colour) {
		hover_ = Resources::CreateMaterial("gui_" + colour, Resources::GetShader("gui"));
		hover_->SetUniform4f("u_colour", (float)colour.r / 255, (float)colour.g / 255, (float)colour.b / 255, (float)colour.a / 255);
	}

	void Button::SetHoverMaterial(Material* material) {
		hover_ = material;
	}

	void Button::SetClickMaterial(const Colour colour) {
		click_ = Resources::CreateMaterial("gui_" + colour, Resources::GetShader("gui"));
		click_->SetUniform4f("u_colour", (float)colour.r / 255, (float)colour.g / 255, (float)colour.b / 255, (float)colour.a / 255);
	}

	void Button::SetClickMaterial(Material* material) {
		click_ = material;
	}
	//void Button::SetOnClick(CallbackFunction function) {
	//	on_click_ = function;
	//}

	void Button::SetOnClick(std::function<void()> function) {
		on_click_ = function;
	}
}