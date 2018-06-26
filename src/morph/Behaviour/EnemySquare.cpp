#include "SDL2/SDL.h"
#include "EnemySquare.hpp"
#include "Physics.hpp"

bool BehaviourEnemySquare::update(Engine* engine, Actor* actor) {
	std::shared_ptr<Actor> player = engine->getHero();
	bool playerIsHit = false,
		 actorIsHit = false;
	for (auto const& attack : player->getAttacks()) {
		if (physics::areRectIntersecting(attack.second, actor->getHitbox())&& !actor->hasInvincibilityFrame()) {
			actorIsHit = true;
		}
	}
	for (auto const& attack : actor->getAttacks()) {
		if (physics::areRectIntersecting(attack.second, player->getHitbox())) {
			playerIsHit = true;
		}
	}

	if (actorIsHit) {
		actor->setHealth(actor->getHealth() - player->getAttack());
		actor->setInvincibilityFrame();
	}
	else if (playerIsHit) {
		player->setHealth(player->getHealth() - actor->getAttack());
	}
	else {
		int direction = actor->canTouch(player.get());
		if (direction != -1) {
			actor->attack(direction);
		}
	}
	// if player's attack is touching the actor
	//		remove health
	// else if is attacking and touching player
	//		remove health from player
	// else if is at reach from player
	//		attack
	// else
	//		move towards player
	return true;
}
