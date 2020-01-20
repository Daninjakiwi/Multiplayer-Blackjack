#pragma once
#include <memory>
#include "Core/Input.hpp"
#include "GuiElement.h"
#include "Text.h"

namespace Blackjack::Core {
	class TextField : public GuiElement {
	private:
		static TextField* m_current;
		static std::unique_ptr<GuiElement> m_cursor;

		std::string m_data;
		Text m_text;

		float m_pad_x, m_pad_y;

		bool m_hidden;

		int m_max_length;
		bool m_selected;
		int m_count;
	public:
		TextField(float x, float y, float width, float height, Material* background_material, Font& font, int font_size, int length, bool hidden=false, float pad_y=0, float pad_x=0);

		void update();

		static void proccessKey(unsigned int code);

		std::string& getText();

		void setTextColour(float r=0, float g=0, float b = 0);

		std::vector<GuiElement*> getElements();
	};
}