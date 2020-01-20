#include "Transform.hpp"

namespace Blackjack::Core {
	Transform::Transform() : matrix_(1.0f), position_(0,0,0), rotation_(0,0,0), scale_(1,1,1) {
	}

	void Transform::SetPosition(float x, float y, float z) {
		position_ = glm::vec3(x, y, z);
		UpdateMatrix();
	}

	void Transform::SetRotation(float x, float y, float z) {
		rotation_ = glm::vec3(x, y, z);
		UpdateMatrix();
	}

	void Transform::SetScale(float x, float y, float z) {
		scale_ = glm::vec3(x, y, z);
		UpdateMatrix();
	}

	void Transform::Reset() {
		position_ = glm::vec3();
		rotation_ = glm::vec3();
		scale_ = glm::vec3(1,1,1);
		UpdateMatrix();
	}

	void Transform::UpdateMatrix() {
		matrix_ = glm::mat4(1.0f);
		matrix_ = glm::translate(matrix_, position_);	
		matrix_ = glm::rotate(matrix_, glm::radians(rotation_.x), glm::vec3(1, 0, 0));
		matrix_ = glm::rotate(matrix_, glm::radians(rotation_.y), glm::vec3(0, 1, 0));
		matrix_ = glm::rotate(matrix_, glm::radians(rotation_.z), glm::vec3(0, 0, 1));
		matrix_ = glm::scale(matrix_, scale_);

	}

	float* Transform::GetMatrix() {
		return &matrix_[0][0];
	}
}