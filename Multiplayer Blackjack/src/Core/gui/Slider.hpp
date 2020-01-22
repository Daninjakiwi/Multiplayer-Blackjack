#pragma once
#include "GuiElement.hpp"

namespace Blackjack::Core {
	class Slider2 : public GuiElement {
	private:
		GuiElement slider_;
		float min_, max_, current_;
		bool is_changing_;
	public:
		Slider2(float x, float y, float width, float height, float min=0, float max=100);

		void SetSliderMaterial(const Colour colour);
		void SetSliderMaterial(Material* material);

		void Update();
		void Draw(RendererUI& renderer);
	};
}