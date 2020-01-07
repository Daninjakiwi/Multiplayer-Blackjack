#pragma once
#include "Mesh.h"
#include "Core/Transform.h"

namespace Core {
	class Cube : public Mesh {
	public:
		Cube(float x, float y, float z, float width, float height, float depth);
		Cube();
	};
}
