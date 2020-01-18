#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glad/glad.h"

namespace Blackjack::Core {
	class Camera {
	public:
		// Camera Attributes
		glm::mat4 m_proj;
		glm::mat4 m_view;

		glm::vec3 m_position;
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;
		// Euler Angles
		float m_yaw;
		float m_pitch;

		Camera(float fov, float aspect_ratio);

		float* getView();

		void translateX(float amount);
		void translateY(float amount);
		void translateZ(float amount);

		void pitch(float amount);
		void yaw(float amount);

		glm::vec3& getPosition();

	private:

		void calculateDirectionalVectors();

	};




}
