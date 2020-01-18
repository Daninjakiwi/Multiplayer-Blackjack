#pragma once
#include "GuiElement.h"

namespace Blackjack::Core {
	class Slider : public GuiElement {
	private:
		Material* m_back;
		Material* m_front;
		GuiElement m_slider;

		float m_min, m_max, m_current;
		bool m_change;
	public:
		Slider(float x, float y, float width, float height, Material* front, Material* back, float min=0, float max=100, float initial=0);

		void update();

		std::vector<GuiElement*> getElements();
	};
}