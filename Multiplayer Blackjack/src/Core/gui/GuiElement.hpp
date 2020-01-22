#pragma once
#include "Core/Render/Meshes/Mesh.h"
#include "Core/Render/Material.h"
#include "Colour.hpp"
#include <vector>
#include "Core/Render/Renderer.h"

namespace Blackjack::Core {
	class GuiElement : public Mesh {
	protected:
		float x_, y_, width_, height_;
		Material* material_;
	public:
		friend class RendererUI;
		GuiElement(const float x, const float y, const float width, const float height, const Colour colour = {});
		GuiElement(const float x, const float y, const float width, const float height, Material* material);

		virtual ~GuiElement() = default;

		void SetX(const float x);
		void SetY(const float y);
		void SetWidth(const float width);
		void SetHeight(const float height);

		bool MouseIntersect();

		Material* GetMaterial();

		virtual void SetMaterial(const Colour colour);
		virtual void SetMaterial(Material* material);
		virtual void Update();
		virtual void Draw(RendererUI& renderer);

	private:
		void Initialise();
	};


}
