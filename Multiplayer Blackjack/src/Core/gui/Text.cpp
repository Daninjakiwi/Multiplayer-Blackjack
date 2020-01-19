#include "Text.h"
#include "Core/ResourceManager.h"
#include <iostream>

namespace Blackjack::Core {
	Shader* Text::m_text_shader = nullptr;

	void Text::setText(const std::string& text) {
		for (GuiElement* e : m_text) {
			delete e;
		}
		m_text.clear();
		if (m_text_shader == nullptr) {
			m_text_shader = ResourceManager::createShader("text_shader", "res/text");
		}
		m_material = ResourceManager::createMaterial("font_" + m_font->getName(), m_text_shader);
		m_material->setUniform("u_texture", UniformType::TEXTURE2D, m_font->getTexture());
		m_material->setUniform3f("u_colour", 1.0f, 1.0f, 1.0f);

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

	Text::Text(const std::string& text, float x, float y, float size, Font& font) : GuiElement(nullptr, x, y, 0, 0), m_material(nullptr), m_font(&font), m_size(size), m_offset(0) {
		if (m_text_shader == nullptr) {
			m_text_shader = ResourceManager::createShader("text_shader", "res/text");
		}
		m_material = ResourceManager::createMaterial("font_" + font.getName(), m_text_shader);
		m_material->setUniform("u_texture", UniformType::TEXTURE2D, font.getTexture());
		m_material->setUniform3f("u_colour", 0.0f, 0.0f, 0.0f);

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
	}

	std::vector<GuiElement*> Text::getElements() {
		return m_text;
	}
}