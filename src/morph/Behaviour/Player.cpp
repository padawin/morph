#include "Player.hpp"
#include "Command/Attack.hpp"
#include "Command/Move.hpp"
#include "SDL2_framework/UserActions.h"
#include "SDL2_framework/ServiceProvider.h"

bool BehaviourPlayer::update(__attribute__((unused)) Engine* engine, Actor* actor) {
	_updatePlayerPosition(actor);
	_tryAttack(actor);
	return true;
}

void BehaviourPlayer::_updatePlayerPosition(Actor* actor) {
	char verticalPressed = 0;
	char horizontalPressed = 0;
	UserActions* userActions = ServiceProvider::getUserActions();
	if (userActions->getActionState("MOVE_PLAYER_UP")) {
		verticalPressed = -1;
	}
	else if (userActions->getActionState("MOVE_PLAYER_DOWN")) {
		verticalPressed = 1;
	}
	else {
		verticalPressed = 0;
	}
	if (userActions->getActionState("MOVE_PLAYER_LEFT")) {
		horizontalPressed = -1;
	}
	else if (userActions->getActionState("MOVE_PLAYER_RIGHT")) {
		horizontalPressed = 1;
	}
	else {
		horizontalPressed = 0;
	}

	MoveCommand cmd = MoveCommand();
	cmd.execute(
		actor,
		actor->getX() + actor->getSpeed() * horizontalPressed,
		actor->getY() + actor->getSpeed() * verticalPressed
	);
}

void BehaviourPlayer::_tryAttack(Actor* actor) {
	AttackCommand cmd = AttackCommand();
	UserActions* userActions = ServiceProvider::getUserActions();
	if (userActions->getActionState("ATTACK_UP")) {
		cmd.execute(actor, 0, -1);
	}
	if (userActions->getActionState("ATTACK_RIGHT")) {
		cmd.execute(actor, 1, 0);
	}
	if (userActions->getActionState("ATTACK_DOWN")) {
		cmd.execute(actor, 0, 1);
	}
	if (userActions->getActionState("ATTACK_LEFT")) {
		cmd.execute(actor, -1, 0);
	}
}
