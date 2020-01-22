#pragma once
#include <vector>

#include "Core/Camera.hpp"
#include "Core/gui/GuiElement.hpp"
#include "Light.hpp"
#include "RenderObject.hpp"

namespace blackjack::core {
	class Renderer {
	protected:
		unsigned int va_, vb_, ib_;
		std::vector<float> vertices_;
		std::vector<unsigned int> indices_;
	public:
		Renderer();
		virtual ~Renderer();

		virtual void Bind() const = 0;

		virtual void Flush() = 0;
	};

	class Renderer3D : public Renderer {
	private:
		Light* light_;
		Camera* camera_;
		std::vector<RenderObject*> objects_;
	public:
		Renderer3D();

		void Bind() const;
		void Draw(RenderObject& object);
		void Flush();

		void SetLight(Light& light);
		void SetCamera(Camera& camera);
	};

	class RendererUI : public Renderer {
	private:
		glm::mat4 camera_;
		std::vector<GuiElement*> elements_;
	public:
		RendererUI(float width, float height);

		void Bind() const;
		void Flush();

		void Push(GuiElement* element);
		void Render();
	};
}
