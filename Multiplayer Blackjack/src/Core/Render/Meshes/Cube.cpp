#include "Cube.h"

namespace Core {
	Cube::Cube() : Mesh(40, 36) {
		m_vertices[0] = 0;
		m_vertices[1] = 0;
		m_vertices[2] = 0;

		m_vertices[3] = 1;
		m_vertices[4] = 0;
		m_vertices[5] = 0;

		m_vertices[6] = 1;
		m_vertices[7] = 1;
		m_vertices[8] = 0;

		m_vertices[9] = 0;
		m_vertices[10] = 1;
		m_vertices[11] = 0;

		m_vertices[12] = 0;
		m_vertices[13] = 1;
		m_vertices[14] = 1;

		m_vertices[15] = 1;
		m_vertices[16] = 1;
		m_vertices[17] = 1;


		m_vertices[18] = 1;
		m_vertices[19] = 0;
		m_vertices[20] = 1;

		m_vertices[21] = 0;
		m_vertices[22] = 0;
		m_vertices[23] = 1;

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