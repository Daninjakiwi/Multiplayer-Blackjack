#pragma once
#include "Core/Render/Meshes/Quad.h"

namespace Blackjack {
	class Card : public Core::Quad {
	public:
		Card(unsigned int value);
		Card();

		void setValue(unsigned int value);
	};
}
