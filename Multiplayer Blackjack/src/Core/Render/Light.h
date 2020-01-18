#pragma once
#include "glm/glm.hpp"

namespace Blackjack::Core {
	class Light {
		friend class Renderer3D;
	private:
		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;
		glm::vec3 m_position;
	public:
		Light();

		void setAmbient(float f0, float f1, float f2);
		void setDiffuse(float f0, float f1, float f2);
		void setSpecular(float f0, float f1, float f2);
		void setPosition(float f0, float f1, float f2);

		void setPosition(glm::vec3& position);
	};
}
