#pragma once
#include "Core/Render/Meshes/Mesh.hpp"
#include "Core/Render/Material.hpp"
#include "Colour.hpp"
#include <vector>
#include "Core/Render/Renderer.hpp"

namespace blackjack::core {
	class GuiElement : public Mesh {
	protected:
		float x_, y_, width_, height_;
		Material* material_;
		bool draw_;
	public:
		friend class RendererUI;
		GuiElement(const float x, const float y, const float width, const float height, const Colour colour = {});
		GuiElement(const float x, const float y, const float width, const float height, Material* material);

		virtual ~GuiElement() = default;

		virtual void SetX(const float x);
		virtual void SetY(const float y);
		void SetWidth(const float width);
		void SetHeight(const float height);

		void Show();
		void Hide();

		const float GetX() const;
		const float GetY() const;
		const float GetWidth() const;
		const float GetHeight() const;

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
