#pragma once
#include <string>

namespace blackjack::core {

	class Resources {
	public:
		static std::string LoadFile(const char* filepath);
		static std::string LoadFile(const std::string& filepath);
	};
}
