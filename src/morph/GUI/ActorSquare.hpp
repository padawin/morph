#ifndef __GUI_ACTOR_SQUARE__
#define __GUI_ACTOR_SQUARE__

#include "Actor.hpp"

class GraphicActorSquare : public GraphicActor {
	private:
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
	std::map<int, SDL_Rect> getAttacks(Actor* actor);
};

#endif
