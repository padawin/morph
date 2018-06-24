#include "Player.hpp"
#include "Command/Attack.hpp"
#include "Command/Move.hpp"
#include "SDL2_framework/UserActions.h"
#include "SDL2_framework/ServiceProvider.h"

bool BehaviourPlayer::update(Engine* engine, Actor* actor) {
	_updatePlayerPosition(actor, engine);
	_tryAttack(actor);
	return true;
}

void BehaviourPlayer::_updatePlayerPosition(Actor* actor, Engine* engine) {
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

	int currX = actor->getX(),
		currY = actor->getY(),
		newX = currX + actor->getSpeed() * horizontalPressed,
		newY = currY + actor->getSpeed() * verticalPressed,
		actorWidth = actor->getHitboxWidth() / 2,
		actorHeight = actor->getHitboxHeight() / 2;

	auto m = engine->getMap();
	if (!m.areCoordinatesValid(newX - actorWidth, currY)) {
		newX = actorWidth;
	}
	else if (!m.areCoordinatesValid(newX + actorWidth, currY)) {
		newX = m.getWidth() - actorWidth;
	}
	if (!m.areCoordinatesValid(currX, newY - actorHeight)) {
		newY = actorHeight;
	}
	else if (!m.areCoordinatesValid(currX, newY + actorHeight)) {
		newY = m.getHeight() - actorHeight;
	}
	MoveCommand cmd = MoveCommand();
	cmd.execute(actor, newX, newY);
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
