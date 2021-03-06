#include "SceneGame.hpp"
#include <cstdlib>

namespace blackjack {
	SceneGame::SceneGame() : Scene(), renderer(), light(), camera(45.0f, 16.0f/9.0f), table(), card(), table_mesh(1,180) {
		renderer.SetCamera(camera);
		renderer.SetLight(light);

		camera.TranslateX(2.0f);
		camera.TranslateY(8.63f);
		camera.TranslateZ(14.7f);
		camera.Pitch(-40);

		light.SetAmbient(0.2f, 0.2f, 0.2f);
		light.SetDiffuse(0.4f, 0.4f, 0.4f);
		light.SetSpecular(0.3f, 0.3f, 0.3f);
		light.SetPosition(2.5f, 10, -10.0f);

		core::Texture::Load("table.png");

		card.GetTransform().SetRotation(-90, 0, 0);
		card.GetTransform().SetPosition(3, 0.15f, 5);

		core::Material* table_material = core::Material::Create("TableMaterial", "texture");
		table_material->SetUniform("u_material.diffuse", core::UniformType::TEXTURE2D, core::Texture::Get("table.png"));
		table_material->SetUniform1f("u_material.shininess", 64.0f);

		table.SetMesh(&table_mesh);
		table.SetMaterial(table_material);

		table.GetTransform().SetPosition(2, 0, 0);
		table.GetTransform().SetScale(10, 0.1f, 10);
		table.GetTransform().SetRotation(0, 180, 0);
	}

	void SceneGame::Update(float delta) {
		table.GetTransform().Rotate(0, 360 * delta, 0);
		int val = rand() % 53;
		card.SetValue(val);
	}

	void SceneGame::Draw() {
		renderer.Draw(table);
		renderer.Draw(card);
		renderer.Flush();
	}
}