#include "glad/glad.h"

#include "Renderer.hpp"

namespace blackjack::core {
	Renderer::Renderer() : va_(0), vb_(0), ib_(0){
		glGenVertexArrays(1, &va_);
		glGenBuffers(1, &vb_);
		glGenBuffers(1, &ib_);
	}

	Renderer::~Renderer() {
		glDeleteVertexArrays(1, &va_);
		glDeleteBuffers(1, &vb_);
		glDeleteBuffers(1, &ib_);
	}

	Renderer3D::Renderer3D() : Renderer(), light_(nullptr), camera_(nullptr) {
	}

	void Renderer3D::Bind() const {
		glBindVertexArray(va_);

		glBindBuffer(GL_ARRAY_BUFFER, vb_);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), nullptr);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (const void*)12);
		glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (const void*)24);
	}

	void Renderer3D::Draw(RenderObject& object) {
		Mesh* mesh = object.GetMesh();
		indices_.reserve(indices_.size() + mesh->GetIndicesCount());
		for (int i = 0; i < mesh->GetIndicesCount(); i++) {
			indices_.push_back(mesh->GetIndexAt(i) + ((int)vertices_.size() / 8));
		}

		vertices_.reserve(vertices_.size() + mesh->GetVertexCount());
		for (int i = 0; i < mesh->GetVertexCount(); i++) {
			vertices_.push_back(mesh->GetVertexAt(i));
		}

		objects_.push_back(&object);
	}

	void Renderer3D::Flush() {

		if (objects_.size() > 0) {
			Bind();
			glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), &vertices_[0], GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);

			unsigned int* start = nullptr;

			for (RenderObject* r : objects_) {
				r->material_->shader_->Bind();

				r->material_->SetUniform("u_light.ambient", UniformType::FVEC3, &light_->ambient_.x);
				r->material_->SetUniform("u_light.diffuse", UniformType::FVEC3, &light_->diffuse_.x);
				r->material_->SetUniform("u_light.specular", UniformType::FVEC3, &light_->specular_.x);
				r->material_->SetUniform("u_light.position", UniformType::FVEC3, &light_->position_.x);

				r->material_->SetUniform("u_view_pos", UniformType::FVEC3, &camera_->position_.x);
				r->material_->SetUniform("u_camera", UniformType::MAT4, camera_->GetView());

				r->material_->SetUniform("u_transform", UniformType::MAT4, r->transform_.GetMatrix());

				r->material_->Bind();

				glDrawElements(GL_TRIANGLES, r->mesh_->GetIndicesCount(), GL_UNSIGNED_INT, start);
				start += r->mesh_->GetIndicesCount();
			}
			objects_.clear();
			vertices_.clear();
			indices_.clear();

		}

	}

	void Renderer3D::SetLight(Light& light) {
		light_ = &light;
	}

	void Renderer3D::SetCamera(Camera& camera) {
		camera_ = &camera;
	}


	//-------------------------------------------------------------------
	//-------------------------------------------------------------------
	//-------------------------------------------------------------------
	//-------------------------------------------------------------------

	RendererUI::RendererUI(float width, float height) : Renderer(), camera_(glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f)) {

	}

	void RendererUI::Bind() const {
		glBindVertexArray(va_);

		glBindBuffer(GL_ARRAY_BUFFER, vb_);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), nullptr);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (const void*)8);
	}


	void RendererUI::Push(GuiElement* element) {
		indices_.reserve(indices_.size() + element->GetIndicesCount());
		for (int i = 0; i < element->GetIndicesCount(); i++) {
			indices_.push_back(element->GetIndexAt(i) + ((int)vertices_.size() / 4));
		}

		vertices_.reserve(vertices_.size() + element->GetVertexCount());
		for (int i = 0; i < element->GetVertexCount(); i++) {
			vertices_.push_back(element->GetVertexAt(i));
		}

		elements_.push_back(element);
	}

	void RendererUI::Render() {
		if (elements_.size() > 0) {
			Bind();

			glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), &vertices_[0], GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);
			unsigned int* start = nullptr;
			for (auto element : elements_) {
				element->material_->GetShader()->Bind();
				element->material_->SetUniform("u_camera", UniformType::MAT4, &camera_[0][0]);
				element->material_->Bind();

				glDrawElements(GL_TRIANGLES, element->GetIndicesCount(), GL_UNSIGNED_INT, start);
				start += element->GetIndicesCount();
			}

			vertices_.clear();
			indices_.clear();
			elements_.clear();
		}
	}

	void RendererUI::Flush() {

	}
}