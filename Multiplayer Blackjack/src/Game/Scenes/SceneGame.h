#pragma once
#include "Core/Core.hpp"
#include "Core/Scene.hpp"
#include "../Card.h"
#include "Core/Render/Meshes/CircleSegment.h"

namespace Blackjack {
	class SceneGame : public Core::Scene {
	private:
		Core::Renderer3D renderer;
		Core::Light light;
		Core::Camera camera;

		Core::RenderObject table;
		Core::RenderObject card;


		//Core::CircleSegment table_mesh;
		Card card_mesh;
	public:
		SceneGame();

		void Update(float delta);

		void Draw();
	};
}
