#pragma once
#include "Meshes/Mesh.h"
#include "Core/Transform.h"

namespace Core {
	class RenderObject {
	private:
		Mesh* m_mesh;
		Transform m_transform;
	public:
		RenderObject();
		~RenderObject() = default;

		void setMesh(Mesh* mesh);
		Mesh* getMesh() const;

		Transform& getTransform();
	};
}