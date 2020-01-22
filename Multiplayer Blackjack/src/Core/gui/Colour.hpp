#pragma once
#include "Core/Resources.hpp"

namespace blackjack::core {
	struct Colour {
		unsigned char r, g, b, a;

		Colour(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
		Colour();
	};

	std::string operator+(const std::string& str, const Colour& col);
}
