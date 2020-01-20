#pragma once
#include "Mesh.h"
#include "Core/Transform.hpp"

namespace Blackjack::Core {
	class Cube : public Mesh {
	public:
		Cube(float x, float y, float z, float width, float height, float depth);
		Cube();
	};
}
