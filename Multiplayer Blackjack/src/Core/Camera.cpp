#include "Camera.h"

namespace Blackjack::Core {
	Camera::Camera(float fov, float aspect_ratio) : m_proj(glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f)),m_view(1.0f), m_position(0,0,0), m_yaw(-90), m_pitch(0) {
		calculateDirectionalVectors();
	}

	void Camera::calculateDirectionalVectors() {
		//Calculate the front vector using the pitch and yaw
		glm::vec3 front;
		front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.y = sin(glm::radians(m_pitch));
		front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_front = glm::normalize(front);

		//Calculate the other vectors using the new front vector
		m_right = glm::normalize(glm::cross(m_front, glm::vec3(0,1,0)));
		m_up = glm::normalize(glm::cross(m_right, m_front));

		//m_front = -m_front;
	}

	float* Camera::getView() {
		m_view = m_proj * glm::lookAt(m_position, m_position + m_front, m_up);
		return &m_view[0][0];
	}

	glm::vec3& Camera::getPosition() {
		return m_position;
	}

	void Camera::translateX(float amount) {
		m_position += m_right * amount;
	}

	void Camera::translateY(float amount) {
		m_position += m_up * amount;
	}

	void Camera::translateZ(float amount) {
		m_position -= m_front * amount;
	}

	void Camera::pitch(float amount) {
		m_pitch += amount;
		if (m_pitch > 89.0f) {
			m_pitch = 89.0f;
		}
		if (m_pitch < -89.0f) {
			m_pitch = -89.0f;
		}
		calculateDirectionalVectors();
	}

	void Camera::yaw(float amount) {
		m_yaw += amount;
		calculateDirectionalVectors();
	}
}