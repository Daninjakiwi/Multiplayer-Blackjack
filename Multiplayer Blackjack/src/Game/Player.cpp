#include "Player.hpp"

namespace blackjack {
	Player::Player(const std::string& name) : name(name), bet(0){
	}

	Player::Player() : name("[PLAYER]"), bet(0) {
	}
}