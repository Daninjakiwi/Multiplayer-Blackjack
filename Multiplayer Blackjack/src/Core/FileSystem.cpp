#include <fstream>
#include <sstream>

#include "FileSystem.h"

namespace Core {
	std::string FileSystem::loadFile(const char* filepath) {
		std::ifstream stream(filepath);
		std::stringstream ss;

		if (!stream.fail()) {
			ss << stream.rdbuf();
			stream.close();
		}
		return ss.str();
	}

	std::string FileSystem::loadFile(const std::string& filepath) {
		return loadFile(filepath.c_str());
	}
}