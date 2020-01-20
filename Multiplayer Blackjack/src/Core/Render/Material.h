#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Shader.h"
#include "Texture.h"

namespace Blackjack::Core {
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
		UniformType m_type;
		int m_location;
		void* m_buffer;
	public:
		Uniform(UniformType type, int location, const void* data);
		Uniform() = default;
		virtual ~Uniform();

		void setData(const void* data);

		static unsigned int getSizeOf(UniformType type);

		inline UniformType getType() { return m_type; };
		inline int getLocation() { return m_location; };
		inline void* getBuffer() { return m_buffer; };
	};

	class Material {
		friend class Renderer3D;
	private:
		Shader* m_shader;
		std::vector<Uniform*> m_uniforms;
		std::unordered_map<std::string, std::unique_ptr<Uniform>> m_uniform;
	public:
		Material(Shader* s);
		~Material();

		void bind() const;

		inline Shader* shader() const { return m_shader; };

		void setUniform(const std::string& name, UniformType type, const void* data);

		void setUniform3f(const std::string& name, const float f0, const float f1, const float f2);
		void setUniform3f(const std::string& name, glm::vec3& vec);
		void setUniform1f(const std::string& name, const float f0);

		void setUniform4f(const std::string& name, const float f0, const float f1, const float f2, const float f3);

	};

}
