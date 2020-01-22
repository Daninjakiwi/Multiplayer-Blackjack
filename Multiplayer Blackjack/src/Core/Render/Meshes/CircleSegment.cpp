#include <cmath>
#include <iostream>
#include <glm/glm.hpp>

#include "CircleSegment.hpp"

#define PI 3.14159265

namespace blackjack::core {
	CircleSegment::CircleSegment(float radius, float degrees, unsigned int segments) : Mesh(((segments + 2) * 8 * 2) + ((segments+2) * 32), (segments * 3 * 2) + (6*(segments+2))) {
		float d = PI * degrees / segments / 180;

		int face_vertices = segments + 2;


		float mapy = 0.8f / 2.0f;
		float mapx = -1.0f / 2.0f;

		//Bottom plate

		vertices_[0] = 0;
		vertices_[1] = 0;
		vertices_[2] = 0;
		vertices_[3] = 0;
		vertices_[4] = -1;
		vertices_[5] = 0;
		vertices_[6] = 0.5f;
		vertices_[7] = 0.5f;

		for (int i = 1; i < segments + 2; i++) {
			vertices_[8 * i] = -radius * cos(d * (i - 1));
			vertices_[(8 * i) + 1] = 0;
			vertices_[(8 * i) + 2] = -radius * sin(d * (i - 1));
			vertices_[(8 * i) + 3] = 0;
			vertices_[(8 * i) + 4] = -1;
			vertices_[(8 * i) + 5] = 0;
			vertices_[(8 * i) + 6] = mapx * (cos(d * (i - 1)) - 1);
			vertices_[(8 * i) + 7] = mapy * (sin(d * (i - 1)) + 1);
		}

		for (int i = 0; i < segments * 3; i++) {
			if (i % 3 == 0) {
				indices_[i] = 0;
			}
			if (i % 3 == 1) {
				indices_[i] = ceil(((float)i) / 3);
			}
			if (i % 3 == 2) {
				indices_[i] = 1 + ceil(((float)i) / 3);
			}
		}

		//TOP PLATE

		int offset = (segments + 2) * 8;

		vertices_[offset] = 0;
		vertices_[offset + 1] = 1;
		vertices_[offset + 2] = 0;
		vertices_[offset + 3] = 0;
		vertices_[offset + 4] = 1;
		vertices_[offset + 5] = 0;
		vertices_[offset + 6] = 0.5f;
		vertices_[offset + 7] = 0.4f;

		for (int i = 1; i < segments + 2; i++) {
			vertices_[(8 * i) + offset] = -radius * cos(d * (i - 1));
			vertices_[(8 * i) + 1 + offset] = 1;
			vertices_[(8 * i) + 2 + offset] = -radius * sin(d * (i - 1));
			vertices_[(8 * i) + 3 + offset] = 0;
			vertices_[(8 * i) + 4 + offset] = 1;
			vertices_[(8 * i) + 5 + offset] = 0;
			vertices_[(8 * i) + 6 + offset] = mapx * (cos(d * (i - 1)) - 1);//abs(cos(d * (i - 1)));//abs((d * (i - 1)) / (d * segments / 2) - 1);
			vertices_[(8 * i) + 7 + offset] = mapy * (sin(d * (i - 1)) + 1);//(sin(d * (i - 1)) / 2) + 0.5f;
		}

		int nuvertices_ = segments + 2;
		offset = segments * 3;

		for (int i = 0; i < segments * 3; i++) {
			if (i % 3 == 0) {
				indices_[offset + i] = nuvertices_;
			}
			if (i % 3 == 1) {
				indices_[offset + i] = nuvertices_ + ceil(((float)i) / 3);
			}
			if (i % 3 == 2) {
				indices_[offset + i] = nuvertices_ + 1 + ceil(((float)i) / 3);
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
			int original = ((int)floor((k - j) / 2) % (vert_start / 2)) + count;

			Vertex v = GetVertex(original);

			int vert = floor((i % vert_start) / 2);
			float angle = 0;

			if (vert == 0) {
				angle = 270;
			}
			else if (vert < segments + 1) {
				angle = (deg * (vert - 1)) + n;
			}
			else {
				angle = degrees + 90;
			}

			SetVertexPos(vert_start + i, v.x, v.y, v.z);

			SetVertexNormal(vert_start + i, -cos(glm::radians(angle)), 0, -sin(glm::radians(angle)));

			float uvx = angle / 360;
			float uvy = 1.0f;

			if (count == 0) {
				uvy = 0.8f;
			}

			SetVertexUv(vert_start + i, uvx, uvy);
		}

		offset = segments * 6;

		for (int i = 0; i < segments + 2; i++) {
			int pos = (6 * i) + offset;
			indices_[pos] = vert_start + (2 * i);
			indices_[pos + 1] = vert_start + (2 * i) + 1;
			indices_[pos + 2] = (2 * vert_start) + (2 * i);
			indices_[pos + 3] = (2 * vert_start) + (2 * i);
			indices_[pos + 4] = (2 * vert_start) + (2 * i) + 1;
			indices_[pos + 5] = vert_start + (2 * i) + 1;
		}
	}

	void CircleSegment::SetVertexPos(int vert_num, float x, float y, float z) {
		vertices_[8 * vert_num] = x;
		vertices_[(8 * vert_num) + 1] = y;
		vertices_[(8 * vert_num) + 2] = z;
	}
	void CircleSegment::SetVertexNormal(int vert_num, float nx, float ny, float nz) {
		vertices_[(8 * vert_num) + 3] = nx;
		vertices_[(8 * vert_num) + 4] = ny;
		vertices_[(8 * vert_num) + 5] = nz;
	}
	void CircleSegment::SetVertexUv(int vert_num, float uvx, float uvy) {
		vertices_[(8 * vert_num) + 6] = uvx;
		vertices_[(8 * vert_num) + 7] = uvy;
	}

	Vertex CircleSegment::GetVertex(int vert_num) {
		Vertex v;
		v.x = vertices_[8 * vert_num];
		v.y = vertices_[(8 * vert_num) + 1];
		v.z = vertices_[(8 * vert_num) + 2];

		v.nx = vertices_[(8 * vert_num) + 3];
		v.ny = vertices_[(8 * vert_num) + 4];
		v.nz = vertices_[(8 * vert_num) + 5];

		v.uvx = vertices_[(8 * vert_num) + 6];
		v.uvy = vertices_[(8 * vert_num) + 7];

		return v;
	}
}