#define STB_IMAGE_IMPLEMENTATION

#include "stb_image/stb_image.h"
#include "glad/glad.h"

#include "Texture.h"
#include <iostream>

namespace Blackjack::Core {

	Texture::Texture(const std::string& filepath) : m_id(0) {
		stbi_set_flip_vertically_on_load(true);
		int width, height, bpp;
		auto buffer = stbi_load(filepath.c_str(), &width, &height, &bpp, 4);

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		
		//glGenerateMipmap(GL_TEXTURE_2D);

		if (buffer) {
			stbi_image_free(buffer);
		}
	}

	Texture::~Texture() {
		glDeleteTextures(1, &m_id);
	}

	void Texture::bind(unsigned int slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}


	unsigned int* Texture::getId() {
		return &m_id;
	}
}