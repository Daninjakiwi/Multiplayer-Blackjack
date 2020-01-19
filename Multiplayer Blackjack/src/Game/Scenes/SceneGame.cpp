#include "SceneGame.h"

namespace Blackjack {
	SceneGame::SceneGame() : Scene(), renderer(), light(), camera(45.0f, 16.0f/9.0f), table(), card(), table_mesh(1,180), card_mesh(0){
		renderer.setCamera(camera);
		renderer.setLight(light);

		camera.translateX(1.66f);
		camera.translateY(8.63f);
		camera.translateZ(14.7f);
		camera.pitch(-40);

		light.setAmbient(0.2f, 0.2f, 0.2f);
		light.setDiffuse(0.4f, 0.4f, 0.4f);
		light.setSpecular(0.3f, 0.3f, 0.3f);
		light.setPosition(2.5f, 10, -10.0f);

		Core::Material* card_material = Core::ResourceManager::createMaterial("CardMaterial", Core::ResourceManager::createShader("Texture", "res/texture"));
		card_material->setUniform("u_material.diffuse", Core::UniformType::TEXTURE2D, Core::ResourceManager::createTexture("cards", "res/Cards.png"));
		card_material->setUniform1f("u_material.shininess", 32.0f);

		card.setMesh(&card_mesh);
		card.setMaterial(card_material);

		card.getTransform().setRotation(-90, 0, 0);
		card.getTransform().setPosition(3, 0.15f, 5);

		Core::Material* table_material = Core::ResourceManager::createMaterial("TableMaterial", Core::ResourceManager::getShader("Texture"));
		table_material->setUniform("u_material.diffuse", Core::UniformType::TEXTURE2D, Core::ResourceManager::createTexture("felt", "res/table.png"));
		table_material->setUniform1f("u_material.shininess", 64.0f);

		table.setMesh(&table_mesh);
		table.setMaterial(table_material);

		table.getTransform().setPosition(2, 0, 0);
		table.getTransform().setScale(10, 0.1f, 10);
		table.getTransform().setRotation(0, 180, 0);
	}

	void SceneGame::update(float delta) {
	}

	void SceneGame::draw() {
		renderer.draw(table);
		renderer.draw(card);
		renderer.flush();
	}
}