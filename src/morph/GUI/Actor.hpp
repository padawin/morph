#ifndef __GRAPHIC_ACTOR__
#define __GRAPHIC_ACTOR__

#include "GUI.hpp"

class Actor;

class GraphicActor : public Graphic {
	public:
	virtual void render(
		int displayShiftX,
		int displayShiftY,
		Actor *actor
	) = 0;
};

#endif
