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
			m_vertices[i] = vert[i];
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
			m_indices[i] = ind[i];
		}
	}

	Cube::Cube(float x, float y, float z, float width, float height, float depth) : Mesh(24, 36) {
		m_vertices[0] = x;
		m_vertices[1] = y;
		m_vertices[2] = z;

		m_vertices[3] = x + width;
		m_vertices[4] = y;
		m_vertices[5] = z;

		m_vertices[6] = x + width;
		m_vertices[7] = y + height;
		m_vertices[8] = z;

		m_vertices[9] = x;
		m_vertices[10] = y + height;
		m_vertices[11] = z;

		m_vertices[12] = x;
		m_vertices[13] = y + height;
		m_vertices[14] = z + depth;

		m_vertices[15] = x + width;
		m_vertices[16] = y + height;
		m_vertices[17] = z + depth;


		m_vertices[18] = x + width;
		m_vertices[19] = y;
		m_vertices[20] = z + depth;

		m_vertices[21] = x;
		m_vertices[22] = y;
		m_vertices[23] = z + depth;






		//Front
		m_indices[0] = 0;
		m_indices[1] = 1;
		m_indices[2] = 2;
		m_indices[3] = 2;
		m_indices[4] = 3;
		m_indices[5] = 0;

		//Left
		m_indices[6] = 0;
		m_indices[7] = 7;
		m_indices[8] = 4;
		m_indices[9] = 4;
		m_indices[10] = 3;
		m_indices[11] = 0;

		//Bottom
		m_indices[12] = 0;
		m_indices[13] = 1;
		m_indices[14] = 6;
		m_indices[15] = 6;
		m_indices[16] = 7;
		m_indices[17] = 0;

		//Right
		m_indices[18] = 1;
		m_indices[19] = 6;
		m_indices[20] = 5;
		m_indices[21] = 5;
		m_indices[22] = 2;
		m_indices[23] = 1;

		//Top
		m_indices[24] = 3;
		m_indices[25] = 2;
		m_indices[26] = 5;
		m_indices[27] = 5;
		m_indices[28] = 4;
		m_indices[29] = 3;

		//Back
		m_indices[30] = 7;
		m_indices[31] = 6;
		m_indices[32] = 5;
		m_indices[33] = 5;
		m_indices[34] = 4;
		m_indices[35] = 7;
	}
}