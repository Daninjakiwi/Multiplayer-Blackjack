#pragma once
#include "GuiElement.hpp"
#include "Font.hpp"

namespace blackjack::core {
	class Text : public GuiElement {
	private:
		std::string text_;
		std::string display_text_;
		Font* font_;
		float offset_;
		bool hidden_;
	public:
		friend class Label;
		Text(const float x, const float y,const std::string& text, Font* font, bool hidden=false);

		void SetText(const std::string& text);
		void Append(const std::string& text);
		void Append(char c);
		void Remove(int num_characters=1);

		void SetHidden(bool value);

		const std::string& GetText() const;

		virtual ~Text() = default;

		inline float GetOffset() { return offset_; };
		inline Font* GetFont() { return font_; };
	private:
		void CreateQuad(const int char_num, Character& character);
	};

	class Label : public GuiElement {
	protected:
		Text text_;
	public:
		Label(const float x, const float y, const float width, const float height, const std::string& text, Font* font, const Colour colour = {});

		virtual ~Label() = default;

		void Draw(RendererUI& renderer);

		void SetText(const std::string& text);

		void SetTextHidden(bool value);

		const std::string& GetText() const;
	};
}