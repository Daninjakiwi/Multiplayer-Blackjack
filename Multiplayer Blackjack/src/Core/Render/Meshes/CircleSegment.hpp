#pragma once
#include "Mesh.hpp"

namespace blackjack::core {
	struct Vertex {
		float x;
		float y;
		float z;
		float nx;
		float ny;
		float nz;
		float uvx;
		float uvy;
	};

	class CircleSegment : public Mesh {
	public:
		CircleSegment(float radius, float degrees, int segments = 64);

		void SetVertexPos(int vert_num, float x, float y, float z);
		void SetVertexNormal(int vert_num, float nx, float ny, float nz);
		void SetVertexUv(int vert_num, float uvx, float uvy);

		Vertex GetVertex(int vert_num);
	};

}
