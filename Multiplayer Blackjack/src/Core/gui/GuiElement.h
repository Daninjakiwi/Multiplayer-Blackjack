#pragma once
#include "Core/Render/Meshes/Mesh.h"
#include "Core/Render/Material.h"
#include <vector>

namespace Blackjack::Core {
	class GuiElement : public Mesh {
	protected:
		float m_x, m_y, m_width, m_height;
		Material* m_material;
	public:
		GuiElement(Material* material, float x, float y, float width, float height, unsigned int extra_vertices=0, unsigned int extra_indices=0);
		virtual ~GuiElement() = default;

		Material* material();

		virtual void update();

		void setWidth(float width);
		void setHeight(float height);
		void setX(float x);
		void setY(float y);

		void setTexCoords(float x, float y, int location);

		virtual std::vector<GuiElement*> getElements();
	};
}
