#pragma once
#include "Transform.hpp"
#include "Meshes/Mesh.hpp"
#include "Material.hpp"

namespace blackjack::core {
	class RenderObject {
		friend class Renderer3D;
	protected:
		Mesh* mesh_;
		Material* material_;
		Transform transform_;
	public:
		RenderObject();
		RenderObject(Mesh* mesh);
		RenderObject(Material* material);
		RenderObject(Mesh* mesh, Material* material);
		virtual ~RenderObject() = default;

		Mesh* GetMesh() const;
		Transform& GetTransform();

		void SetMesh(Mesh* mesh);
		void SetMaterial(Material* mat);
	};
}