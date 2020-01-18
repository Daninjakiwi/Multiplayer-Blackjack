#pragma once
#include <string>
#include "Core/Render/Texture.h"
#include <unordered_map>

namespace Blackjack::Core {
	struct Character {
		float x, y, width, height, xoffset, yoffset, advance;
	};
	
	class Font {
	private:
		Texture* m_glyph;
		std::string m_name;
		float m_width, m_height;
		float m_size;
		std::unordered_map<char, Character> m_data;
	public:
		Font(const std::string& filepath);

		void load(const std::string& filepath);
		Character& getCharacter(char c);

		Texture* getTexture();

		std::string& getName();

		float getWidth();
		float getHeight();
		float getSize();
	};
}