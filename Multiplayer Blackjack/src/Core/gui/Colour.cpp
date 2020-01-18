#include "Colour.h"
#include <sstream>

namespace Blackjack::Core {
	Shader* Colour::s_shader = nullptr;

	Colour::Colour(int r, int g, int b) : m_r((float)(r) / 255.0f), m_g((float)g / 255.0f), m_b((float)b / 255.0f) {
		if (s_shader == nullptr) {
			s_shader = ResourceManager::createShader("ui_shader", "res/ui");
		}

		std::stringstream ss;
		ss << m_r << ":" << m_g << ":" << m_b;
		m_material = ResourceManager::createMaterial(ss.str(), s_shader);
		m_material->setUniform3f("u_colour", m_r, m_g, m_b);
	}

	Material* Colour::getMaterial() {
		return m_material;
	}
}