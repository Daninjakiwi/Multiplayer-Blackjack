#pragma once
#include "Core/Render/Meshes/Quad.hpp"

namespace blackjack {
	class Card : public core::Quad {
	public:
		Card(unsigned int value);
		Card();

		void setValue(unsigned int value);
	};
}
