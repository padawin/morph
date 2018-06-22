#include "Attack.hpp"
#include "Map.hpp"
#include "Actor.hpp"
#include <memory>

bool AttackCommand::execute(Actor* actor, int xDest, int yDest) {
	int direction = -1;
	if (xDest > 0) {
		direction = ATTACK_RIGHT;
	}
	else if (xDest < 0) {
		direction = ATTACK_LEFT;
	}
	else if (yDest > 0) {
		direction = ATTACK_DOWN;
	}
	else if (yDest < 0) {
		direction = ATTACK_UP;
	}
	if (direction != -1) {
		actor->attack(direction);
		return true;
	}
	return false;
}
