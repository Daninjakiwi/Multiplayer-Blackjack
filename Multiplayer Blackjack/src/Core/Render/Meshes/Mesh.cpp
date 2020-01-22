#include <memory>

#include "Core/Log.hpp"
#include "Mesh.hpp"

namespace blackjack::core {
	Mesh::Mesh(int vertex_count, int indices_count) : vertices_(nullptr), indices_(nullptr), vertex_count_(vertex_count), indices_count_(indices_count){
		vertices_ = (float*)malloc(vertex_count * sizeof(float));
		indices_ = (unsigned int*)malloc(indices_count * sizeof(unsigned int));
	}

	Mesh::~Mesh() {
		if (vertex_count_ != 0) {
			free(vertices_);
		}
		if (indices_count_ != 0) {
			free(indices_);
		}

	}

	float* Mesh::GetVertices() {
		return vertices_;
	}

	unsigned int* Mesh::GetIndices() {
		return indices_;
	}

	int Mesh::GetVertexCount() const {
		return vertex_count_;
	}

	int Mesh::GetIndicesCount() const {
		return indices_count_;
	}


	const float& Mesh::GetVertexAt(int index) const {
		if (index < vertex_count_) {
			return vertices_[index];
		}
		else {
			COREERROR(INVALID_ARGUMENT_ERROR);
		}
	}

	const unsigned int& Mesh::GetIndexAt(int index) const {
		if (index < indices_count_) {
			return indices_[index];
		}
		else {
			COREERROR(INVALID_ARGUMENT_ERROR);
		}
	}

	void Mesh::ResizeVertices(int new_size) {
		if (new_size < 0) {
			COREERROR(INVALID_ARGUMENT_ERROR);
		}
		else {
			if (new_size == 0) {
				free(vertices_);
				vertex_count_ = 0;
			}
			else {
				void* temp;
				if (vertex_count_ == 0) {
					temp = malloc(sizeof(float) * new_size);
				}
				else {
					temp = realloc(vertices_, sizeof(float) * new_size);
				}
				if (temp != nullptr) {
					vertices_ = (float*)temp;
					vertex_count_ = new_size;
				}
				else {
					COREFATAL(HEAP_ALLOCATION_ERROR);
				}
			}

		}
	}

	void Mesh::ResizeIndices(int new_size) {
		if (new_size < 0) {
			COREERROR(INVALID_ARGUMENT_ERROR);
		}
		else {
			if (new_size == 0) {
				free(indices_);
				indices_count_ = 0;
			}
			else {
				void* temp;
				if (indices_count_ == 0) {
					temp = malloc(sizeof(unsigned int) * new_size);
				}
				else {
					temp = realloc(indices_, sizeof(unsigned int) * new_size);
				}
				if (temp != nullptr) {
					indices_ = (unsigned int*)temp;
					indices_count_ = new_size;
				}
				else {
					COREFATAL(HEAP_ALLOCATION_ERROR);
				}
			}
		}
	}
}