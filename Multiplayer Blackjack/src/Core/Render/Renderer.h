#pragma once
#include <vector>
#include "Light.h"

#include "RenderObject.h"
#include "Core/Camera.hpp"
#include "Core/gui/GuiElement.h"

namespace Blackjack::Core {
	class Renderer {
	protected:
		unsigned int m_va, m_vb, m_ib;
		std::vector<float> m_vert;
		std::vector<unsigned int> m_index;
	public:
		Renderer();
		virtual ~Renderer();

		virtual void bind() const = 0;

		virtual void flush() = 0;
	};

	class Renderer3D : public Renderer {
	private:
		Light* m_light;
		Camera* m_camera;
		std::vector<RenderObject*> m_obj;
	public:
		Renderer3D();
		~Renderer3D() = default;

		void bind() const;
		void draw(RenderObject& object);
		void flush();

		void setLight(Light& light);
		void setCamera(Camera& camera);
	};

	class RendererUI : public Renderer {
	private:
		glm::mat4 m_camera;
		std::vector<GuiElement*> m_ui;
	public:
		RendererUI(float width, float height);
		~RendererUI() = default;

		void bind() const;
		void draw(GuiElement& object);
		void flush();
	};
}
