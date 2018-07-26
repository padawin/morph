#ifndef __GUI_ACTOR_POLYGON__
#define __GUI_ACTOR_POLYGON__

#include "Actor.hpp"

class GraphicActorPolygon : public GraphicActor {
	protected:
	virtual double _getRenderRatio();
	virtual unsigned int _getCountCorners() = 0;
	virtual double _getAngleCorners() = 0;
	std::pair<std::vector<Sint16>, std::vector<Sint16>> _getCorners(
		Actor *actor, E_ActorAttack orientation, double distanceFromCenter
	);
	virtual void _renderAttacks(int displayShiftX, int displayShiftY, Actor *actor) = 0;
	virtual void _renderPolygon(int displayShiftX, int displayShiftY, Actor* actor, std::pair<std::vector<Sint16>, std::vector<Sint16>> corners, bool hollow);

	public:
	void render(
		int displayShiftX,
		int displayShiftY,
		Actor *actor
	);
};

#endif
