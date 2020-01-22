#include "SceneGame.hpp"

namespace blackjack {
	SceneGame::SceneGame() : Scene(), renderer(), light(), camera(45.0f, 16.0f/9.0f), table(), card(), card_mesh(0),table_mesh(1,180) {
		renderer.SetCamera(camera);
		renderer.SetLight(light);

		camera.TranslateX(2.0f);
		camera.TranslateY(8.63f);
		camera.TranslateZ(14.7f);
		camera.Pitch(-40);

		light.setAmbient(0.2f, 0.2f, 0.2f);
		light.setDiffuse(0.4f, 0.4f, 0.4f);
		light.setSpecular(0.3f, 0.3f, 0.3f);
		light.setPosition(2.5f, 10, -10.0f);

		core::Material* card_material = core::Resources::CreateMaterial("CardMaterial", core::Resources::CreateShader("Texture", "res/texture"));
		card_material->SetUniform("u_material.diffuse", core::UniformType::TEXTURE2D, core::Resources::CreateTexture("cards", "res/Cards.png"));
		card_material->SetUniform1f("u_material.shininess", 32.0f);

		card.SetMesh(&card_mesh);
		card.SetMaterial(card_material);

		card.GetTransform().SetRotation(-90, 0, 0);
		card.GetTransform().SetPosition(3, 0.15f, 5);

		core::Material* table_material = core::Resources::CreateMaterial("TableMaterial", core::Resources::GetShader("Texture"));
		table_material->SetUniform("u_material.diffuse", core::UniformType::TEXTURE2D, core::Resources::CreateTexture("felt", "res/table.png"));
		table_material->SetUniform1f("u_material.shininess", 64.0f);

		table.SetMesh(&card_mesh);
		table.SetMaterial(table_material);

		table.GetTransform().SetPosition(2, 0, 0);
		table.GetTransform().SetScale(10, 0.1f, 10);
		table.GetTransform().SetRotation(0, 180, 0);
	}

	void SceneGame::Update(float delta) {
	}

	void SceneGame::Draw() {
		renderer.Draw(table);
		renderer.Draw(card);
		renderer.Flush();
	}
}