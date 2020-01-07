#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include "Core/Render/Shader.h"
#include "Core/Render/Meshes/Mesh.h"

namespace Core {
	class ResourceManager {
	private:
		static std::unordered_map<std::string, std::unique_ptr<Shader>> s_shaders;
	public:
		static Shader* createShader(const std::string& name, const std::string& filepath);
		static Shader* getShader(const std::string& name);
	};
}
