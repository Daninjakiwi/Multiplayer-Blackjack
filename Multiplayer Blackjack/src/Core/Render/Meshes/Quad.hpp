#pragma once
#include "Mesh.hpp"

namespace blackjack::core {
	class Quad : public Mesh {
	public:
		friend class Card2;
		Quad(float x, float y, float z, float width, float height);
	};
}
