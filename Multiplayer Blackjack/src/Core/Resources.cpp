#include <fstream>
#include <sstream>

#include "Resources.hpp"

namespace blackjack::core {


	std::string Resources::LoadFile(const char* filepath) {
		std::ifstream stream(filepath);
		std::stringstream ss;

		if (!stream.fail()) {
			ss << stream.rdbuf();
			stream.close();
		}
		return ss.str();
	}

	std::string Resources::LoadFile(const std::string& filepath) {
		return LoadFile(filepath.c_str());
	}

}