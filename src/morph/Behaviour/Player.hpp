#ifndef __BEHAVIOUR_PLAYER__
#define __BEHAVIOUR_PLAYER__

#include "Behaviour/Behaviour.hpp"
#include "Engine.hpp"
#include "Actor.hpp"

class Map;

class BehaviourPlayer : public Behaviour {
	private:
	void _updatePlayerPosition(Actor* actor);

	public:
	bool update(Engine* engine, Actor* actor);
};

#endif
