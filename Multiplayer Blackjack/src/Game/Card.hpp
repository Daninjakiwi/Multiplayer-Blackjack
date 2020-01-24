#pragma once
#include "Core/Render/Meshes/Quad.hpp"
#include "Core/Render/RenderObject.hpp"

namespace blackjack {

	class Card : public core::RenderObject {
	private:
	public:
		Card(int value=0);
		~Card();

		void SetValue(int value);
	};
}
