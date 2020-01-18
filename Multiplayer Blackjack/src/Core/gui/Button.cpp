#include "Button.h"
#include "Core/Input.h"
#include <iostream>

namespace Blackjack::Core {
	Button::Button(float x, float y, float width, float height, Material* default_material, Material* hover_material, Material* click_material) 
		: GuiElement(default_material, x,y,width,height), m_default(default_material), m_hover(hover_material), m_click(click_material), m_clicked(false), m_onClick(nullptr) {
	}

	void Button::setOnClickFunc(CallbackFunc onClick) {
		m_onClick = onClick;
	}

	void Button::update() {
		if (Input::getMouseX() >= m_x && Input::getMouseX() <= m_x + m_width && Input::getMouseY() >= m_y && Input::getMouseY() <= m_y + m_height) {
			m_material = m_hover;
			if (Input::mouseDown(VOLT_MOUSE_LEFT)) {
				m_material = m_click;
				if (!m_clicked) {
					m_onClick();
					m_clicked = true;
				}
			}
			else {
				m_clicked = false;
			}

		}
		else {
			m_material = m_default;
		}
	}
}