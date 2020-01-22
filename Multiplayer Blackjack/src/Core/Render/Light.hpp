#pragma once
#include "glm/glm.hpp"

namespace blackjack::core {
	class Light {
		friend class Renderer3D;
	private:
		glm::vec3 ambient_;
		glm::vec3 diffuse_;
		glm::vec3 specular_;
		glm::vec3 position_;
	public:
		Light();

		void SetAmbient(const float f0, const float f1, const float f2);
		void SetDiffuse(const float f0, float f1, float f2);
		void SetSpecular(const float f0, float f1, float f2);
		void SetPosition(float f0, float f1, float f2);

		void SetPosition(const glm::vec3& position);
	};
}
