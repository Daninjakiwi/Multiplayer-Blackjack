#include "glad/glad.h"
#include "glm/glm.hpp"

#include "Core/Log.hpp"
#include "Core/Resources.hpp"
#include "Shader.h"


namespace Blackjack::Core {
	Shader::Shader(const std::string& filepath) : m_id(0) {
		m_id = glCreateProgram();

		std::string vertex_source = Resources::LoadFile(filepath + ".vert");
		std::string fragment_source = Resources::LoadFile(filepath + ".frag");

		unsigned int vert = compileShader(vertex_source.c_str(), GL_VERTEX_SHADER);


		unsigned int frag = compileShader(fragment_source.c_str(), GL_FRAGMENT_SHADER);

		if (vert != 0 && frag != 0) {
			glAttachShader(m_id, vert);
			glAttachShader(m_id, frag);

			glLinkProgram(m_id);
			glValidateProgram(m_id);
		}

		glDeleteShader(vert);
		glDeleteShader(frag);

	}

	Shader::~Shader() {
		glDeleteProgram(m_id);
		for (auto& it : m_uniforms) {
			void* i = it.second;
			if (i!= nullptr) {
				free(i);
			}
		}
	}

	void Shader::bind() const {
		glUseProgram(m_id);
	}

	void Shader::setFloat(unsigned int location, float* data) {
		float* n = (float*)m_uniforms[location];
		if (n == nullptr) {
			glUniform1fv(location, 1, data);
			void* next = malloc(1 * sizeof(float));
			if (next) {
				memcpy(next, data, 1 * sizeof(float));
				m_uniforms[location] = next;
			}
		}
		else {
			if (memcmp(n, data, 1 * sizeof(float)) != 0) {
				memcpy(n, data, 1 * sizeof(float));
				glUniform1fv(location, 1, data);
			}
		}
	}

	void Shader::setFloat(unsigned int location, float& data) {
		glUniform1f(location, data);
	}

	void Shader::setFVec2(unsigned int location, float* data) {
		glUniform2fv(location, 1, data);
	}

	void Shader::setFVec3(unsigned int location, float* data) {
		float* n = (float*)m_uniforms[location];
		if (n == nullptr) {
			glUniform3fv(location, 1, data);
			void* next = malloc(3 * sizeof(float));
			if (next) {
				memcpy(next, data, 3 * sizeof(float));
				m_uniforms[location] = next;
			}
		}
		else {
			if (memcmp(n, data, 3 * sizeof(float)) != 0) {
				memcpy(n, data, 3 * sizeof(float));
				glUniform3fv(location, 1, data);
			}
		}
	}

	void Shader::setFVec4(unsigned int location, float* data) {
		glUniform4fv(location, 1, data);
	}

	void Shader::setUInt(unsigned int location, unsigned int* data) {
		glUniform1uiv(location, 1, data);
	}

	void Shader::setUInt(unsigned int location, unsigned int data) {
		glUniform1ui(location, data);
	}

	void Shader::setInt(unsigned int location, int data) {
		glUniform1i(location, data);
	}

	void Shader::setInt(unsigned int location, int* data) {
		int* n = (int*)m_uniforms[location];
		if (n == nullptr) {
			glUniform1iv(location, 1, data);
			void* next = malloc(sizeof(int));
			if (next) {
				memcpy(next, data, sizeof(int));
				m_uniforms[location] = next;
			}
		}
		else {
			if (memcmp(n, data, sizeof(int)) != 0) {
				memcpy(n, data, sizeof(int));
				glUniform1iv(location, 1, data);
			}
		}
	}

	void Shader::setMat4(unsigned int location, float* data) {
		float* n = (float*)m_uniforms[location];
		if (n == nullptr) {
			glUniformMatrix4fv(location, 1, false, data);
			void* next = malloc(16 * sizeof(float));
			if (next) {
				memcpy(next, data, 16 * sizeof(float));
				m_uniforms[location] = next;
			}
		}
		else {
			if (memcmp(n, data, 16 * sizeof(float)) != 0) {
				memcpy(n, data, 16 * sizeof(float));
				glUniformMatrix4fv(location, 1, false, data);
			}
		}	
	}

	int Shader::getLocation(const std::string& name) {
		return glGetUniformLocation(m_id, name.c_str());
	}

	unsigned int Shader::compileShader(const char* source, unsigned int type) {
		unsigned int id = glCreateShader(type);

		glShaderSource(id, 1, &source, nullptr);
		glCompileShader(id);


		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE) {
			return 0;
		}

		return id;
	}
}