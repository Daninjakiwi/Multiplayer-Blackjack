#include <algorithm> 
#include <iostream>
#include "Core/Input.hpp"
#include "Slider.hpp"

namespace blackjack::core {
	Slider2::Slider2(float x, float y, float width, float height, float min, float max) : GuiElement(x, y, width, height), slider_(x, y, 0, height, { 60,60,60 }), min_(min), max_(max), current_(0.0f), is_changing_(false) {

	}

	void Slider2::SetSliderMaterial(const Colour colour) {
		slider_.SetMaterial(colour);
	}
	void Slider2::SetSliderMaterial(Material* material) {
		slider_.SetMaterial(material);
	}

	void Slider2::Update() {
		if (Input::MouseDown(InputCode::MOUSE_LEFT)) {
			if (is_changing_ || MouseIntersect()) {
				is_changing_ = true;
				current_ = std::max(min_, std::min(max_, ((Input::GetMouseX() - x_) / width_) * max_));
				slider_.SetWidth((current_ * width_) / max_);
			}
		}
		else {
			is_changing_ = false;
		}
	}

	void Slider2::Draw(RendererUI& renderer) {
		slider_.Draw(renderer);
		renderer.Push(this);
	}


}