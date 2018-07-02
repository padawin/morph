#include "SDL2/SDL.h"
#include "EnemySquare.hpp"
#include "Physics.hpp"
#include "Command/Move.hpp"

bool BehaviourEnemySquare::update(Engine* engine, Actor* actor) {
	std::shared_ptr<Actor> player = engine->getHero();
	bool playerIsHit = false,
		 actorIsHit = false;
	for (auto const& playerAttack : player->getAttacks()) {
		if (physics::areRectIntersecting(playerAttack.second, actor->getHitbox())&& !actor->hasInvincibilityFrame()) {
			actorIsHit = true;
			goto testHitPlayer;
		}
		for (auto const& actorAttack : actor->getAttacks()) {
			if (physics::areRectIntersecting(playerAttack.second, actorAttack.second)) {
				actorIsHit = true;
				goto testHitPlayer;
			}
		}
	}
	for (auto const& attack : actor->getAttacks()) {
		if (physics::areRectIntersecting(attack.second, player->getHitbox())) {
			playerIsHit = true;
			break;
		}
	}

	testHitPlayer:
	if (actorIsHit) {
		actor->setHealth(actor->getHealth() - player->getAttack());
		actor->setInvincibilityFrame();
		actor->cancelAttacks();
	}
	else if (playerIsHit) {
		player->setHealth(player->getHealth() - actor->getAttack());
		actor->cancelAttacks();
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
			cmd.execute(actor, direction, engine->getMap(), false);
		}
	}
	return true;
}
