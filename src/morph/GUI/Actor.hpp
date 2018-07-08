#ifndef __GRAPHIC_ACTOR__
#define __GRAPHIC_ACTOR__

#include "GUI.hpp"
#include "SDL2/SDL.h"
#include "types.hpp"
#include <vector>

class Actor;

class GraphicActor : public Graphic {
	protected:
	E_ActorAttack m_lastAttack = ATTACK_UP;

	public:
	virtual void render(
		int displayShiftX,
		int displayShiftY,
		Actor* actor
	) = 0;
	virtual std::vector<std::pair<E_ActorAttack, SDL_Rect>> getAttacks(Actor* actor, bool full = false) = 0;
	virtual E_ActorAttack canTouch(Actor* actor1, Actor* actor2) = 0;
	virtual int getAttackDuration() = 0;
	void setLastAttack(E_ActorAttack attack);
};

#endif
