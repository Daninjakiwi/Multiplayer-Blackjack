#pragma once
#include "GuiElement.hpp"
#include <functional>
#include "Colour.hpp"
#include "Label.hpp"

namespace blackjack::core {
	class Button : public Label {
	public:
		//typedef void(*CallbackFunction)();

	private:
		Material* default_;
		Material* hover_;
		Material* click_;
		bool is_clicked_;

		//CallbackFunction on_click_;
		std::function<void()> on_click_;
	public:
		Button(float x, float y, float width, float height, const std::string& text, Font* font);

		void Update();

		void SetMaterial(const Colour colour);
		void SetMaterial(Material* material);
		void SetHoverMaterial(const Colour colour);
		void SetHoverMaterial(Material* material);
		void SetClickMaterial(const Colour colour);
		void SetClickMaterial(Material* material);

		//void SetOnClick(CallbackFunction function);
		void SetOnClick(std::function<void()> function);
	};
}
