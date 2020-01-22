#pragma once
#include "Core/Transform.hpp"
#include "Meshes/Mesh.hpp"
#include "Material.hpp"

namespace blackjack::core {
	class RenderObject {
		friend class Renderer3D;
	private:
		Mesh* mesh_;
		Material* material_;
		Transform transform_;
	public:
		RenderObject();
		RenderObject(Mesh* mesh);
		RenderObject(Material* material);
		RenderObject(Mesh* mesh, Material* material);
		~RenderObject() = default;

		Mesh* GetMesh() const;
		Transform& GetTransform();

		void SetMesh(Mesh* mesh);
		void SetMaterial(Material* mat);
	};
}