#include "GuiElement.h"

namespace Blackjack::Core {
	GuiElement::GuiElement(Material* material, float x, float y, float width, float height, unsigned int extra_vertices, unsigned int extra_indices) : Mesh(16+extra_vertices,6+extra_indices), m_material(material), m_x(x), m_y(y), m_width(width), m_height(height){
		m_vertices[0] = x;
		m_vertices[1] = y;
		m_vertices[2] = 0;
		m_vertices[3] = 0;

		m_vertices[4] = x+width;
		m_vertices[5] = y;
		m_vertices[6] = 1;
		m_vertices[7] = 0;

		m_vertices[8] = x + width;
		m_vertices[9] = y + height;
		m_vertices[10] = 1;
		m_vertices[11] = 1;

		m_vertices[12] = x;
		m_vertices[13] = y + height;
		m_vertices[14] = 0;
		m_vertices[15] = 1;

		m_indices[0] = 0;
		m_indices[1] = 1;
		m_indices[2] = 2;
		m_indices[3] = 2;
		m_indices[4] = 3;
		m_indices[5] = 0;

	}

	Material* GuiElement::getMaterial() {
		return m_material;
	}
}