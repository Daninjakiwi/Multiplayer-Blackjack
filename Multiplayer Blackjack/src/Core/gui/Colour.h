#pragma once
#include "Core/ResourceManager.h"

namespace Blackjack::Core {
	class Colour {
	private:
		static Shader* s_shader;
		float m_r, m_g, m_b;
		Material* m_material;
	public:
		Colour(int r, int g, int b);

		Material* getMaterial();
	};
}
