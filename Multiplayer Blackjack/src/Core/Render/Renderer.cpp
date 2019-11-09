#include "Renderer.h"
#include "glad/glad.h"

namespace Core {
	void Renderer::drawTriangleLegacy(float width, float height, float x, float y) {
		glBegin(GL_TRIANGLES);
		glVertex3f(x-(width/2), y-(height/2), 0.0f);
		glVertex3f(x+(width/2), y-(height/2), 0.0f);
		glVertex3f(x, y+(height/2), 0.0f);
		glEnd();
	}
}