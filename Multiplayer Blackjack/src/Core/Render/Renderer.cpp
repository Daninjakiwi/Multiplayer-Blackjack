#include "Renderer.h"
#include "glad/glad.h"
#include "Core/Log.h"

namespace Core {
	Renderer::Renderer() : m_va(0), m_vb(0), m_ib(0){
		glGenVertexArrays(1, &m_va);
		glGenBuffers(1, &m_vb);
		glGenBuffers(1, &m_ib);
	}

	Renderer::~Renderer() {
		glDeleteVertexArrays(1, &m_va);
		glDeleteBuffers(1, &m_vb);
		glDeleteBuffers(1, &m_ib);
	}

	Renderer3D::Renderer3D() : Renderer() {
	}

	void Renderer3D::bind() const {
		glBindVertexArray(m_va);

		glBindBuffer(GL_ARRAY_BUFFER, m_vb);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);


		glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), nullptr);

		glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (const void*)12);

		glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (const void*)24);

	}

	void Renderer3D::draw(RenderObject& object) {
		Mesh* mesh = object.getMesh();
		for (int i = 0; i < mesh->getIndicesCount(); i++) {
			m_index.push_back(mesh->getIndicesData()[i] + (m_vert.size() / 8));
		}

		for (int i = 0; i < mesh->getVertexCount(); i++) {
			m_vert.push_back(mesh->getVertexData()[i]);
		}
	}

	void Renderer3D::flush() {
		glBufferData(GL_ARRAY_BUFFER, m_vert.size() * sizeof(float), &m_vert[0], GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index.size() * sizeof(unsigned int), &m_index[0], GL_STATIC_DRAW);

		glDrawElements(GL_TRIANGLES, m_index.size(), GL_UNSIGNED_INT, nullptr);


		m_vert.clear();
		m_index.clear();
	}
}