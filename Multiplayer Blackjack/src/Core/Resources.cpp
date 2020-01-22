#include <fstream>
#include <sstream>
#include <random>
#include "glad/glad.h"
#include "Resources.hpp"
#include "Log.hpp"

namespace Blackjack::Core {
	std::unordered_map<std::string, std::unique_ptr<Shader> > Resources::shaders_;
	std::unordered_map<std::string, std::unique_ptr<Material> > Resources::materials_;
	std::unordered_map<std::string, std::unique_ptr<Texture> > Resources::textures_;

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
		Shader* s = shaders_[name].get();
		if (s == nullptr) {
			CORE_LOG(name + " is null");
		}
		return shaders_[name].get();
	}

	Material* Resources::CreateMaterial(const std::string& name, Shader* shader) {
		Material* m = materials_[name].get();
		if (m == nullptr) {
			materials_[name] = std::make_unique<Material>(shader);
			CORE_LOG("Created:" + name);
			return materials_[name].get();
		}
		else {
			CORE_LOG("Found:" + name);
			return m;
		}
	}

	void Resources::UpdateMaterial(const std::string& name, const std::string& new_name) {
		auto m = materials_.extract(name);
		m.key() = new_name;
		materials_.insert(move(m));
	}

	Material* Resources::CreateMaterial(Shader* shader) {
		std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

		std::random_device rd;
		std::mt19937 generator(rd());

		std::shuffle(str.begin(), str.end(), generator);

		materials_[str.substr(0, 20)] = std::make_unique<Material>(shader);
		return materials_[str.substr(0, 20)].get();
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