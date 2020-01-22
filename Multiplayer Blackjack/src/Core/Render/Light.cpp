#include "Light.hpp"

namespace blackjack::core {
	Light::Light() : ambient_(1.0f), diffuse_(1.0f), specular_(1.0f), position_(0.0f) {

	}

	void Light::SetAmbient(const float f0, const float f1, const float f2) {
		ambient_ = glm::vec3(f0, f1, f2);
	}
	void Light::SetDiffuse(const float f0, const float f1, const float f2) {
		diffuse_ = glm::vec3(f0, f1, f2);
	}
	void Light::SetSpecular(const float f0, const float f1, const float f2) {
		specular_ = glm::vec3(f0, f1, f2);
	}
	void Light::SetPosition(const float f0, const float f1, const float f2) {
		position_ = glm::vec3(f0, f1, f2);
	}

	void Light::SetPosition(const glm::vec3& position) {
		position_ = position;
	}
}