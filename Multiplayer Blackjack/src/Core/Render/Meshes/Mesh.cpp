#include <memory>

#include "Core/Log.hpp"
#include "Mesh.h"

namespace Blackjack::Core {
	Mesh::Mesh(unsigned int vertex_count, unsigned int indices_count) : m_vertices(nullptr), m_indices(nullptr), m_vertex_count(vertex_count), m_indices_count(indices_count){
		m_vertices = (float*)malloc(vertex_count * sizeof(float));
		m_indices = (unsigned int*)malloc(indices_count * sizeof(unsigned int));
	}

	Mesh::~Mesh() {
		free(m_vertices);
		free(m_indices);
	}

	unsigned int Mesh::getVertexCount() const {
		return m_vertex_count;
	}

	unsigned int Mesh::getIndicesCount() const {
		return m_indices_count;
	}

	const float* Mesh::getVertexData() const {
		return m_vertices;
	}

	const unsigned int* Mesh::getIndicesData() const {
		return m_indices;
	}
}