#pragma once
#include "Mesh.h"

namespace Core {
	class CircleSegment : public Mesh {
	public:
		CircleSegment(float radius, float degrees, unsigned int segments = 32);
	};
}
