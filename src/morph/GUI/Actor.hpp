#ifndef __GRAPHIC_ACTOR__
#define __GRAPHIC_ACTOR__

#include "GUI.hpp"
#include "SDL2/SDL.h"
#include <vector>

class Actor;

class GraphicActor : public Graphic {
	public:
	virtual void render(
		int displayShiftX,
		int displayShiftY,
		Actor* actor
	) = 0;
	virtual std::vector<std::pair<int, SDL_Rect>> getAttacks(Actor* actor, bool full = false) = 0;
	virtual int canTouch(Actor* actor1, Actor* actor2) = 0;
	virtual int getAttackDuration() = 0;
};

#endif
