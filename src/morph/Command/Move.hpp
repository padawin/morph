#ifndef __MOVE_COMMAND__
#define __MOVE_COMMAND__

#include "Command/Command.hpp"
#include "Map.hpp"

class MoveCommand : public Command {
	public:
	bool execute(Actor* actor, Vector2D direction, Map& m);
};

#endif
