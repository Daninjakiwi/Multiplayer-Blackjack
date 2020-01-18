#include "Renderer.h"
#include "glad/glad.h"
#include "Core/Log.h"

namespace Blackjack::Core {
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

	Renderer3D::Renderer3D() : Renderer(), m_light(nullptr), m_camera(nullptr) {
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

		m_obj.push_back(&object);
	}

	void Renderer3D::flush() {

		if (m_obj.size() > 0) {
			bind();
			glBufferData(GL_ARRAY_BUFFER, m_vert.size() * sizeof(float), &m_vert[0], GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index.size() * sizeof(unsigned int), &m_index[0], GL_STATIC_DRAW);

			unsigned int* start = nullptr;

			for (RenderObject* r : m_obj) {
				r->m_material->m_shader->bind();

				r->m_material->setUniform("u_light.ambient", UniformType::FVEC3, &m_light->m_ambient.x);
				r->m_material->setUniform("u_light.diffuse", UniformType::FVEC3, &m_light->m_diffuse.x);
				r->m_material->setUniform("u_light.specular", UniformType::FVEC3, &m_light->m_specular.x);
				r->m_material->setUniform("u_light.position", UniformType::FVEC3, &m_light->m_position.x);

				r->m_material->setUniform("u_view_pos", UniformType::FVEC3, &m_camera->m_position.x);
				r->m_material->setUniform("u_camera", UniformType::MAT4, m_camera->getView());

				r->m_material->setUniform("u_transform", UniformType::MAT4, r->m_transform.getMatrix());

				r->m_material->bind();

				glDrawElements(GL_TRIANGLES, r->m_mesh->getIndicesCount(), GL_UNSIGNED_INT, start);
				start += r->m_mesh->getIndicesCount();
			}
			m_obj.clear();
			m_vert.clear();
			m_index.clear();

		}

	}

	void Renderer3D::setLight(Light& light) {
		m_light = &light;
	}

	void Renderer3D::setCamera(Camera& camera) {
		m_camera = &camera;
	}


	//-------------------------------------------------------------------
	//-------------------------------------------------------------------
	//-------------------------------------------------------------------
	//-------------------------------------------------------------------

	RendererUI::RendererUI(float width, float height) : Renderer(), m_camera(glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f)) {

	}

	void RendererUI::bind() const {
		glBindVertexArray(m_va);

		glBindBuffer(GL_ARRAY_BUFFER, m_vb);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);


		glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), nullptr);

		glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (const void*)8);
	}

	void RendererUI::draw(GuiElement& object) {
		std::vector<GuiElement*> elements = object.getElements();

		for (GuiElement* element : elements) {
			for (int i = 0; i < element->getIndicesCount(); i++) {
				m_index.push_back(element->getIndicesData()[i] + (m_vert.size() / 4));
			}

			for (int i = 0; i < element->getVertexCount(); i++) {
				m_vert.push_back(element->getVertexData()[i]);
			}

			m_ui.push_back(element);

		}

		//m_ui.push_back(&object);
	}

	void RendererUI::flush() {
		if (m_ui.size() > 0) {
			bind();

			glBufferData(GL_ARRAY_BUFFER, m_vert.size() * sizeof(float), &m_vert[0], GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index.size() * sizeof(unsigned int), &m_index[0], GL_STATIC_DRAW);

			unsigned int* start = nullptr;

			for (GuiElement* r : m_ui) {

				r->getMaterial()->getShader()->bind();

				r->getMaterial()->setUniform("u_camera", UniformType::MAT4, &m_camera[0][0]);
				r->getMaterial()->bind();

				glDrawElements(GL_TRIANGLES, r->getIndicesCount(), GL_UNSIGNED_INT, start);
				start += r->getIndicesCount();
			}
			m_ui.clear();
			m_vert.clear();
			m_index.clear();
		}
	}
}