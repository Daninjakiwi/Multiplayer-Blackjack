#include "Quad.h"

namespace Core {

	Quad::Quad(float x, float y, float z, float width, float height) : Mesh(12,6){
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

		m_indices[0] = 0;
		m_indices[1] = 1;
		m_indices[2] = 2;
		m_indices[3] = 2;
		m_indices[4] = 3;
		m_indices[5] = 0;
	}
}