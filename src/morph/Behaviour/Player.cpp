#include "Player.hpp"
#include "Command/Move.hpp"
#include "SDL2_framework/UserActions.h"
#include "SDL2_framework/ServiceProvider.h"

bool BehaviourPlayer::update(Engine* engine, Actor* actor) {
	_updatePlayerPosition(actor, engine);
	_tryAttack(actor);
	return true;
}

void BehaviourPlayer::_updatePlayerPosition(Actor* actor, Engine* engine) {
	Vector2D direction;
	UserActions* userActions = ServiceProvider::getUserActions();
	if (userActions->getActionState("MOVE_PLAYER_UP")) {
		direction.setY(-1);
	}
	else if (userActions->getActionState("MOVE_PLAYER_DOWN")) {
		direction.setY(1);
	}
	if (userActions->getActionState("MOVE_PLAYER_LEFT")) {
		direction.setX(-1);
	}
	else if (userActions->getActionState("MOVE_PLAYER_RIGHT")) {
		direction.setX(1);
	}

	if (direction.getLength() > 0) {
		direction.normalize();
		MoveCommand cmd = MoveCommand();
		cmd.execute(actor, direction, engine->getMap(), true);
	}
}

void BehaviourPlayer::_tryAttack(Actor* actor) {
	UserActions* userActions = ServiceProvider::getUserActions();
	if (userActions->getActionState("ATTACK_UP") == PRESSED) {
		actor->attack(ATTACK_UP);
	}
	if (userActions->getActionState("ATTACK_RIGHT") == PRESSED) {
		actor->attack(ATTACK_RIGHT);
	}
	if (userActions->getActionState("ATTACK_DOWN") == PRESSED) {
		actor->attack(ATTACK_DOWN);
	}
	if (userActions->getActionState("ATTACK_LEFT") == PRESSED) {
		actor->attack(ATTACK_LEFT);
	}
}
