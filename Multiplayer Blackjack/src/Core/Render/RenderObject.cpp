#include "RenderObject.h"

namespace Blackjack::Core {
	RenderObject::RenderObject() : m_mesh(nullptr), m_material(nullptr) {

	}

	RenderObject::RenderObject(Mesh* mesh) : m_mesh(mesh), m_material(nullptr) {

	}
	RenderObject::RenderObject(Material* material) : m_mesh(nullptr), m_material(material) {

	}
	RenderObject::RenderObject(Mesh* mesh, Material* material) :m_mesh(mesh), m_material(material){

	}

	void RenderObject::setMesh(Mesh* mesh) {
		m_mesh = mesh;
	}

	Mesh* RenderObject::getMesh() const {
		return m_mesh;
	}

	void RenderObject::setMaterial(Material* mat) {
		m_material = mat;
	}

	Transform& RenderObject::getTransform() {
		return m_transform;
	}
}