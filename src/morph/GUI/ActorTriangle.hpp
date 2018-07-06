#ifndef __GUI_ACTOR_TRIANGLE__
#define __GUI_ACTOR_TRIANGLE__

#include "Actor.hpp"

class GraphicActorTriangle : public GraphicActor {
	public:
	void render(
		int displayShiftX,
		int displayShiftY,
		Actor *actor
	);
	std::map<int, SDL_Rect> getAttacks(Actor* actor, bool full = false);
	int canTouch(Actor* actor1, Actor* actor2);
};

#endif
