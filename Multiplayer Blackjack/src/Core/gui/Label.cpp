#include "Label.hpp"
#include "Core/Log.hpp"

namespace blackjack::core {
	Text::Text(const float x, const float y, const std::string& text, Font* font, bool hidden) : GuiElement(x,y,100,100, font->GetMaterial()),text_(text), display_text_() ,font_(font), offset_(0), hidden_(hidden) {
		SetText(text);
	}

	void Text::SetText(const std::string& text) {
		offset_ = 0;
		text_ = text;
		if (hidden_) {
			display_text_ = "";
			for (int i = 0; i < text.length(); i++) {
				display_text_ += '*';
			}
		}
		else {
			display_text_ = text_;
		}


		ResizeVertices(display_text_.length() * 16);
		ResizeIndices(display_text_.length() * 6);

		float ratio = font_->GetScale();

		for (int i = 0; i < display_text_.length(); i++) {
			char c;
			if (hidden_) {
				c = '*';
			}
			else {
				c = display_text_.at(i);
			}

			if (c == ' ') {
				offset_ += 80 * ratio;
			}
			else {
				Character ch = font_->GetBaseFont()->characters[c];
				CreateQuad(i, ch);
				offset_ += ch.advance;
			}
		}
	}
	void Text::Append(const std::string& text) {
		text_ += text;
		if (hidden_) {
			for (int i = 0; i < text.length(); i++) {
				display_text_ += '*';
			}
		}
		else {
			display_text_ = text_;
		}


		ResizeVertices(text_.length() * 16);
		ResizeIndices(text_.length() * 6);

		float ratio = font_->GetScale();
		for (int i = display_text_.length() - text.length(); i < display_text_.length(); i++) {
			char c;
			if (hidden_) {
				c = '*';
			}
			else {
				c = display_text_.at(i);
			}
			if (c == ' ') {
				offset_ += 80 * ratio;
			}
			else {
				Character ch = font_->GetBaseFont()->characters[c];
				CreateQuad(i, ch);
				offset_ += ch.advance;
			}
		}
	}
	void Text::Append(char c) {
		text_ += c;
		if (hidden_) {
			c = '*';
		}
		display_text_ += c;

		ResizeVertices(text_.length() * 16);
		ResizeIndices(text_.length() * 6);

		float ratio = font_->GetScale();
		if (c == ' ') {
			offset_ += 80 * ratio;
		}
		else {
			Character ch = font_->GetBaseFont()->characters[c];
			CreateQuad(text_.length() - 1, ch);
			offset_ += ch.advance;
		}
	}
	void Text::Remove(int num_characters) {
		int val = text_.length() - 1;
		int val2 = text_.length() - num_characters - 1;
		for (int i = val; i > val2; i--) {
			char c;
			if (hidden_) {
				c = '*';
			}
			else {
				c = display_text_.at(i);
			}
			if (c == ' ') {
				offset_ -= 80 * font_->GetScale();
			}
			else {
				Character ch = font_->GetBaseFont()->characters[c];
				ch = font_->GetScale() * ch;
				offset_ -= ch.advance;
			}

		}
		text_ = text_.substr(0, text_.length() - num_characters);
		display_text_ = display_text_.substr(0, display_text_.length() - num_characters);
		ResizeVertices(text_.length() * 16);
		ResizeIndices(text_.length() * 6);
	}

	void Text::CreateQuad(const int char_num, Character& character) {

		vertices_[2 + (16 * char_num)] = character.x;
		vertices_[3 + (16 * char_num)] = character.y ;
		vertices_[6 + (16 * char_num)] = character.x + character.wratio;
		vertices_[7 + (16 * char_num)] = character.y;
		vertices_[10 + (16 * char_num)] = character.x + character.wratio;
		vertices_[11 + (16 * char_num)] = character.y - character.hratio;
		vertices_[14 + (16 * char_num)] = character.x;
		vertices_[15 + (16 * char_num)] = character.y - character.hratio;

		character = font_->GetScale() * character;

		vertices_[16 * char_num] = x_ + offset_ + character.xoffset;
		vertices_[1 + (16 * char_num)] = y_ + character.yoffset;
		vertices_[4+(16 * char_num)] = x_ + offset_ + character.xoffset + character.width;
		vertices_[5+(16 * char_num)] = y_ + character.yoffset;
		vertices_[8+(16 * char_num)] = x_ + offset_ + character.xoffset + character.width;
		vertices_[9+(16 * char_num)] = y_ + character.yoffset + character.height;
		vertices_[12+(16 * char_num)] = x_ + offset_ + character.xoffset;
		vertices_[13+(16 * char_num)] = y_ + character.yoffset + character.height;


		indices_[6*char_num] = (4*char_num);
		indices_[1+(6*char_num)] = 1+ (4 * char_num);
		indices_[2+(6 * char_num)] = 2 + (4 * char_num);
		indices_[3+(6 * char_num)] = 2 + (4 * char_num);
		indices_[4+(6 * char_num)] = 3 + (4 * char_num);
		indices_[5+(6 * char_num)] = (4 * char_num);
	}

	const std::string& Text::GetText() const {
		return text_;
	}

	void Text::SetHidden(bool value) {
		if (value != hidden_) {
			hidden_ = value;
			SetText(text_);
		}
	}

	Label::Label(const float x, const float y, const float width, const float height, const std::string& text, Font* font, const Colour colour) : GuiElement(x, y, width, height, colour), text_(x + (width/5), y + ((height - font->GetSize()) / 2) - (font->GetSize()/5),  text, font) {

	}

	void Label::Draw(RendererUI& renderer) {
		renderer.Push(&text_);
		renderer.Push(this);
	}

	void Label::SetTextHidden(bool value) {
		text_.SetHidden(value);
	}

	void Label::SetText(const std::string& text) {
		text_.SetText(text);
	}

	const std::string& Label::GetText() const {
		return text_.text_;
	}
}