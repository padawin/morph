#ifndef __BEHAVIOUR_ENEMY_SQUARE__
#define __BEHAVIOUR_ENEMY_SQUARE__

#include "Behaviour/Behaviour.hpp"
#include "Engine.hpp"
#include "Actor.hpp"

class BehaviourEnemySquare : public Behaviour {
	public:
	bool update(Engine* engine, Actor* actor);
};

#endif
