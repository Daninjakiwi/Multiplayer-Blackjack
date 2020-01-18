#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include "Core/Render/Shader.h"
#include "Core/Render/Meshes/Mesh.h"
#include "Core/Render/Material.h"

namespace Blackjack::Core {
	class ResourceManager {
	private:
		static std::unordered_map<std::string, std::unique_ptr<Shader>> s_shaders;
		static std::unordered_map<std::string, std::unique_ptr<Material>> s_materials;
		static std::unordered_map<std::string, std::unique_ptr<Texture>> s_textures;
	public:
		static Shader* createShader(const std::string& name, const std::string& filepath);
		static Shader* getShader(const std::string& name);

		static Material* createMaterial(const std::string& name, Shader* shader);
		static Material* getMaterial(const std::string& name);

		static Texture* createTexture(const std::string& name, const std::string& filepath);
		static Texture* getTexture(const std::string& name);
	};
}
