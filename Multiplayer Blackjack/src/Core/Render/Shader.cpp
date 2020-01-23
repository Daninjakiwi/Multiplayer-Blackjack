#include "Core/Log.hpp"
#include "glad/glad.h"

#include "Core/Resources.hpp"
#include "Shader.hpp"

namespace blackjack::core {
	Shader::Shader(const std::string& filepath) : id_(0) {
		id_ = glCreateProgram();

		std::string vertex_source = Resources::LoadFile(filepath + ".vert");
		std::string fragment_source = Resources::LoadFile(filepath + ".frag");

		unsigned int vert = CompileShader(vertex_source.c_str(), GL_VERTEX_SHADER);


		unsigned int frag = CompileShader(fragment_source.c_str(), GL_FRAGMENT_SHADER);

		if (vert != 0 && frag != 0) {
			glAttachShader(id_, vert);
			glAttachShader(id_, frag);

			glLinkProgram(id_);
			glValidateProgram(id_);
		}
		glDeleteShader(vert);
		glDeleteShader(frag);
	}

	Shader::~Shader() {
		glDeleteProgram(id_);
		for (auto& it : uniforms_) {
			void* i = it.second;
			if (i!= nullptr) {
				free(i);
			}
		}
	}

	void Shader::Bind() const {
		glUseProgram(id_);
	}

	int Shader::GetLocation(const std::string& name) const {
		return glGetUniformLocation(id_, name.c_str());
	}

	void Shader::SetFloat(unsigned int location, float* data) {
		float* n = (float*)uniforms_[location];
		if (n == nullptr) {
			glUniform1fv(location, 1, data);
			void* next = malloc(1 * sizeof(float));
			if (next) {
				memcpy(next, data, 1 * sizeof(float));
				uniforms_[location] = next;
			}
		}
		else {
			if (memcmp(n, data, 1 * sizeof(float)) != 0) {
				memcpy(n, data, 1 * sizeof(float));
				glUniform1fv(location, 1, data);
			}
		}
	}

	void Shader::SetFloat(unsigned int location, float& data) {
		glUniform1f(location, data);
	}

	void Shader::SetFVec2(unsigned int location, float* data) {
		glUniform2fv(location, 1, data);
	}

	void Shader::SetFVec3(unsigned int location, float* data) {
		float* n = (float*)uniforms_[location];
		if (n == nullptr) {
			glUniform3fv(location, 1, data);
			void* next = malloc(3 * sizeof(float));
			if (next) {
				memcpy(next, data, 3 * sizeof(float));
				uniforms_[location] = next;
			}
		}
		else {
			if (memcmp(n, data, 3 * sizeof(float)) != 0) {
				memcpy(n, data, 3 * sizeof(float));
				glUniform3fv(location, 1, data);
			}
		}
	}

	void Shader::SetFVec4(unsigned int location, float* data) {
		glUniform4fv(location, 1, data);
	}

	void Shader::SetUInt(unsigned int location, unsigned int* data) {
		glUniform1uiv(location, 1, data);
	}

	void Shader::SetUInt(unsigned int location, unsigned int data) {
		glUniform1ui(location, data);
	}

	void Shader::SetInt(unsigned int location, int data) {
		glUniform1i(location, data);
	}

	void Shader::SetInt(unsigned int location, int* data) {
		int* n = (int*)uniforms_[location];
		if (n == nullptr) {
			glUniform1iv(location, 1, data);
			void* next = malloc(sizeof(int));
			if (next) {
				memcpy(next, data, sizeof(int));
				uniforms_[location] = next;
			}
		}
		else {
			if (memcmp(n, data, sizeof(int)) != 0) {
				memcpy(n, data, sizeof(int));
				glUniform1iv(location, 1, data);
			}
		}
	}

	void Shader::SetMat4(unsigned int location, float* data) {
		float* n = (float*)uniforms_[location];
		if (n == nullptr) {
			glUniformMatrix4fv(location, 1, false, data);
			void* next = malloc(16 * sizeof(float));
			if (next) {
				memcpy(next, data, 16 * sizeof(float));
				uniforms_[location] = next;
			}
		}
		else {
			if (memcmp(n, data, 16 * sizeof(float)) != 0) {
				memcpy(n, data, 16 * sizeof(float));
				glUniformMatrix4fv(location, 1, false, data);
			}
		}	
	}

	unsigned int Shader::CompileShader(const char* source, unsigned int type) {
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