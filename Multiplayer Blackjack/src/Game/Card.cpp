#include <math.h>
#include <iostream>
#include "Card.hpp"

namespace blackjack {
	Card::Card(int value) : Quad(0,0,0,1,1.53f) {
		setValue(value);
	}

	Card::Card() : Quad(0, 0, 0, 1, 1.53f) {
		setValue(0);
	}

	void Card::setValue(int value) {
		float xstep = 1 / 10.0f;
		float ystep = 1 / 8.0f;

		float row = (float)floor(value / 10);
		float col = (float)(value % 10);

		vertices_[6] = col * xstep;
		vertices_[7] = 1 - ((row+1) * ystep);

		vertices_[14] = (col+1) * xstep;
		vertices_[15] = 1 - ((row + 1) * ystep);

		vertices_[22] = (col + 1) * xstep;
		vertices_[23] = 1 - (row * ystep);

		vertices_[30] = col * xstep;
		vertices_[31] = 1 - (row * ystep);
	}
}