#ifndef __GUI_ACTOR_STAR__
#define __GUI_ACTOR_STAR__

#include "ActorPolygon.hpp"

class GraphicActorStar : public GraphicActorPolygon {
	private:
	double _getRenderRatio();
	unsigned int _getCountCorners();
	double _getAngleCorners();
	void _renderAttacks(int displayShiftX, int displayShiftY, Actor *actor);
	void _renderAttack(
		const SDL_Rect r,
		const unsigned char red,
		const unsigned char green,
		const unsigned char blue
	);

	public:
	std::vector<std::pair<E_ActorAttack, SDL_Rect>> getAttacks(Actor* actor, bool full = false);
	E_ActorAttack canTouch(Actor* actor1, Actor* actor2);
	int getAttackDuration();
};

#endif
