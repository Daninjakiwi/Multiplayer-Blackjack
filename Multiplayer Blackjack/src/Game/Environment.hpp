#pragma once
#include <string>

namespace blackjack {
	struct Environment {
		int window_width;
		int window_height;
		std::string username;
		std::string password;
		std::string token;
	};
}
