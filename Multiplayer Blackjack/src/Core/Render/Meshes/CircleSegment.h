#pragma once
#include "Mesh.h"

namespace Blackjack::Core {
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
		CircleSegment(float radius, float degrees, unsigned int segments = 64);

		void setup2(float radius, float degrees, unsigned int segments);

		void setVertexPos(int vert_num, float x, float y, float z);
		void setVertexNormal(int vert_num, float nx, float ny, float nz);
		void setVertexUv(int vert_num, float uvx, float uvy);

		Vertex getVertex(int vert_num);
	};

}
