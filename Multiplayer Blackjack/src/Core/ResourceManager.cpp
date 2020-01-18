#include "ResourceManager.h"
#include "glad/glad.h"

namespace Blackjack::Core {
	std::unordered_map<std::string, std::unique_ptr<Shader>> ResourceManager::s_shaders;
	std::unordered_map<std::string, std::unique_ptr<Material>> ResourceManager::s_materials;
	std::unordered_map<std::string, std::unique_ptr<Texture>> ResourceManager::s_textures;

	Shader* ResourceManager::createShader(const std::string& name, const std::string& filepath) {
		Shader* s = s_shaders[name].get();
		if (s == nullptr) {

			s_shaders[name] = std::make_unique<Shader>(filepath);

			if (s_shaders[name].get()->m_id == 0) {
				s_shaders.erase(name);
				return nullptr;
			}
			return s_shaders[name].get();
		}
		else {
			return s;
		}
	}

	Shader* ResourceManager::getShader(const std::string& name) {
		return s_shaders[name].get();
	}

	Material* ResourceManager::createMaterial(const std::string& name, Shader* shader) {
		Material* m = s_materials[name].get();
		if (m == nullptr) {
			s_materials[name] = std::make_unique<Material>(shader);

			return s_materials[name].get();
		}
		else {
			return m;
		}
	}

	Material* ResourceManager::getMaterial(const std::string& name) {
		return s_materials[name].get();
	}

	Texture* ResourceManager::createTexture(const std::string& name, const std::string& filepath) {
		s_textures[name] = std::make_unique<Texture>(filepath);

		return s_textures[name].get();
	}

	Texture* ResourceManager::getTexture(const std::string& name) {
		return s_textures[name].get();
	}

}