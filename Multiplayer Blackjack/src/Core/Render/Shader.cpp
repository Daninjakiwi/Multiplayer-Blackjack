#include "glad/glad.h"

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

	void Shader::setColour(float r, float g, float b) {
		glUniform3f(glGetUniformLocation(m_id, "u_colour"), r, g, b);
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