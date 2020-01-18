#pragma once
#include "glm/glm.hpp"
#include <unordered_map>

namespace Blackjack::Core {
	class Shader {
		friend class ResourceManager;
	private:
		unsigned int m_id;
		std::unordered_map<unsigned int, void*> m_uniforms;
	public:
		Shader(const std::string& filepath);
		~Shader();

		void bind() const;

		void setFloat(unsigned int location, float* data);
		void setFloat(unsigned int location, float& data);

		void setFVec2(unsigned int location, float* data);
		void setFVec3(unsigned int location, float* data);
		void setFVec4(unsigned int location, float* data);

		void setUInt(unsigned int location, unsigned int* data);
		void setUInt(unsigned int location, unsigned int data);

		void setInt(unsigned int location, int data);
		void setInt(unsigned int location, int* data);

		void setMat4(unsigned int location, float* data);

		int getLocation(const std::string& name);
	private:
		static unsigned int compileShader(const char* source, unsigned int type);
	};
}
