#pragma once

namespace Core {
	class Mesh {
	protected:
		float* m_vertices;
		unsigned int* m_indices;
		unsigned int m_vertex_count;
		unsigned int m_indices_count;
	public:
		Mesh(unsigned int vertex_count, unsigned int indices_count);
		virtual ~Mesh();

		unsigned int getVertexCount() const;
		unsigned int getIndicesCount() const;

		const float* getVertexData() const;
		const unsigned int* getIndicesData() const;
	};
}