#pragma once
#include <string>
#include <unordered_map>
#include "Core/Render/Texture.h"
#include "Colour.hpp"

namespace Blackjack::Core {
	struct Character {
		float x, y, width, height, xoffset, yoffset, advance, wratio,hratio;
	};

	struct FontData {
		std::unordered_map<char, Character> characters;
		Texture* texture;
		int base_size;
		std::string name;

		FontData(const std::string& font_name);
	};

	class Font {
	private:
		static std::unordered_map<std::string, std::unique_ptr<FontData>> fonts_;

		FontData* font_;
		int size_;
		Material* material_;
	public:
		static void Load(const std::string& font_name);
		static Font Get(const std::string& font_name, const int size, const Colour colour);
		static Font Get(const std::string& font_name, const int size);

		Material* GetMaterial() const;
		const float GetScale() const;
		FontData* GetBaseFont() const;
		const int GetSize() const;
	private:
		Font(FontData* font, int size, const Colour colour);
	};

	Character operator*(const float scale, Character& character);
}