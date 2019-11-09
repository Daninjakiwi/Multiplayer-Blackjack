#pragma once

namespace Core {
	class Shader {
		friend class ResourceManager;
	private:
		unsigned int m_id;
	public:
		Shader(const std::string& filepath);
		~Shader();

		void bind() const;

		void setColour(float r, float g, float b);
	private:
		static unsigned int compileShader(const char* source, unsigned int type);
	};
}
