#include "Light.h"

namespace Blackjack::Core {
	Light::Light() : m_ambient(1.0f), m_diffuse(1.0f), m_specular(1.0f), m_position(0.0f) {

	}

	void Light::setAmbient(float f0, float f1, float f2) {
		m_ambient = glm::vec3(f0, f1, f2);
	}
	void Light::setDiffuse(float f0, float f1, float f2) {
		m_diffuse = glm::vec3(f0, f1, f2);
	}
	void Light::setSpecular(float f0, float f1, float f2) {
		m_specular = glm::vec3(f0, f1, f2);
	}
	void Light::setPosition(float f0, float f1, float f2) {
		m_position = glm::vec3(f0, f1, f2);
	}

	void Light::setPosition(glm::vec3& position) {
		m_position = position;
	}
}