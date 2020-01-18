#include "Quad.h"

namespace Blackjack::Core {

	Quad::Quad(float x, float y, float z, float width, float height) : Mesh(4 * 8,6){
		m_vertices[0] = x;
		m_vertices[1] = y;
		m_vertices[2] = z;
		m_vertices[3] = 0;
		m_vertices[4] = 0;
		m_vertices[5] =1;
		m_vertices[6] = 0;
		m_vertices[7] = 0;

		m_vertices[8] = x + width;
		m_vertices[9] = y;
		m_vertices[10] = z;
		m_vertices[11] = 0;
		m_vertices[12] = 0;
		m_vertices[13] = 1;
		m_vertices[14] = 1;
		m_vertices[15] = 0;

		m_vertices[16] = x + width;
		m_vertices[17] = y + height;
		m_vertices[18] = z;
		m_vertices[19] = 0;
		m_vertices[20] = 0;
		m_vertices[21] = 1;
		m_vertices[22] = 1;
		m_vertices[23] = 1;

		m_vertices[24] = x;
		m_vertices[25] = y + height;
		m_vertices[26] = z;
		m_vertices[27] = 0;
		m_vertices[28] = 0;
		m_vertices[29] = 1;
		m_vertices[30] = 0;
		m_vertices[31] = 1;

		m_indices[0] = 0;
		m_indices[1] = 1;
		m_indices[2] = 2;
		m_indices[3] = 2;
		m_indices[4] = 3;
		m_indices[5] = 0;
	}
}