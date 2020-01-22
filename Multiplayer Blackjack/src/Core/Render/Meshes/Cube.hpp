#pragma once
#include "Core/Transform.hpp"
#include "Mesh.hpp"

namespace blackjack::core {
	class Cube : public Mesh {
	public:
		Cube(float x, float y, float z, float width, float height, float depth);
		Cube();
	};
}
