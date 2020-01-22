#include "Cube.h"

namespace Blackjack::Core {
	Cube::Cube() : Mesh(192, 36) {
		float vert[] = {
			0,0,0,0,0,-1,0,0,
			1,0,0,0,0,-1,1,0,
			1,1,0,0,0,-1,1,1,
			0,1,0,0,0,-1,0,1,

			1,0,1,0,0,1,0,0,
			0,0,1,0,0,1,1,0,
			0,1,1,0,0,1,1,1,
			1,1,1,0,0,1,0,1,

			0,0,1,-1,0,0,0,0,
			0,0,0,-1,0,0,1,0,
			0,1,0,-1,0,0,1,1,
			0,1,1,-1,0,0,0,1,

			1,0,0,1,0,0,0,0,
			1,0,1,1,0,0,1,0,
			1,1,1,1,0,0,1,1,
			1,1,0,1,0,0,0,1,

			0,1,0,0,1,0,0,0,
			1,1,0,0,1,0,1,0,
			1,1,1,0,1,0,1,1,
			0,1,1,0,1,0,0,1,

			0,0,1,0,-1,0,0,0,
			1,0,1,0,-1,0,1,0,
			1,0,0,0,-1,0,1,1,
			0,0,0,0,-1,0,0,1
		};

		for (int i = 0; i < 192; i++) {
			vertices_[i] = vert[i];
		}
		unsigned int ind[] = {
			0,1,2,2,3,0,
			4,5,6,6,7,4,
			8,9,10,10,11,8,
			12,13,14,14,15,12,
			16,17,18,18,19,16,
			20,21,22,22,23,20
		};

		for (int i = 0; i < 36; i++) {
			indices_[i] = ind[i];
		}
	}

	Cube::Cube(float x, float y, float z, float width, float height, float depth) : Mesh(24, 36) {
		vertices_[0] = x;
		vertices_[1] = y;
		vertices_[2] = z;

		vertices_[3] = x + width;
		vertices_[4] = y;
		vertices_[5] = z;

		vertices_[6] = x + width;
		vertices_[7] = y + height;
		vertices_[8] = z;

		vertices_[9] = x;
		vertices_[10] = y + height;
		vertices_[11] = z;

		vertices_[12] = x;
		vertices_[13] = y + height;
		vertices_[14] = z + depth;

		vertices_[15] = x + width;
		vertices_[16] = y + height;
		vertices_[17] = z + depth;


		vertices_[18] = x + width;
		vertices_[19] = y;
		vertices_[20] = z + depth;

		vertices_[21] = x;
		vertices_[22] = y;
		vertices_[23] = z + depth;






		//Front
		indices_[0] = 0;
		indices_[1] = 1;
		indices_[2] = 2;
		indices_[3] = 2;
		indices_[4] = 3;
		indices_[5] = 0;

		//Left
		indices_[6] = 0;
		indices_[7] = 7;
		indices_[8] = 4;
		indices_[9] = 4;
		indices_[10] = 3;
		indices_[11] = 0;

		//Bottom
		indices_[12] = 0;
		indices_[13] = 1;
		indices_[14] = 6;
		indices_[15] = 6;
		indices_[16] = 7;
		indices_[17] = 0;

		//Right
		indices_[18] = 1;
		indices_[19] = 6;
		indices_[20] = 5;
		indices_[21] = 5;
		indices_[22] = 2;
		indices_[23] = 1;

		//Top
		indices_[24] = 3;
		indices_[25] = 2;
		indices_[26] = 5;
		indices_[27] = 5;
		indices_[28] = 4;
		indices_[29] = 3;

		//Back
		indices_[30] = 7;
		indices_[31] = 6;
		indices_[32] = 5;
		indices_[33] = 5;
		indices_[34] = 4;
		indices_[35] = 7;
	}
}