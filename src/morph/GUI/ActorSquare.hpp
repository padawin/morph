#ifndef __GUI_ACTOR_SQUARE__
#define __GUI_ACTOR_SQUARE__

#include "Actor.hpp"

class GraphicActorSquare : public GraphicActor {
	public:
	void render(
		int displayShiftX,
		int displayShiftY,
		Actor *actor
	);
};

#endif
