#pragma once
#include <string>

namespace Blackjack::Core {
	class FileSystem {
	public:
		static std::string loadFile(const char* filepath);
		static std::string loadFile(const std::string& filepath);
	};
}