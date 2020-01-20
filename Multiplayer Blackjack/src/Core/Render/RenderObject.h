#pragma once
#include "Meshes/Mesh.h"
#include "Material.h"
#include "Core/Transform.hpp"

namespace Blackjack::Core {
	class RenderObject {
		friend class Renderer3D;
	private:
		Mesh* m_mesh;
		Material* m_material;
		Transform m_transform;
	public:
		RenderObject();
		RenderObject(Mesh* mesh);
		RenderObject(Material* material);
		RenderObject(Mesh* mesh, Material* material);
		~RenderObject() = default;

		void setMesh(Mesh* mesh);
		Mesh* getMesh() const;

		void setMaterial(Material* mat);

		Transform& getTransform();
	};
}