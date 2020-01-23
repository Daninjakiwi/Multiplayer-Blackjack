#include "Camera.hpp"

namespace blackjack::core {
	Camera::Camera(float fov, float aspect_ratio) : proj_(glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f)),view_(1.0f), position_(0,0,0), yaw_(-90), pitch_(0) {
		CalculateDirectionalVectors();
	}

	void Camera::CalculateDirectionalVectors() {
		//Calculate the front vector using the pitch and yaw
		glm::vec3 front;
		front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
		front.y = sin(glm::radians(pitch_));
		front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
		front_ = glm::normalize(front);

		//Calculate the other vectors using the new front vector
		right_ = glm::normalize(glm::cross(front_, glm::vec3(0,1,0)));
		up_ = glm::normalize(glm::cross(right_, front_));
	}

	float* Camera::GetView() {
		view_ = proj_ * glm::lookAt(position_, position_ + front_, up_);
		return &view_[0][0];
	}

	glm::vec3& Camera::GetPosition() {
		return position_;
	}

	void Camera::TranslateX(float amount) {
		position_ += right_ * amount;
	}

	void Camera::TranslateY(float amount) {
		position_ += up_ * amount;
	}

	void Camera::TranslateZ(float amount) {
		position_ -= front_ * amount;
	}

	void Camera::Pitch(float amount) {
		pitch_ += amount;
		if (pitch_ > 89.0f) {
			pitch_ = 89.0f;
		}
		if (pitch_ < -89.0f) {
			pitch_ = -89.0f;
		}
		CalculateDirectionalVectors();
	}

	void Camera::Yaw(float amount) {
		yaw_ += amount;
		CalculateDirectionalVectors();
	}
}