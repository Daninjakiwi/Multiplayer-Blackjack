#include "CircleSegment.h"
#include <cmath>

#define PI 3.14159265

namespace Core {
	CircleSegment::CircleSegment(float radius, float degrees, unsigned int segments) : Mesh((segments + 2) * 6, ((2 * segments) + 2) * 6) {
		float d = PI * degrees / segments / 180;

		float rot = PI * 0 / 180;

		m_vertices[0] = 0;
		m_vertices[1] = 0;
		m_vertices[2] = 0;

		for (int i = 1; i < segments + 2; i++) {
			m_vertices[3 * i] = -(radius * (cos((d * (i - 1)) + rot)));
			m_vertices[(3 * i) + 1] = 0;
			m_vertices[(3 * i) + 2] = -(radius * (sin((d * (i - 1)) + rot)));
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

		int start = ((segments + 2) * 3);

		m_vertices[start] = 0;
		m_vertices[start + 1] = 1;
		m_vertices[start + 2] = 0;

		for (int i = 1; i < segments + 2; i++) {
			m_vertices[start + (3 * i)] = -(radius * (cos((d * (i - 1)) + rot)));
			m_vertices[(3 * i) + 1 + start] = 1;
			m_vertices[(3 * i) + 2 + start] = -(radius * (sin((d * (i - 1)) + rot)));;
		}

		int start2 = segments * 3;

		for (int i = 0; i < segments * 3; i++) {
			if (i % 3 == 0) {
				m_indices[start2 + i] = start / 3;
			}
			if (i % 3 == 1) {
				m_indices[start2 + i] = (start / 3) + ceil(((float)i) / 3);
			}
			if (i % 3 == 2) {
				m_indices[start2 + i] = (start / 3) + (1 + ceil(((float)i) / 3));
			}
		}

		//Connecting quads

		start2 = segments * 6;

		start = start / 3;

		int part = 0;

		//(part + 5) % (2*(segments+2))

		for (int i = start2; i < ((2 * segments) + 2) * 6; i++) {
			if (i % 6 == 0) {
				m_indices[i] = part;
			}
			else if (i % 6 == 1) {
				m_indices[i] = (part + start) % (2 * (segments + 2));
			}
			else if (i % 6 == 2) {
				m_indices[i] = (part + 1) % (2 * (segments + 2));
			}
			else if (i % 6 == 3) {
				m_indices[i] = (part + 1) % (2 * (segments + 2));
			}
			else if (i % 6 == 4) {
				m_indices[i] = (part + 1 + start) % (2 * (segments + 2));
			}
			else if (i % 6 == 5) {
				m_indices[i] = (part + start) % (2 * (segments + 2));
				part += 1;
			}

		}
	}
}