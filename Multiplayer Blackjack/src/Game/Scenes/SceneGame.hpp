#pragma once
#include "Core/Core.hpp"
#include "Core/Scene.hpp"
#include "../Card.hpp"
#include "Core/Render/Meshes/CircleSegment.hpp"

namespace blackjack {
	class SceneGame : public core::Scene {
	private:
		core::Renderer3D renderer;
		core::Light light;
		core::Camera camera;
		
		core::RenderObject table;
		core::RenderObject card;


		core::CircleSegment table_mesh;
		Card card_mesh;
	public:
		SceneGame();

		void Update(float delta);

		void Draw();
	};
}
