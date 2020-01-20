#include "TextField.h"
#include "Colour.h"

namespace Blackjack::Core {
	TextField* TextField::m_current = nullptr;
	std::unique_ptr<GuiElement> TextField::m_cursor = nullptr;

	TextField::TextField(float x, float y, float width, float height, Material* background_material, Font& font, int font_size, int length, bool hidden, float pad_y,float pad_x) : GuiElement(background_material, x,y,width, height), m_text("", x + pad_x, y + pad_y, font_size, font), m_max_length(length), m_selected(false), m_count(0), m_pad_x(pad_x), m_pad_y(pad_y),m_hidden(hidden) {
		if (m_cursor == nullptr) {
			Colour c(0, 0, 0);
			m_cursor = std::make_unique<GuiElement>(c.material(), 0, 0, 10, 40);
		}
	}

	void TextField::update() {
		if (Input::GetMouseX() >= m_x && Input::GetMouseX() <= m_x + m_width && Input::GetMouseY() >= m_y && Input::GetMouseY() <= m_y + m_height) {
			if (Input::MouseDown(InputCode::MOUSE_LEFT)) {
				if (!m_selected) {
					Input::SetInputCallback(proccessKey);
					m_cursor.get()->setHeight(m_height * 0.6);
					m_cursor.get()->setX(m_x + m_pad_x + m_text.m_offset);
					m_cursor.get()->setY(m_y + (m_height*0.3));
					m_current = this;
					m_selected = true;
					m_count = 0;
				}
			}
		}
		else {
			if (Input::MouseDown(InputCode::MOUSE_LEFT)) {
				if (m_selected) {
					m_current = nullptr;
					m_selected = false;
					m_count = 0;
				}
			}
		}
		if (m_selected) {
			m_count += 1;
			if (m_count > 60) {
				m_count = 0;
			}
		}
	}

	void TextField::proccessKey(unsigned int code) {
		if (m_current != nullptr) {
			if (code == 14) {
				if (m_current->m_data.length() > 0) {
					m_current->m_data = m_current->m_data.substr(0, m_current->m_data.length() - 1);
					if (m_current->m_hidden) {
						std::string txt = "";
						for (int i = 0; i < m_current->m_data.length(); i++) {
							txt += "*";
						}
						m_current->m_text.setText(txt);
					}
					else {
						//m_current->m_text.append((char)code);
						m_current->m_text.setText(m_current->m_data);
					}					
					m_cursor.get()->setX(m_current->m_x + m_current->m_pad_x + m_current->m_text.m_offset);
					m_cursor.get()->setY(m_current->m_y + (m_current->m_height * 0.3));
				}
			}
			else {
				if (m_current->m_data.length() < m_current->m_max_length) {
					m_current->m_data += (char)code;
					if (m_current->m_hidden) {
						m_current->m_text.append("*");
					}
					else {
						m_current->m_text.append((char)code);
					}				
					m_cursor.get()->setX(m_current->m_x + m_current->m_pad_x + m_current->m_text.m_offset);
					m_cursor.get()->setY(m_current->m_y + (m_current->m_height * 0.3));
				}
			}
		}
	}

	std::string& TextField::getText() {
		return m_data;
	}

	void TextField::setTextColour(float r, float g, float b) {
		m_text.setTextColour(r, g, b);
	}

	std::vector<GuiElement*> TextField::getElements() {
		auto elements = m_text.getElements();
		if (m_selected) {
			if (m_count < 30) {
				elements.push_back(m_cursor.get());
			}
		}
		elements.push_back(this);
		return elements;
	}
}