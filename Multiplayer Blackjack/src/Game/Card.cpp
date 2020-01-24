#include <math.h>
#include <iostream>
#include "Card.hpp"

namespace blackjack {
	Card::Card(int value) : RenderObject() {
		core::Quad* quad = new core::Quad(0, 0, 0, 1, 1.53f);
		mesh_ = quad;
		material_ = core::Material::Get("card_mat");

		SetValue(value);
	}

	Card::~Card() {
		delete mesh_;
	}

	void Card::SetValue(int value) {
		if (value >= 0) {
			float xstep = 1 / 10.0f;
			float ystep = 1 / 8.0f;

			float row = (float)floor(value / 10);
			float col = (float)(value % 10);

			mesh_->SetVertex(6, col * xstep);
			mesh_->SetVertex(7, 1 - ((row + 1) * ystep));
			mesh_->SetVertex(14, (col + 1) * xstep);
			mesh_->SetVertex(15, 1 - ((row + 1) * ystep));
			mesh_->SetVertex(22, (col + 1) * xstep);
			mesh_->SetVertex(23, 1 - (row * ystep));
			mesh_->SetVertex(30, col * xstep);
			mesh_->SetVertex(31, 1 - (row * ystep));
		}
	}
}