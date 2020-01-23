#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace blackjack::core {
	class Camera {
	public:
		// Camera Attributes
		glm::mat4 proj_;
		glm::mat4 view_;

		glm::vec3 position_;
		glm::vec3 front_;
		glm::vec3 up_;
		glm::vec3 right_;
		// Euler Angles
		float yaw_;
		float pitch_;

		Camera(float fov, float aspect_ratio);

		void TranslateX(float amount);
		void TranslateY(float amount);
		void TranslateZ(float amount);

		void Pitch(float amount);
		void Yaw(float amount);

		glm::vec3& GetPosition();
		float* GetView();

	private:
		void CalculateDirectionalVectors();
	};




}
