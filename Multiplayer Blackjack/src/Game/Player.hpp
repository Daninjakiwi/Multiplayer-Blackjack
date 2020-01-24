#pragma once
#include <string>
#include <vector>

#include "Card.hpp"

namespace blackjack {
	struct Player {
		std::string name;
		std::vector<int> cards;
		int bet;

		Player(const std::string& name);
		Player();
	};
}