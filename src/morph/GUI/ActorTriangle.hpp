#ifndef __GUI_ACTOR_TRIANGLE__
#define __GUI_ACTOR_TRIANGLE__

#include "Actor.hpp"

class GraphicActorTriangle : public GraphicActor {
	private:
	std::vector<std::pair<Sint16, Sint16>> _getCorners(Actor *actor);

	public:
	void render(
		int displayShiftX,
		int displayShiftY,
		Actor *actor
	);
	std::vector<std::pair<int, SDL_Rect>> getAttacks(Actor* actor, bool full = false);
	int canTouch(Actor* actor1, Actor* actor2);
	int getAttackDuration();
};

#endif
