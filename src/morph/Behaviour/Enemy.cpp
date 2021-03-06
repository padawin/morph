#include "SDL2/SDL.h"
#include "Enemy.hpp"
#include "Physics.hpp"
#include "Command/Move.hpp"

bool BehaviourEnemy::update(Engine* engine, Actor* actor) {
	Actor* player = engine->getHero().get();
	bool playerIsHit = false,
		 actorIsHit = false;
	for (auto const& playerAttack : player->getAttacks()) {
		if (physics::areRectIntersecting(playerAttack.second, actor->getHitbox())&& !actor->hasInvincibilityFrame()) {
			actorIsHit = true;
			goto testHitPlayer;
		}
		for (auto const& actorAttack : actor->getAttacks()) {
			if (physics::areRectIntersecting(playerAttack.second, actorAttack.second)) {
				actor->cancelAttacks();
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
		E_ActorAttack attack = actor->canTouch(player);
		if (attack != NO_ATTACK) {
			actor->attack(attack);
		}
		else {
			_move(engine, actor, player);
		}
	}
	return true;
}

void BehaviourEnemy::_move(Engine* engine, Actor* actor, Actor* player) {
	// move
	Vector2D direction = player->getPosition() - actor->getPosition();
	direction.normalize();

	MoveCommand cmd = MoveCommand();
	cmd.execute(actor, direction, engine->getMap(), false);
}
