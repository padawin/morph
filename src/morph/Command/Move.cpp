#include "Move.hpp"
#include "Map.hpp"
#include "Actor.hpp"

bool MoveCommand::execute(Actor* actor, Vector2D direction, Map& m) {
	int currX = actor->getX(),
		currY = actor->getY(),
		newX = currX + actor->getSpeed() / 2 * (int) direction.getX(),
		newY = currY + actor->getSpeed() / 2 * (int) direction.getY(),
		actorWidth = actor->getHitboxWidth() / 2,
		actorHeight = actor->getHitboxHeight() / 2;

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
	actor->setX(newX);
	actor->setY(newY);
	return true;
}
