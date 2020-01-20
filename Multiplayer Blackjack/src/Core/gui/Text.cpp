#include "Text.h"
#include "Core/Resources.hpp"
#include <iostream>

namespace Blackjack::Core {
	Shader* Text::m_text_shader = nullptr;

	void Text::setTextColour(float r, float g, float b) {
		m_material->setUniform3f("u_colour", r/255, g/255, b/255);
	}

	void Text::setText(const std::string& text) {
		for (GuiElement* e : m_text) {
			delete e;
		}
		m_text.clear();

		float scale = m_size / m_font->getSize();

		int offset = 0;
		for (int i = 0; i < text.length(); i++) {
			char c = text.at(i);
			if (c == ' ') {
				offset += 80 * scale;
			}
			else {
				Character character = m_font->getCharacter(c);
				GuiElement* element = new GuiElement(m_material, m_x + offset + (character.xoffset * scale), m_y + (character.yoffset * scale), character.width * scale, character.height * scale);
				m_text.push_back(element);
				offset += (character.width + character.xoffset) * scale;

				element->setTexCoords(character.x / m_font->getWidth(), (m_font->getHeight() - (character.y + character.height)) / m_font->getHeight(), 3);

				element->setTexCoords((character.x + character.width) / m_font->getWidth(), (m_font->getHeight() - (character.y + character.height)) / m_font->getHeight(), 2);

				element->setTexCoords((character.x + character.width) / m_font->getWidth(), (m_font->getHeight() - character.y) / m_font->getHeight(), 1);

				element->setTexCoords(character.x / m_font->getWidth(), (m_font->getHeight() - character.y) / m_font->getHeight(), 0);
			}
		}
		m_offset = offset;
	}

	Text::Text(const std::string& text, float x, float y, float size, Font& font, float r, float g, float b) : GuiElement(nullptr, x, y, 0, 0), m_material(nullptr), m_font(&font), m_size(size), m_offset(0) {
		if (m_text_shader == nullptr) {
			m_text_shader = Resources::CreateShader("text_shader", "res/text");
		}
		m_material = Resources::CreateMaterial("font_" + font.getName(), m_text_shader);
		m_material->setUniform("u_texture", UniformType::TEXTURE2D, font.texture());
		m_material->setUniform3f("u_colour", r/255,g/255,b/255);

		float scale = size / font.getSize();

		int offset = 0;
		for (int i = 0; i < text.length(); i++) {
			char c = text.at(i);
			if (c == ' ') {
				offset += 80 * scale;
			}
			else {
				Character character = font.getCharacter(c);
				GuiElement* element = new GuiElement(m_material, x + offset + (character.xoffset*scale), y + (character.yoffset*scale), character.width * scale, character.height * scale);
				m_text.push_back(element);
				offset += (character.width+character.xoffset) * scale;

				element->setTexCoords(character.x / font.getWidth(), (font.getHeight() - (character.y + character.height)) / font.getHeight(), 3);

				element->setTexCoords((character.x + character.width) / font.getWidth(), (font.getHeight() - (character.y + character.height)) / font.getHeight(), 2);

				element->setTexCoords((character.x + character.width) / font.getWidth(), (font.getHeight() - character.y) / font.getHeight(), 1);

				element->setTexCoords(character.x / font.getWidth(), (font.getHeight() - character.y) / font.getHeight(), 0);
			}
		}

		m_offset = offset;
	}

	Text::~Text() {
		for (GuiElement* e : m_text) {
			delete e;
		}
		m_text.clear();
	}

	std::vector<GuiElement*> Text::getElements() {
		return m_text;
	}

	void Text::append(const char& text) {
		float scale = m_size / m_font->getSize();
		int offset = m_offset;
		if (text == ' ') {
			offset += 80 * scale;
		}
		else {
			Character character = m_font->getCharacter(text);
			GuiElement* element = new GuiElement(m_material, m_x + offset + (character.xoffset * scale), m_y + (character.yoffset * scale), character.width * scale, character.height * scale);
			m_text.push_back(element);
			offset += (character.width + character.xoffset) * scale;

			element->setTexCoords(character.x / m_font->getWidth(), (m_font->getHeight() - (character.y + character.height)) / m_font->getHeight(), 3);

			element->setTexCoords((character.x + character.width) / m_font->getWidth(), (m_font->getHeight() - (character.y + character.height)) / m_font->getHeight(), 2);

			element->setTexCoords((character.x + character.width) / m_font->getWidth(), (m_font->getHeight() - character.y) / m_font->getHeight(), 1);

			element->setTexCoords(character.x / m_font->getWidth(), (m_font->getHeight() - character.y) / m_font->getHeight(), 0);
		}
		m_offset = offset;

	}

	void Text::append(const std::string& text) {
		float scale = m_size / m_font->getSize();
		int offset = m_offset;
		for (int i = 0; i < text.length(); i++) {
			char c = text.at(i);
			if (c == ' ') {
				offset += 80 * scale;
			}
			else {
				Character character = m_font->getCharacter(c);
				GuiElement* element = new GuiElement(m_material, m_x + offset + (character.xoffset * scale), m_y + (character.yoffset * scale), character.width * scale, character.height * scale);
				m_text.push_back(element);
				offset += (character.width + character.xoffset) * scale;

				element->setTexCoords(character.x / m_font->getWidth(), (m_font->getHeight() - (character.y + character.height)) / m_font->getHeight(), 3);

				element->setTexCoords((character.x + character.width) / m_font->getWidth(), (m_font->getHeight() - (character.y + character.height)) / m_font->getHeight(), 2);

				element->setTexCoords((character.x + character.width) / m_font->getWidth(), (m_font->getHeight() - character.y) / m_font->getHeight(), 1);

				element->setTexCoords(character.x / m_font->getWidth(), (m_font->getHeight() - character.y) / m_font->getHeight(), 0);
			}
		}
		m_offset = offset;
	}
}