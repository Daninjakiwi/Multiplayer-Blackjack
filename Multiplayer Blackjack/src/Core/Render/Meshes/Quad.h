#pragma once
#include "Mesh.h"

namespace Blackjack::Core {
	class Quad : public Mesh {
	public:
		Quad(float x, float y, float z, float width, float height);
	};
}
