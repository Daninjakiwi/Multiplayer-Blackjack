#pragma once
#include "Core/Render/Meshes/Mesh.h"
#include "GuiElement.h"
#include "Font.h"
#include "Colour.h"

namespace Blackjack::Core {

	class Text : public GuiElement {
		friend class TextField;
	private:
		static Shader* m_text_shader;
		Material* m_material;
		Font* m_font;
		float m_size;
		float m_offset;
		std::vector<GuiElement*> m_text;
	public:
		Text(const std::string& text, float x, float y, float size, Font& font, float r=0, float g=0, float b=0);

		~Text();

		void setText(const std::string& text);
		void append(const std::string& text);
		void append(const char& text);

		void setTextColour(float r = 0, float g = 0, float b = 0);

		std::vector<GuiElement*> getElements();
	};
}