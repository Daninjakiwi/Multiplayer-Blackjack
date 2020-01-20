#include "Scene.hpp"

namespace Blackjack::Core {
	int Scene::state_ = 0;

	Scene::Scene()  {
	}

	int Scene::GetState() {
		return state_;
	}

	void Scene::SetState(int state) {
		state_ = state;
	}
}