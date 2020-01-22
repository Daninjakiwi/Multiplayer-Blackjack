#include "Card.h"
#include <math.h>
#include <iostream>

namespace Blackjack {
	Card::Card(unsigned int value) : Quad(0,0,0,1,1.53f) {
		setValue(value);
	}

	Card::Card() : Quad(0, 0, 0, 1, 1.53f) {
		setValue(0);
	}

	void Card::setValue(unsigned int value) {
		float xstep = 1 / 10.0f;
		float ystep = 1 / 8.0f;

		float row = floor(value / 10);
		float col = value % 10;

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