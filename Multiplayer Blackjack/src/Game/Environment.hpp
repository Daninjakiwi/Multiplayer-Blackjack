#pragma once
#include <string>

namespace blackjack {
	struct Environment {
		int base_width;
		int base_height;
		int window_width;
		int window_height;
		float scale_width;
		float scale_height;
		std::string username;
		std::string password;
		std::string token;
		std::string server_url;
		unsigned char state;
	};
}
