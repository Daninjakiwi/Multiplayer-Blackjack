#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include "Resources.hpp"

namespace Blackjack::Core {
	std::unordered_map<std::string, std::unique_ptr<Shader>> Resources::shaders_;
	std::unordered_map<std::string, std::unique_ptr<Material>> Resources::materials_;
	std::unordered_map<std::string, std::unique_ptr<Texture>> Resources::textures_;

	Shader* Resources::CreateShader(const std::string& name, const std::string& filepath) {
		Shader* s = shaders_[name].get();
		if (s == nullptr) {

			shaders_[name] = std::make_unique<Shader>(filepath);

			if (shaders_[name].get()->m_id == 0) {
				shaders_.erase(name);
				return nullptr;
			}
			return shaders_[name].get();
		}
		else {
			return s;
		}
	}

	Shader* Resources::GetShader(const std::string& name) {
		return shaders_[name].get();
	}

	Material* Resources::CreateMaterial(const std::string& name, Shader* shader) {
		Material* m = materials_[name].get();
		if (m == nullptr) {
			materials_[name] = std::make_unique<Material>(shader);

			return materials_[name].get();
		}
		else {
			return m;
		}
	}

	Material* Resources::GetMaterial(const std::string& name) {
		return materials_[name].get();
	}

	Texture* Resources::CreateTexture(const std::string& name, const std::string& filepath) {
		textures_[name] = std::make_unique<Texture>(filepath);

		return textures_[name].get();
	}

	Texture* Resources::GetTexture(const std::string& name) {
		return textures_[name].get();
	}

	std::string Resources::LoadFile(const char* filepath) {
		std::ifstream stream(filepath);
		std::stringstream ss;

		if (!stream.fail()) {
			ss << stream.rdbuf();
			stream.close();
		}
		return ss.str();
	}

	std::string Resources::LoadFile(const std::string& filepath) {
		return LoadFile(filepath.c_str());
	}

}