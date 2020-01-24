#include "Core/Log.hpp"
#include "Material.hpp"
#include <iostream>

namespace blackjack::core {
	std::unordered_map<std::string, std::unique_ptr<Material>> Material::materials_;

	Material* Material::Create(const std::string& name, const std::string& shader) {
		Material* mat = materials_[name].get();
		if (mat == nullptr) {
			materials_[name] = std::make_unique<Material>(Shader::Get(shader));
			return materials_[name].get();
		}
		return mat;
	}
	
	Material* Material::Create(const std::string& name, Shader* shader) {
		Material* mat = materials_[name].get();
		if (mat == nullptr) {
			materials_[name] = std::make_unique<Material>(shader);
			return materials_[name].get();
		}
		return mat;
	}
	Material* Material::Get(const std::string& name) {
		return materials_[name].get();
	}



	Material::Material(Shader* s) : shader_(s) {
	}

	void Material::Bind() const {
		int tex_slot = 0;
		shader_->Bind();

		for (auto& it : uniform_) {
			Uniform* u = it.second.get();
			switch (u->type_) {
				case UniformType::FLOAT:
					shader_->SetFloat(u->GetLocation(), (float*)u->buffer_);
					break;
				case UniformType::FVEC2:
					shader_->SetFVec2(u->GetLocation(), (float*)u->buffer_);
					break;
				case UniformType::FVEC3:
					shader_->SetFVec3(u->GetLocation(), (float*)u->buffer_);
					break;
				case UniformType::FVEC4:
					shader_->SetFVec4(u->GetLocation(), (float*)u->buffer_);
					break;
				case UniformType::MAT4:
					shader_->SetMat4(u->GetLocation(), (float*)u->buffer_);
					break;
				case UniformType::BOOL:
					shader_->SetInt(u->GetLocation(), (int*)u->buffer_);
					break;
				case UniformType::TEXTURE2D:
					Texture* tex = (Texture*)u->buffer_;

					tex->Bind(tex_slot);
					shader_->SetInt(u->GetLocation(), tex_slot);

					tex_slot += 1;
					break;
			}
		}
	}

	void Material::SetUniform3f(const std::string& name, const float f0, const float f1, const float f2) {
		float data[] = { f0,f1,f2 };
		SetUniform(name, UniformType::FVEC3, &data);
	}

	void Material::SetUniform3f(const std::string& name, const glm::vec3& vec) {
		SetUniform(name, UniformType::FVEC3, &vec.x);
	}

	void Material::SetUniform1f(const std::string& name, const float f0) {
		SetUniform(name, UniformType::FLOAT, &f0);
	}

	void Material::SetUniform4f(const std::string& name, const float f0, const float f1, const float f2, const float f3) {
		float data[] = { f0,f1,f2,f3};
		SetUniform(name, UniformType::FVEC4, &data);
	}

	void Material::SetUniform(const std::string& name, UniformType type, const void* data) {
		Uniform* uniform = uniform_[name].get();

		if (uniform == nullptr) {			
			int loc = shader_->GetLocation(name);
			if (loc == -1) {
				return;
			}

			uniform_[name] = std::make_unique<Uniform>(type, loc, data);
		}
		else {
			uniform->SetData(data);
		}
	}


	void Uniform::SetData(const void* data) {
		if (buffer_) {
			memcpy(buffer_, data, GetSizeOf(type_));
		}
	}

	Uniform::Uniform(UniformType type, int location, const void* data) : type_(type), location_(location), buffer_(nullptr) {
		buffer_ = malloc(GetSizeOf(type));
		if (buffer_) {
			memcpy(buffer_, data, GetSizeOf(type_));
		}
	}

	Uniform::~Uniform() {
		if (buffer_ != nullptr) {
			free(buffer_);
		}
	}

	unsigned int Uniform::GetSizeOf(UniformType type) {
		switch (type) {
		case UniformType::FLOAT:
			return sizeof(float);
		case UniformType::FVEC2:
			return 2*sizeof(float);
		case UniformType::FVEC3:
			return 3*sizeof(float);
		case UniformType::FVEC4:
			return 4*sizeof(float);
		case UniformType::UINT:
			return sizeof(unsigned int);
		case UniformType::MAT4:
			return 16*sizeof(float);
		case UniformType::TEXTURE2D:
			return sizeof(Texture*);
		case UniformType::BOOL:
			return sizeof(bool);
		default:
			return 0;
		}
	}
}