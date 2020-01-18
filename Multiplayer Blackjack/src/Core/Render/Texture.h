#pragma once
#include <string>

namespace Blackjack::Core {
	class Texture {
	private:
		unsigned int m_id;
	public:
		Texture(const std::string& filepath);
		~Texture();

		void bind(unsigned int slot = 0) const;

		unsigned int* getId();
	};
}