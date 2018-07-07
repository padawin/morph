#ifndef __GUI_ACTOR_TRIANGLE__
#define __GUI_ACTOR_TRIANGLE__

#include "Actor.hpp"

class GraphicActorTriangle : public GraphicActor {
	private:
	std::vector<std::pair<Sint16, Sint16>> _getCorners(Actor *actor);
	void _renderAttacks(int displayShiftX, int displayShiftY, Actor *actor);
	void _renderAttack(
		const SDL_Rect r,
		const unsigned char red,
		const unsigned char green,
		const unsigned char blue
	);

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
