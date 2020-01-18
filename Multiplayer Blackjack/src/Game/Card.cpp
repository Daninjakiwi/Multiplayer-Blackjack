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

		m_vertices[6] = col * xstep;
		m_vertices[7] = 1 - ((row+1) * ystep);

		m_vertices[14] = (col+1) * xstep;
		m_vertices[15] = 1 - ((row + 1) * ystep);

		m_vertices[22] = (col + 1) * xstep;
		m_vertices[23] = 1 - (row * ystep);

		m_vertices[30] = col * xstep;
		m_vertices[31] = 1 - (row * ystep);
	}
}