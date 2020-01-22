#include "RenderObject.hpp"

namespace blackjack::core {
	RenderObject::RenderObject() : mesh_(nullptr), material_(nullptr) {

	}

	RenderObject::RenderObject(Mesh* mesh) : mesh_(mesh), material_(nullptr) {

	}

	RenderObject::RenderObject(Material* material) : mesh_(nullptr), material_(material) {

	}
	RenderObject::RenderObject(Mesh* mesh, Material* material) :mesh_(mesh), material_(material){

	}

	Mesh* RenderObject::GetMesh() const {
		return mesh_;
	}

	Transform& RenderObject::GetTransform() {
		return transform_;
	}

	void RenderObject::SetMesh(Mesh* mesh) {
		mesh_ = mesh;
	}

	void RenderObject::SetMaterial(Material* mat) {
		material_ = mat;
	}
}