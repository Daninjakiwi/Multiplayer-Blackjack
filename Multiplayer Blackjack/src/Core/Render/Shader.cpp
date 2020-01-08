#include "glad/glad.h"
#include "glm/glm.hpp"

#include "Core/Log.h"
#include "Core/FileSystem.h"
#include "Shader.h"


namespace Core {
	Shader::Shader(const std::string& filepath) : m_id(0) {
		m_id = glCreateProgram();

		std::string vertex_source = FileSystem::loadFile(filepath + ".vert");
		std::string fragment_source = FileSystem::loadFile(filepath + ".frag");

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
	}

	void Shader::bind() const {
		glUseProgram(m_id);
	}

	void Shader::setVec3(const std::string& name, float x, float y, float z) {
		unsigned int loc = glGetUniformLocation(m_id, name.c_str());
		glUniform3f(loc, x, y, z);
	}

	void Shader::setMat4(const std::string& name, glm::mat4& mat) {
		unsigned int loc = glGetUniformLocation(m_id, name.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::setUInt(const std::string& name, unsigned int value) {
		unsigned int loc = glGetUniformLocation(m_id, name.c_str());
		glUniform1ui(loc, value);
	}

	void Shader::setFloat(const std::string& name, float value) {
		unsigned int loc = glGetUniformLocation(m_id, name.c_str());
		glUniform1f(loc, value);
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