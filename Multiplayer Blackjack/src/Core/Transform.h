#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Blackjack::Core {
	class Transform {
	private:
		glm::mat4 m_matrix;
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	public:
		Transform();
		~Transform() = default;

		void setPosition(float x, float y, float z);
		void setRotation(float x, float y, float z);
		void setScale(float x, float y, float z);

		void reset();

		float* getMatrix();
	private:
		void updateMatrix();
	};
}
