#include <fstream>
#include <sstream>
#include "Core/Log.hpp"
#include "Font.hpp"

namespace blackjack::core {
	std::unordered_map<std::string, std::unique_ptr<FontData>> Font::fonts_;

	FontData::FontData(const std::string& font_name) : texture(nullptr), base_size(0), name(font_name) {
		std::ifstream file(FONT_PATH + font_name + ".fnt");
		if (file.is_open()) {
			std::string line;

			getline(file, line);
			getline(file, line);

			base_size = std::stoi(line.substr(27, 4));

			getline(file, line);

			std::string t = FONT_PATH + line.substr(16, line.length() - 17);

			texture = Resources::CreateTexture(font_name, t);

			getline(file, line);
			int num_characters = std::stoi(line.substr(12, 2));

			for (int i = 0; i < num_characters; i++) {
				getline(file, line);
				Character c;

				c.x = (float)(std::stoi(line.substr(18, 4))) / texture->GetWidth();
				c.y =  1.0f - ((float)(std::stoi(line.substr(25, 4))) / texture->GetHeight());
				c.wratio = (float)(std::stoi(line.substr(36, 4))) / texture->GetWidth();
				c.hratio = (float)(std::stoi(line.substr(48, 4))) / texture->GetHeight();
				c.width = (float)std::stoi(line.substr(36, 4));
				c.height = (float)std::stoi(line.substr(48, 4));
				c.xoffset = (float)std::stoi(line.substr(61, 4));
				c.yoffset = (float)std::stoi(line.substr(74, 4));
				c.advance = (float)std::stoi(line.substr(88, 4));

				//int code = ;

				characters[(char)std::stoi(line.substr(8, 4))] = c;
			}

			file.close();
		}
	}


	void Font::Load(const std::string& font_name) {
		FontData f2(font_name);

		if (f2.texture != nullptr) {
			fonts_[font_name] = std::make_unique<FontData>(f2);
		}

	}

	Font Font::Get(const std::string& font_name, const int size) {
		FontData* f = fonts_[font_name].get();
		if (f == nullptr) {
			f = fonts_["Monospaced"].get();
		}
		Colour c(0,0,0);
		return { f,size,c };
	}

	Font Font::Get(const std::string& font_name, const int size, const Colour colour) {
		FontData* f = fonts_[font_name].get();
		if (f == nullptr) {
			f = fonts_["Monospaced"].get();
		}
		return { f,size,colour };
	}

	std::string operator+(const std::string& str, int i) {
		std::stringstream ss;
		ss << i;
		return str + ss.str();
	}

	Font::Font(FontData* font, int size, const Colour colour) : font_(font), size_(size), material_(nullptr) {
		std::string name = font->name + "_" + size + "_" + colour;
		material_ = Resources::CreateMaterial(name, Resources::GetShader("text"));
		material_->SetUniform("u_texture", UniformType::TEXTURE2D, font->texture);
		material_->SetUniform3f("u_colour", colour.r, colour.g, colour.b);
	}

	Material* Font::GetMaterial() const {
		return material_;
	}

	const float Font::GetScale() const {
		return (float)size_ / font_->base_size;
	}

	FontData* Font::GetBaseFont() const {
		return font_;
	}

	const int Font::GetSize() const {
		return size_;
	}

	Character operator*(const float scale, Character& character) {
		character.xoffset *= scale;
		character.yoffset *= scale;
		character.width *= scale;
		character.height *= scale;
		character.advance *= scale;
		return character;
	}
}