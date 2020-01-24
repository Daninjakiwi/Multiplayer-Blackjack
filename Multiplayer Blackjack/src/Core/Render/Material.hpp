#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "glm/glm.hpp"

#include "Shader.hpp"
#include "Texture.hpp"

namespace blackjack::core {
	enum class UniformType {
		FLOAT, FVEC2, FVEC3, FVEC4,
		INT, IVEC2, IVEC3, IVEC4,
		UINT, UVEC2, UVEC3, UVEC4,
		MAT2, MAT3, MAT4, TEXTURE2D,
		BOOL
	};

	class Uniform {
		friend class Material;
	private:
		UniformType type_;
		int location_;
		void* buffer_;
	public:
		Uniform(UniformType type, int location, const void* data);
		Uniform() = default;
		virtual ~Uniform();

		void SetData(const void* data);

		static unsigned int GetSizeOf(UniformType type);

		inline UniformType getType() { return type_; };
		inline int GetLocation() { return location_; };
		inline void* GetBuffer() { return buffer_; };
	};

	class Material {
		friend class Renderer3D;
	private:
		static std::unordered_map<std::string, std::unique_ptr<Material>> materials_;

		Shader* shader_;
		std::unordered_map<std::string, std::unique_ptr<Uniform>> uniform_;
	public:
		static Material* Create(const std::string& name, const std::string& shader);
		static Material* Create(const std::string& name, Shader* shader);
		static Material* Get(const std::string& name);


		Material(Shader* s);

		void Bind() const;

		inline Shader* GetShader() const { return shader_; };

		void SetUniform(const std::string& name, UniformType type, const void* data);
		void SetUniform3f(const std::string& name, const float f0, const float f1, const float f2);
		void SetUniform3f(const std::string& name, const glm::vec3& vec);
		void SetUniform1f(const std::string& name, const float f0);
		void SetUniform4f(const std::string& name, const float f0, const float f1, const float f2, const float f3);

	};

}
