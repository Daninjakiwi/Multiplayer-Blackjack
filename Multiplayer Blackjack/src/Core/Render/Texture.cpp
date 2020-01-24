#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include "Core/Log.hpp"
#include "glad/glad.h"
#include "stb_image/stb_image.h"

#include "Texture.hpp"

namespace blackjack::core {
	constexpr auto TEXTURE_PATH = "res/textures/";

	std::unordered_map<std::string, std::unique_ptr<Texture>> Texture::textures_;

	void Texture::Load(const std::string& name) {
		textures_[name] = std::make_unique<Texture>(TEXTURE_PATH + name);
	}

	Texture* Texture::Get(const std::string& name) {
		return textures_[name].get();
	}

	Texture::Texture(const std::string& file_path) : id_(0), width_(0), height_(0) {
		stbi_set_flip_vertically_on_load(true);
		int width, height, bpp;
		auto buffer = stbi_load(file_path.c_str(), &width, &height, &bpp, 4);

		width_ = width;
		height_ = height;

		glGenTextures(1, &id_);
		glBindTexture(GL_TEXTURE_2D, id_);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

		if (buffer) {
			stbi_image_free(buffer);
		}
	}

	Texture::Texture(bool test): width_(2), height_(2) {
		glGenTextures(1, &id_);
		glBindTexture(GL_TEXTURE_2D, id_);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		float data[] = {
			1.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,
			0.0f,0.0f,1.0f,
			1.0f,1.0f,1.0f
		};

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB , GL_FLOAT, data);
	}

	Texture::~Texture() {	
		glDeleteTextures(1, &id_);
	}

	void Texture::Bind(unsigned int slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, id_);
	}


	unsigned int* Texture::GetId() {
		return &id_;
	}

	const int Texture::GetWidth() const {
		return width_;
	}

	const int Texture::GetHeight() const {
		return height_;
	}
}