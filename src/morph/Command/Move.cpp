#include "Move.hpp"
#include "Map.hpp"
#include "Actor.hpp"

bool MoveCommand::execute(Actor* actor, Vector2D direction, Map& m, bool boundMap) {
	int actorSize = actor->getHitboxSize() / 2;
	double currX = actor->getX(),
		   currY = actor->getY(),
		   newX = currX + (double) actor->getSpeed() / 2 * direction.getX(),
		   newY = currY + (double) actor->getSpeed() / 2 * direction.getY();

	if (boundMap) {
		if (!m.areCoordinatesValid((int) (newX - actorSize), (int) currY)) {
			newX = actorSize;
		}
		else if (!m.areCoordinatesValid((int) (newX + actorSize), (int) currY)) {
			newX = m.getWidth() - actorSize;
		}
		if (!m.areCoordinatesValid((int) currX, (int) (newY - actorSize))) {
			newY = actorSize;
		}
		else if (!m.areCoordinatesValid((int) currX, (int) (newY + actorSize))) {
			newY = m.getHeight() - actorSize;
		}
	}
	actor->setX(newX);
	actor->setY(newY);
	return true;
}
