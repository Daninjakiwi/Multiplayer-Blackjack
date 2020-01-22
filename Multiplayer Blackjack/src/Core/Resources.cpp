#include <fstream>
#include <sstream>
#include <random>
#include "glad/glad.h"
#include "Resources.hpp"
#include "Log.hpp"

namespace blackjack::core {
	std::unordered_map<std::string, std::unique_ptr<Shader> > Resources::shaders_;
	std::unordered_map<std::string, std::unique_ptr<Material> > Resources::materials_;
	std::unordered_map<std::string, std::unique_ptr<Texture> > Resources::textures_;

	Shader* Resources::CreateShader(const std::string& name, const std::string& filepath) {
		Shader* s = shaders_[name].get();
		if (s == nullptr) {

			shaders_[name] = std::make_unique<Shader>(filepath);

			if (shaders_[name].get()->id_ == 0) {
				shaders_.erase(name);
				COREERROR("Shader '" + name + "' failed to load.");
				return nullptr;
			}
			COREINFO("Shader '" + name + "' created.");
			return shaders_[name].get();
		}
		else {
			COREWARN("Shader '" + name + "' already exists.");
			return s;
		}
	}

	Shader* Resources::GetShader(const std::string& name) {
		Shader* s = shaders_[name].get();
		if (s == nullptr) {
			COREERROR("Shader '" + name + "' does not exist.");
		}
		return shaders_[name].get();
	}

	Material* Resources::CreateMaterial(const std::string& name, Shader* shader) {
		Material* m = materials_[name].get();
		if (m == nullptr) {
			materials_[name] = std::make_unique<Material>(shader);
			COREINFO("Created Material '" + name + "'.");
			return materials_[name].get();
		}
		else {
			COREWARN("Material '" + name + "' already exists.");
			return m;
		}
	}

	Material* Resources::GetMaterial(const std::string& name) {
		return materials_[name].get();
	}

	Texture* Resources::CreateTexture(const std::string& name, const std::string& filepath) {
		textures_[name] = std::make_unique<Texture>(filepath);

		COREINFO("Texture '" + name + "' created.");

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