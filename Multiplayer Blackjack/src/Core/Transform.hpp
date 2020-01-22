#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace blackjack::core {
	class Transform {
	private:
		glm::mat4 matrix_;
		glm::vec3 position_;
		glm::vec3 rotation_;
		glm::vec3 scale_;
	public:
		Transform();
		~Transform() = default;

		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);

		void Reset();

		float* GetMatrix();
	private:
		void UpdateMatrix();
	};
}
