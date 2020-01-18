#include "Transform.h"

namespace Blackjack::Core {
	Transform::Transform() : m_matrix(1.0f), m_position(0,0,0), m_rotation(0,0,0), m_scale(1,1,1) {
	}

	void Transform::setPosition(float x, float y, float z) {
		m_position = glm::vec3(x, y, z);
		updateMatrix();
	}

	void Transform::setRotation(float x, float y, float z) {
		m_rotation = glm::vec3(x, y, z);
		updateMatrix();
	}

	void Transform::setScale(float x, float y, float z) {
		m_scale = glm::vec3(x, y, z);
		updateMatrix();
	}

	void Transform::reset() {
		m_position = glm::vec3();
		m_rotation = glm::vec3();
		m_scale = glm::vec3(1,1,1);
		updateMatrix();
	}

	void Transform::updateMatrix() {
		m_matrix = glm::mat4(1.0f);
		m_matrix = glm::translate(m_matrix, m_position);	
		m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
		m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
		m_matrix = glm::rotate(m_matrix, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
		m_matrix = glm::scale(m_matrix, m_scale);

	}

	float* Transform::getMatrix() {
		return &m_matrix[0][0];
	}
}