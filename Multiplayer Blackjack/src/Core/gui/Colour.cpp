#include "Colour.hpp"
#include <sstream>

namespace blackjack::core {
	std::string operator+(const std::string& str, const Colour& col) {
		std::stringstream ss;
		ss << (int)col.r << "_" << (int)col.g << "_" << (int)col.b << "_" << (int)col.a;
		return str + ss.str();
	}

	Colour::Colour(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {
	}

	Colour::Colour() : r(255), g(255), b(255), a(255) {
	}
}