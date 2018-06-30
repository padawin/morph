#include "SDL2/SDL.h"
#include "EnemySquare.hpp"
#include "Physics.hpp"
#include "Command/Move.hpp"

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
		int attack = actor->canTouch(player.get());
		if (attack != -1) {
			actor->attack(attack);
		}
		else {
			// move
			Vector2D direction = player->getPosition() - actor->getPosition();
			direction.normalize();

			MoveCommand cmd = MoveCommand();
			cmd.execute(actor, direction, engine->getMap());
		}
	}
	return true;
}
