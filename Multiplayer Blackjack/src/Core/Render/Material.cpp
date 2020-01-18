#include "Material.h"
#include <iostream>

namespace Blackjack::Core {
	Material::Material(Shader* s) : m_shader(s) {
	}

	Material::~Material() {
		for (Uniform* u : m_uniforms) {
			delete u;
		}
	}

	void Material::bind() const {
		int tex_slot = 0;

		for (auto& it : m_uniform) {
			Uniform* u = it.second.get();
			switch (u->m_type) {
				case UniformType::FLOAT:
					m_shader->setFloat(u->getLocation(), (float*)u->m_buffer);
					break;
				case UniformType::FVEC2:
					m_shader->setFVec2(u->getLocation(), (float*)u->m_buffer);
					break;
				case UniformType::FVEC3:
					m_shader->setFVec3(u->getLocation(), (float*)u->m_buffer);
					break;
				case UniformType::FVEC4:
					m_shader->setFVec4(u->getLocation(), (float*)u->m_buffer);
					break;
				case UniformType::MAT4:
					m_shader->setMat4(u->getLocation(), (float*)u->m_buffer);
					break;
				case UniformType::BOOL:
					m_shader->setInt(u->getLocation(), (int*)u->m_buffer);
					break;
				case UniformType::TEXTURE2D:
					Texture* tex = (Texture*)u->m_buffer;

					tex->bind(tex_slot);
					m_shader->setInt(u->getLocation(), tex_slot);

					tex_slot += 1;
					break;
			}
		}
	}

	void Material::setUniform3f(const std::string& name, const float f0, const float f1, const float f2) {
		float data[] = { f0,f1,f2 };
		setUniform(name, UniformType::FVEC3, &data);
	}

	void Material::setUniform3f(const std::string& name, glm::vec3& vec) {
		float data[] = { vec.x, vec.y, vec.z };
		setUniform(name, UniformType::FVEC3, &data);
	}

	void Material::setUniform1f(const std::string& name, const float f0) {
		setUniform(name, UniformType::FLOAT, &f0);
	}

	void Material::setUniform(const std::string& name, UniformType type, const void* data) {
		Uniform* uniform = m_uniform[name].get();

		if (uniform == nullptr) {			
			int loc = m_shader->getLocation(name);
			if (loc == -1) {
				return;
			}

			m_uniform[name] = std::make_unique<Uniform>(type, loc, data);
		}
		else {
			uniform->setData(data);
		}
	}


	void Uniform::setData(const void* data) {
		if (m_buffer) {
			memcpy(m_buffer, data, getSizeOf(m_type));
		}
	}

	Uniform::Uniform(UniformType type, int location, const void* data) : m_type(type), m_location(location), m_buffer(nullptr) {
		m_buffer = malloc(getSizeOf(type));
		if (m_buffer) {
			memcpy(m_buffer, data, getSizeOf(m_type));
		}
	}

	Uniform::~Uniform() {
		if (m_buffer != nullptr) {
			free(m_buffer);
		}
	}

	unsigned int Uniform::getSizeOf(UniformType type) {
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
		}
	}
}