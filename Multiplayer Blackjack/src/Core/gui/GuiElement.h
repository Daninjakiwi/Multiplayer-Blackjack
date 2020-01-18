#pragma once
#include "Core/Render/Meshes/Mesh.h"
#include "Core/Render/Material.h"

namespace Blackjack::Core {
	class GuiElement : public Mesh {
	protected:
		float m_x, m_y, m_width, m_height;
		Material* m_material;
	public:
		GuiElement(Material* material, float x, float y, float width, float height, unsigned int extra_vertices=0, unsigned int extra_indices=0);

		Material* getMaterial();
	};
}
