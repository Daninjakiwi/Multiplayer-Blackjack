#pragma once
#include "glm/glm.hpp"

namespace Core {
	class Shader {
		friend class ResourceManager;
	private:
		unsigned int m_id;
	public:
		Shader(const std::string& filepath);
		~Shader();

		void bind() const;

		void setVec3(const std::string& name, float x, float y, float z);
		void setMat4(const std::string& name, glm::mat4& mat);
		void setUInt(const std::string& name, unsigned int value);
		void setFloat(const std::string& name, float value);
	private:
		static unsigned int compileShader(const char* source, unsigned int type);
	};
}
