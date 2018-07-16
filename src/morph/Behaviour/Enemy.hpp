#ifndef __BEHAVIOUR_ENEMY__
#define __BEHAVIOUR_ENEMY__

#include "Behaviour/Behaviour.hpp"
#include "Engine.hpp"
#include "Actor.hpp"

class BehaviourEnemy : public Behaviour {
	public:
	bool update(Engine* engine, Actor* actor);
};

#endif
