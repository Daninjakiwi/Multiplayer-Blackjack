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

	Renderer2D::Renderer2D() : Renderer() {

	}

	void Renderer2D::bind() const {
		glBindVertexArray(m_va);
		glBindBuffer(GL_ARRAY_BUFFER, m_vb);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), nullptr);
	}

	void Renderer2D::draw(RenderObject& object) {
		Mesh* mesh = object.getMesh();
		for (int i = 0; i < mesh->getIndicesCount(); i++) {
			m_index.push_back(mesh->getIndicesData()[i] + (m_vert.size() / 2));
		}

		for (int i = 0; i < mesh->getVertexCount(); i++) {
			m_vert.push_back(mesh->getVertexData()[i]);
		}
	}

	void Renderer2D::flush() {
		glBufferData(GL_ARRAY_BUFFER, m_vert.size() * sizeof(float), &m_vert[0], GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index.size() * sizeof(unsigned int), &m_index[0], GL_STATIC_DRAW);

		glDrawElements(GL_TRIANGLES, m_index.size(), GL_UNSIGNED_INT, nullptr);

		m_vert.clear();
		m_index.clear();
	}

	Renderer3D::Renderer3D() : Renderer() {

	}

	void Renderer3D::bind() const {
		glBindVertexArray(m_va);
		glBindBuffer(GL_ARRAY_BUFFER, m_vb);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);
	}

	void Renderer3D::draw(RenderObject& object) {
		Mesh* mesh = object.getMesh();
		for (int i = 0; i < mesh->getIndicesCount(); i++) {
			m_index.push_back(mesh->getIndicesData()[i] + (m_vert.size() / 3));
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