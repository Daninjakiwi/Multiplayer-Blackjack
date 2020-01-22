#pragma once

namespace blackjack::core {
	class Mesh {
		friend class RendererUI;
		friend class GuiElement;
	protected:
		float* vertices_;
		unsigned int* indices_;
		int vertex_count_;
		int indices_count_;
	public:
		Mesh(int vertex_count, int indices_count);
		virtual ~Mesh();

		int GetVertexCount() const;
		int GetIndicesCount() const;

		const float& GetVertexAt(int index) const;
		const unsigned int& GetIndexAt(int index) const;
		
		float* GetVertices();
		unsigned int* GetIndices();

		void ResizeVertices(int new_size);
		void ResizeIndices(int new_size);
	};
}