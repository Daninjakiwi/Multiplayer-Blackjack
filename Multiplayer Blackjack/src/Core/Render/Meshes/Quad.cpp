#include "Quad.hpp"

namespace blackjack::core {

	Quad::Quad(float x, float y, float z, float width, float height) : Mesh(32,6){
		vertices_[0] = x;
		vertices_[1] = y;
		vertices_[2] = z;
		vertices_[3] = 0;
		vertices_[4] = 0;
		vertices_[5] =1;
		vertices_[6] = 0;
		vertices_[7] = 0;

		vertices_[8] = x + width;
		vertices_[9] = y;
		vertices_[10] = z;
		vertices_[11] = 0;
		vertices_[12] = 0;
		vertices_[13] = 1;
		vertices_[14] = 1;
		vertices_[15] = 0;

		vertices_[16] = x + width;
		vertices_[17] = y + height;
		vertices_[18] = z;
		vertices_[19] = 0;
		vertices_[20] = 0;
		vertices_[21] = 1;
		vertices_[22] = 1;
		vertices_[23] = 1;

		vertices_[24] = x;
		vertices_[25] = y + height;
		vertices_[26] = z;
		vertices_[27] = 0;
		vertices_[28] = 0;
		vertices_[29] = 1;
		vertices_[30] = 0;
		vertices_[31] = 1;

		indices_[0] = 0;
		indices_[1] = 1;
		indices_[2] = 2;
		indices_[3] = 2;
		indices_[4] = 3;
		indices_[5] = 0;
	}
}