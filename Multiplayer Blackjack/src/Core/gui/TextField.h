#pragma once
#include "GuiElement.h"
#include "Core/Input.h"
#include "Text.h"
#include <memory>

namespace Blackjack::Core {
	class TextField : public GuiElement {
	private:
		static TextField* m_current;
		static std::unique_ptr<GuiElement> m_cursor;

		std::string m_data;
		Text m_text;

		float m_pad_x, m_pad_y;

		int m_max_length;
		bool m_selected;
		int m_count;
	public:
		TextField(float x, float y, float width, float height, Material* background_material, Font& font, int font_size, int length, float pad_y=0, float pad_x=0);

		void update();

		static void proccessKey(unsigned int code);

		std::vector<GuiElement*> getElements();
	};
}