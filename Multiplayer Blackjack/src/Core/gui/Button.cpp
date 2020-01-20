#include <iostream>
#include "Core/Input.hpp"
#include "Button.h"

namespace Blackjack::Core {
	Button::Button(float x, float y, float width, float height, Material* default_material, Material* hover_material, Material* click_material) 
		: GuiElement(default_material, x,y,width,height), m_default(default_material), m_hover(hover_material), m_click(click_material), m_clicked(false), m_onClick(nullptr) {
	}

	Button::Button(float x, float y, float width, float height, Colour default_material, Colour hover_material, Colour click_material) 
		: GuiElement(default_material.material(), x, y, width, height), m_default(default_material.material()), m_hover(hover_material.material()), m_click(click_material.material()), m_clicked(false), m_onClick(nullptr) {
	
	}

	void Button::setOnClickFunc(CallbackFunc onClick) {
		m_onClick = onClick;
	}

	void Button::update() {
		if (Input::GetMouseX() >= m_x && Input::GetMouseX() <= m_x + m_width && Input::GetMouseY() >= m_y && Input::GetMouseY() <= m_y + m_height) {
			m_material = m_hover;
			if (Input::MouseDown(InputCode::MOUSE_LEFT)) {
				m_material = m_click;
				if (!m_clicked) {
					if (m_onClick != nullptr) {
						m_onClick();
					}
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