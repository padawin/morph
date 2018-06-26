#include "SDL2/SDL.h"
#include "EnemySquare.hpp"
#include "Physics.hpp"

bool BehaviourEnemySquare::update(Engine* engine, Actor* actor) {
	std::shared_ptr<Actor> player = engine->getHero();
	bool playerIsHit = false,
		 actorIsHit = false;
	for (SDL_Rect attack : player->getAttacks()) {
		if (physics::areRectIntersecting(attack, actor->getHitbox())&& !actor->hasInvincibilityFrame()) {
			actorIsHit = true;
		}
	}
	for (SDL_Rect attack : actor->getAttacks()) {
		if (physics::areRectIntersecting(attack, player->getHitbox())) {
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
