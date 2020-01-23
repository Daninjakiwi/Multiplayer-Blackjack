#pragma once
#include "Core/Render/Meshes/Quad.hpp"

namespace blackjack {
	class Card : public core::Quad {
	public:
		Card(int value);
		Card();

		void setValue(int value);
	};
}
