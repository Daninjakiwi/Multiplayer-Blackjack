#include "Slider.h"
#include "Core/Input.h"
#include <algorithm> 
#include <iostream>

namespace Blackjack::Core {
	Slider::Slider(float x, float y, float width, float height, Material* front, Material* back, float min, float max, float initial) 
	: GuiElement(back, x,y,width,height), m_back(back), m_front(front), m_slider(front, x,y,width/2, height), m_min(min), m_max(max), m_current(initial), m_change(false) {

	}

	void Slider::update() {
		if (Input::mouseDown(VOLT_MOUSE_LEFT)) {
			if (m_change || (Input::getMouseX() >= m_x && Input::getMouseX() <= m_x + m_width && Input::getMouseY() >= m_y && Input::getMouseY() <= m_y + m_height)) {
				m_change = true;
				m_current = std::max(m_min, std::min(m_max, ((Input::getMouseX() - m_x) / m_width) * m_max));
				m_slider.setWidth((m_current * m_width) / m_max);
			}
		}
		else {
			m_change = false;
		}

	}

	std::vector<GuiElement*> Slider::getElements() {
		std::vector<GuiElement*> elements;
		elements.push_back(&m_slider);
		elements.push_back(this);



		return elements;
	}


}