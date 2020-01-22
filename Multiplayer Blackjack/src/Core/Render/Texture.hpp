#pragma once
#include <string>

namespace blackjack::core {
	class Texture {
	private:
		unsigned int id_;
		int width_, height_;
	public:
		Texture(const std::string& file_path);
		~Texture();

		void Bind(unsigned int slot = 0) const;

		unsigned int* GetId();

		const int GetWidth() const;
		const int GetHeight() const;
	};
}