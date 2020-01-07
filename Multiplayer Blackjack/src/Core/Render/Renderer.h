#pragma once
#include <vector>

#include "RenderObject.h"

namespace Core {
	class Renderer {
	protected:
		unsigned int m_va, m_vb, m_ib;
		std::vector<float> m_vert;
		std::vector<unsigned int> m_index;
	public:
		Renderer();
		virtual ~Renderer();

		virtual void bind() const = 0;

		virtual void draw(RenderObject& object) = 0;

		virtual void flush() = 0;
	};

	class Renderer2D : public Renderer {
	public:
		Renderer2D();
		~Renderer2D() = default;

		void bind() const;
		void draw(RenderObject& object);
		void flush();
	};

	class Renderer3D : public Renderer {
	public:
		Renderer3D();
		~Renderer3D() = default;

		void bind() const;
		void draw(RenderObject& object);
		void flush();
	};
}
