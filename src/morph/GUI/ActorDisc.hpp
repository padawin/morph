#ifndef __GUI_ACTOR_DISC__
#define __GUI_ACTOR_DISC__

#include "Actor.hpp"

class GraphicActorDisc : public GraphicActor {
	private:
	void _renderAttacks(int displayShiftX, int displayShiftY, Actor *actor);

	public:
	void render(
		int displayShiftX,
		int displayShiftY,
		Actor *actor
	);
	std::vector<std::pair<E_ActorAttack, SDL_Rect>> getAttacks(Actor* actor, bool full = false);
	E_ActorAttack canTouch(Actor* actor1, Actor* actor2);
	int getAttackDuration();
};

#endif
