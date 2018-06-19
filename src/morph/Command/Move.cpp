#include "Move.hpp"
#include "Map.hpp"
#include "Actor.hpp"

bool MoveCommand::execute(Actor* actor, int xDest, int yDest) {
	actor->setX(xDest);
	actor->setY(yDest);
	return true;
}
