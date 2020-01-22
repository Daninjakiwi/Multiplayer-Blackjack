#pragma once

namespace blackjack::core {
	class Scene {
	private:
		static int state_;
	public:
		Scene();

		virtual void Update(float delta) = 0;
		virtual void Draw() = 0;

		static int GetState();
		static void SetState(int state);
	};
}
