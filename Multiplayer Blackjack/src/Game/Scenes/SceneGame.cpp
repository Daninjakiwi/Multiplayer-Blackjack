#include "SceneGame.h"

namespace Blackjack {
	SceneGame::SceneGame() : Scene(), renderer(), light(), camera(45.0f, 16.0f/9.0f), table(), card(), card_mesh(0) {//table_mesh(1,180)
		renderer.setCamera(camera);
		renderer.setLight(light);

		camera.TranslateX(2.0f);
		camera.TranslateY(8.63f);
		camera.TranslateZ(14.7f);
		camera.Pitch(-40);

		light.setAmbient(0.2f, 0.2f, 0.2f);
		light.setDiffuse(0.4f, 0.4f, 0.4f);
		light.setSpecular(0.3f, 0.3f, 0.3f);
		light.setPosition(2.5f, 10, -10.0f);

		Core::Material* card_material = Core::Resources::CreateMaterial("CardMaterial", Core::Resources::CreateShader("Texture", "res/texture"));
		card_material->setUniform("u_material.diffuse", Core::UniformType::TEXTURE2D, Core::Resources::CreateTexture("cards", "res/Cards.png"));
		card_material->setUniform1f("u_material.shininess", 32.0f);

		card.setMesh(&card_mesh);
		card.setMaterial(card_material);

		card.getTransform().SetRotation(-90, 0, 0);
		card.getTransform().SetPosition(3, 0.15f, 5);

		Core::Material* table_material = Core::Resources::CreateMaterial("TableMaterial", Core::Resources::GetShader("Texture"));
		table_material->setUniform("u_material.diffuse", Core::UniformType::TEXTURE2D, Core::Resources::CreateTexture("felt", "res/table.png"));
		table_material->setUniform1f("u_material.shininess", 64.0f);

		table.setMesh(&card_mesh);
		table.setMaterial(table_material);

		table.getTransform().SetPosition(2, 0, 0);
		table.getTransform().SetScale(10, 0.1f, 10);
		table.getTransform().SetRotation(0, 180, 0);
	}

	void SceneGame::Update(float delta) {
	}

	void SceneGame::Draw() {
		renderer.draw(table);
		renderer.draw(card);
		renderer.flush();
	}
}