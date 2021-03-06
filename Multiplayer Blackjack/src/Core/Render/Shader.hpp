#pragma once
#include <unordered_map>

namespace blackjack::core {
	class Shader {
		friend class Resources;
	private:
		static std::unordered_map<std::string, std::unique_ptr<Shader>> shaders_;

		unsigned int id_;
		std::unordered_map<unsigned int, void*> uniforms_;
	public:
		static void Load(const std::string& name);
		static Shader* Get(const std::string& name);

		Shader(const std::string& file_path);
		~Shader();

		void Bind() const;

		int GetLocation(const std::string& name) const;

		void SetFloat(unsigned int location, float* data);
		void SetFloat(unsigned int location, float& data);
		void SetFVec2(unsigned int location, float* data);
		void SetFVec3(unsigned int location, float* data);
		void SetFVec4(unsigned int location, float* data);
		void SetUInt(unsigned int location, unsigned int* data);
		void SetUInt(unsigned int location, unsigned int data);
		void SetInt(unsigned int location, int data);
		void SetInt(unsigned int location, int* data);
		void SetMat4(unsigned int location, float* data);
	private:
		static unsigned int CompileShader(const char* source, unsigned int type);
	};
}
