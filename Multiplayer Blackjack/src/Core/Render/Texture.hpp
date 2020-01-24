#pragma once
#include <string>
#include <memory>
#include <unordered_map>

namespace blackjack::core {
	class Texture {
	private:
		static std::unordered_map<std::string, std::unique_ptr<Texture>> textures_;

		unsigned int id_;
		int width_, height_;
	public:
		static void Load(const std::string& name);
		static Texture* Get(const std::string& name);

		Texture(const std::string& file_path);
		~Texture();

		Texture(bool test);

		void Bind(unsigned int slot = 0) const;

		unsigned int* GetId();

		const int GetWidth() const;
		const int GetHeight() const;
	};
}