#pragma once
#include "Core/Resources.hpp"

namespace Blackjack::Core {
	class Colour {
	private:
		static Shader* s_shader;
		float m_r, m_g, m_b, m_a;
		Material* m_material;
	public:
		Colour(int r, int g, int b, int a=255);

		static Material* getColour(int r, int g, int b, int a = 255);

		Material* material();
	};
}
