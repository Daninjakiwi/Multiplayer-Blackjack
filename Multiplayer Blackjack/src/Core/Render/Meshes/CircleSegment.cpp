#include "CircleSegment.h"
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>

#define PI 3.14159265

namespace Blackjack::Core {
	CircleSegment::CircleSegment(float radius, float degrees, unsigned int segments) : Mesh(((segments + 2) * 8 * 2) + ((segments+2) * 32), (segments * 3 * 2) + (6*(segments+2))) {
		setup2(radius, degrees, segments);
	}

	void CircleSegment::setVertexPos(int vert_num, float x, float y, float z) {
		m_vertices[8 * vert_num] = x;
		m_vertices[(8 * vert_num) + 1] = y;
		m_vertices[(8 * vert_num) + 2] = z;
	}
	void CircleSegment::setVertexNormal(int vert_num, float nx, float ny, float nz) {
		m_vertices[(8 * vert_num) + 3] = nx;
		m_vertices[(8 * vert_num) + 4] = ny;
		m_vertices[(8 * vert_num) + 5] = nz;
	}
	void CircleSegment::setVertexUv(int vert_num, float uvx, float uvy) {
		m_vertices[(8 * vert_num) + 6] = uvx;
		m_vertices[(8 * vert_num) + 7] = uvy;
	}

	Vertex CircleSegment::getVertex(int vert_num) {
		Vertex v;
		v.x = m_vertices[8 * vert_num];
		v.y = m_vertices[(8 * vert_num) + 1];
		v.z = m_vertices[(8 * vert_num) + 2];

		v.nx = m_vertices[(8 * vert_num) + 3];
		v.ny = m_vertices[(8 * vert_num) + 4];
		v.nz = m_vertices[(8 * vert_num) + 5];

		v.uvx = m_vertices[(8 * vert_num) + 6];
		v.uvy = m_vertices[(8 * vert_num) + 7];

		return v;
	}

	void CircleSegment::setup2(float radius, float degrees, unsigned int segments) {
		float d = PI * degrees / segments / 180;

		int face_vertices = segments + 2;


		float mapy = 0.8f / 2.0f;
		float mapx = -1.0f / 2.0f;

		//Bottom plate

		m_vertices[0] = 0;
		m_vertices[1] = 0;
		m_vertices[2] = 0;
		m_vertices[3] = 0;
		m_vertices[4] = -1;
		m_vertices[5] = 0;
		m_vertices[6] = 0.5f;
		m_vertices[7] = 0.5f;

		for (int i = 1; i < segments + 2; i++) {
			m_vertices[8 * i] = -radius * cos(d * (i - 1));
			m_vertices[(8 * i) + 1] = 0;
			m_vertices[(8 * i) + 2] = -radius * sin(d * (i - 1));
			m_vertices[(8 * i) + 3] = 0;
			m_vertices[(8 * i) + 4] = -1;
			m_vertices[(8 * i) + 5] = 0;
			m_vertices[(8 * i) + 6] = mapx * (cos(d * (i - 1)) - 1);
			m_vertices[(8 * i) + 7] = mapy * (sin(d * (i - 1)) + 1);
		}

		for (int i = 0; i < segments * 3; i++) {
			if (i % 3 == 0) {
				m_indices[i] = 0;
			}
			if (i % 3 == 1) {
				m_indices[i] = ceil(((float)i) / 3);
			}
			if (i % 3 == 2) {
				m_indices[i] = 1 + ceil(((float)i) / 3);
			}
		}

		//TOP PLATE

		int offset = (segments + 2) * 8;

		m_vertices[offset] = 0;
		m_vertices[offset+1] = 1;
		m_vertices[offset+2] = 0;
		m_vertices[offset+3] = 0;
		m_vertices[offset+4] = 1;
		m_vertices[offset+5] = 0;
		m_vertices[offset+6] = 0.5f;
		m_vertices[offset+7] = 0.4f;

		for (int i = 1; i < segments + 2; i++) {
			m_vertices[(8 * i) + offset] = -radius * cos(d * (i - 1));
			m_vertices[(8 * i) + 1 + offset] = 1;
			m_vertices[(8 * i) + 2 + offset] = -radius * sin(d * (i - 1));
			m_vertices[(8 * i) + 3 + offset] = 0;
			m_vertices[(8 * i) + 4 + offset] = 1;
			m_vertices[(8 * i) + 5 + offset] = 0;
			m_vertices[(8 * i) + 6 + offset] = mapx * (cos(d * (i - 1)) - 1);//abs(cos(d * (i - 1)));//abs((d * (i - 1)) / (d * segments / 2) - 1);
			m_vertices[(8 * i) + 7 + offset] = mapy * (sin(d * (i - 1)) + 1);//(sin(d * (i - 1)) / 2) + 0.5f;
		}

		int num_vertices = segments + 2;
		offset = segments * 3;

		for (int i = 0; i < segments * 3; i++) {
			if (i % 3 == 0) {
				m_indices[offset+i] = num_vertices;
			}
			if (i % 3 == 1) {
				m_indices[offset+i] = num_vertices + ceil(((float)i) / 3);
			}
			if (i % 3 == 2) {
				m_indices[offset + i] = num_vertices + 1 + ceil(((float)i) / 3);
			}
		}


		//Side quads

		float deg = degrees / segments;
		float n = 90 - ((180 - deg) / 2);

		int vert_start = 2 * (segments + 2);

		for (int i = 0; i < 2 * vert_start; i++) {
			int j = vert_start - 1;
			int k = vert_start + i;
			int count = ((int)floor(i / vert_start) * (vert_start / 2));
			int original = ((int)floor((k-j)/2) % (vert_start/2)) + count;

			Vertex v = getVertex(original);

			int vert = floor((i % vert_start) / 2);
			float angle = 0;

			if (vert == 0) {
				angle = 270;
			}
			else if (vert < segments + 1) {
				angle = (deg * (vert-1)) + n;
			}
			else {
				angle = degrees + 90;
			}

			setVertexPos(vert_start + i, v.x, v.y, v.z);

			setVertexNormal(vert_start + i, -cos(glm::radians(angle)), 0, -sin(glm::radians(angle)));

			float uvx = angle/360;
			float uvy = 1.0f;

			if (count == 0) {
				uvy = 0.8f;
			}

			setVertexUv(vert_start + i, uvx, uvy);
		}

		offset = segments * 6;

		for (int i = 0; i < segments + 2; i++) {
			int pos = (6 * i) + offset;
			m_indices[pos] = vert_start + (2*i);
			m_indices[pos+1] = vert_start + (2*i) + 1;
			m_indices[pos+2] = (2*vert_start) + (2*i);
			m_indices[pos+3] = (2*vert_start) + (2*i);
			m_indices[pos+4] = (2*vert_start) + (2*i) + 1;
			m_indices[pos + 5] = vert_start + (2 * i) + 1;
		}
	}
}