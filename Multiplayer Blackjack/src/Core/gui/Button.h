#pragma once
#include "GuiElement.h"
#include <functional>
#include "Colour.h"

namespace Blackjack::Core {
	class Button : public GuiElement {
	public:
		typedef void (*CallbackFunc)();
	private:
		Material* m_default;
		Material* m_hover;
		Material* m_click;

		bool m_clicked;

		CallbackFunc m_onClick;
	public:
		Button(float x, float y, float width, float height, Material* default_material, Material* hover_material, Material* click_material);
		Button(float x, float y, float width, float height, Colour default_material, Colour hover_material, Colour click_material);


		void setOnClickFunc(CallbackFunc onClick);

		void update();
	};
}
