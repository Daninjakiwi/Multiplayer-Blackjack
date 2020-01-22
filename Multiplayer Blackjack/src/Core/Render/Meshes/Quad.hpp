#pragma once
#include "Mesh.hpp"

namespace blackjack::core {
	class Quad : public Mesh {
	public:
		Quad(float x, float y, float z, float width, float height);
	};
}
