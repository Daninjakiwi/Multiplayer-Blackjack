#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include "glad/glad.h"
#include "stb_image/stb_image.h"

#include "Core/Log.hpp"
#include "Texture.hpp"


namespace blackjack::core {

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