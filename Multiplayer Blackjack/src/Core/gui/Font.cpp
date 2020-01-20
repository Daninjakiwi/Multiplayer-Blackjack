#include <fstream>
#include "Core/Log.hpp"
#include "Core/Resources.hpp"
#include "Font.h"

namespace Blackjack::Core {

	Font::Font(const std::string& filepath) : m_glyph(nullptr), m_name(filepath) {
		load(filepath);
	}

	Character& Font::getCharacter(char c) {
		return m_data[c];
	}

	Texture* Font::texture() {
		return m_glyph;
	}

	std::string& Font::getName() {
		return m_name;
	}

	float Font::getWidth() {
		return m_width;
	}

	float Font::getHeight() {
		return m_height;
	}

	float Font::getSize() {
		return m_size;
	}

	void Font::load(const std::string& filepath) {
		std::ifstream file(filepath);
		if (file.is_open()) {
			std::string line;

			getline(file, line);
			getline(file, line);

			m_size = std::stoi(line.substr(27, 4));
			m_width = std::stoi(line.substr(38, 4));
			m_height = std::stoi(line.substr(50, 4));

			getline(file, line);

			m_glyph = Resources::CreateTexture(filepath, "res/"+line.substr(16, line.length() - 17));

			getline(file, line);
			int num_characters = std::stoi(line.substr(12, 2));

			for (int i = 0; i < num_characters; i++) {
				getline(file, line);
				Character c;

				c.x = std::stoi(line.substr(18, 4));
				c.y = std::stoi(line.substr(25, 4));
				c.width = std::stoi(line.substr(36, 4));
				c.height = std::stoi(line.substr(48, 4));
				c.xoffset = std::stoi(line.substr(61, 4));
				c.yoffset = std::stoi(line.substr(74, 4));
				c.advance = std::stoi(line.substr(88, 4));

				int code = std::stoi(line.substr(8, 4));

				m_data[(char)code] = c;
			}

			file.close();
		}
	}
}