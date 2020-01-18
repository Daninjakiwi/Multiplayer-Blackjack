#pragma once
#include "Core/Render/Meshes/Mesh.h"
#include "GuiElement.h"
#include "Font.h"

namespace Blackjack::Core {

	class Text : public GuiElement {
	private:
		static Shader* m_text_shader;
		Material* m_material;
		std::vector<GuiElement*> m_text;
	public:
		Text(const std::string& text, float x, float y, float size, Font& font);

		~Text();

		std::vector<GuiElement*> getElements();
	};
}