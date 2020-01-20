#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include "Core/Render/Meshes/Mesh.h"
#include "Core/Render/Shader.h"
#include "Core/Render/Material.h"

namespace Blackjack::Core {
	class Resources {
	private:
		static std::unordered_map<std::string, std::unique_ptr<Shader>> shaders_;
		static std::unordered_map<std::string, std::unique_ptr<Material>> materials_;
		static std::unordered_map<std::string, std::unique_ptr<Texture>> textures_;
	public:
		static Shader* CreateShader(const std::string& name, const std::string& filepath);
		static Shader* GetShader(const std::string& name);

		static Material* CreateMaterial(const std::string& name, Shader* shader);
		static Material* GetMaterial(const std::string& name);

		static Texture* CreateTexture(const std::string& name, const std::string& filepath);
		static Texture* GetTexture(const std::string& name);

		static std::string LoadFile(const char* filepath);
		static std::string LoadFile(const std::string& filepath);
	};
}