#include "Colour.h"
#include <sstream>

namespace Blackjack::Core {
	Shader* Colour::s_shader = nullptr;

	Colour::Colour(int r, int g, int b, int a) : m_r((float)(r) / 255.0f), m_g((float)g / 255.0f), m_b((float)b / 255.0f), m_a((float)a/255.0f) {
		if (s_shader == nullptr) {
			s_shader = Resources::CreateShader("ui_shader", "res/ui");
		}

		std::stringstream ss;
		ss << m_r << ":" << m_g << ":" << m_b << ":" << m_a;
		m_material = Resources::CreateMaterial(ss.str(), s_shader);
		//m_material->setUniform3f("u_colour", m_r, m_g, m_b);
		m_material->setUniform4f("u_colour", m_r, m_g, m_b, m_a);
	}

	Material* Colour::getColour(int r, int g, int b, int a) {
		float m_r = (float)r / 255;
		float m_g = (float)g / 255;
		float m_b = (float)b / 255;
		float m_a = (float)a / 255;
		if (s_shader == nullptr) {
			s_shader = Resources::CreateShader("ui_shader", "res/ui");
		}

		std::stringstream ss;
		ss << m_r << ":" << m_g << ":" << m_b << ":" << m_a;
		Material* mat = Resources::CreateMaterial(ss.str(), s_shader);
		mat->setUniform4f("u_colour", m_r, m_g, m_b, m_a);
		return mat;
	}

	Material* Colour::material() {
		return m_material;
	}
}