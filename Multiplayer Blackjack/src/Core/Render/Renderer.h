#pragma once

namespace Core {
	class Renderer {
	private:
	public:
		Renderer() = default;
		~Renderer() = default;

		void drawTriangleLegacy(float width, float height, float x, float y);
	};
}
