#pragma once

namespace Blackjack::Core {
	class Scene {
	public:
		static int state;

		Scene();

		virtual void update(float delta) = 0;
		virtual void draw() = 0;
	};
}
