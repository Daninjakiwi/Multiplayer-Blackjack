#include "ResourceManager.h"
#include "glad/glad.h"

namespace Core {
	std::unordered_map<std::string, std::unique_ptr<Shader>> ResourceManager::s_shaders;

	Shader* ResourceManager::createShader(const std::string& name, const std::string& filepath) {
		s_shaders[name] = std::make_unique<Shader>(filepath);

		if (s_shaders[name].get()->m_id == 0) {
			s_shaders.erase(name);
			return nullptr;
		}
		return s_shaders[name].get();
	}

	Shader* ResourceManager::getShader(const std::string& name) {
		return s_shaders[name].get();
	}
}