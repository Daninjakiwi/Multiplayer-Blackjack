#include "RenderObject.h"

namespace Core {
	RenderObject::RenderObject() : m_mesh(nullptr) {

	}

	void RenderObject::setMesh(Mesh* mesh) {
		m_mesh = mesh;
	}

	Mesh* RenderObject::getMesh() const {
		return m_mesh;
	}

	Transform& RenderObject::getTransform() {
		return m_transform;
	}
}