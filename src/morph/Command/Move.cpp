#include "Move.hpp"
#include "Map.hpp"
#include "Actor.hpp"

bool MoveCommand::execute(Actor* actor, Vector2D direction, Map& m, bool boundMap) {
	int actorWidth = actor->getHitboxWidth() / 2,
		actorHeight = actor->getHitboxHeight() / 2;
	double currX = actor->getX(),
		   currY = actor->getY(),
		   newX = currX + (double) actor->getSpeed() / 2 * direction.getX(),
		   newY = currY + (double) actor->getSpeed() / 2 * direction.getY();

	if (boundMap) {
		if (!m.areCoordinatesValid((int) (newX - actorWidth), (int) currY)) {
			newX = actorWidth;
		}
		else if (!m.areCoordinatesValid((int) (newX + actorWidth), (int) currY)) {
			newX = m.getWidth() - actorWidth;
		}
		if (!m.areCoordinatesValid((int) currX, (int) (newY - actorHeight))) {
			newY = actorHeight;
		}
		else if (!m.areCoordinatesValid((int) currX, (int) (newY + actorHeight))) {
			newY = m.getHeight() - actorHeight;
		}
	}
	actor->setX(newX);
	actor->setY(newY);
	return true;
}
