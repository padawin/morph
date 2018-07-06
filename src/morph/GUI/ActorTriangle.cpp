#include <iostream>
#include <math.h>
#include "ActorTriangle.hpp"
#include "../Actor.hpp"
#include "SDL2_framework/Game.h"
#include "Physics.hpp"
#include "SDL2/SDL2_gfxPrimitives.h"

const int ACTOR_RIM_THICKNESS = 2;
const int ACTOR_RIM_HALF_THICKNESS = ACTOR_RIM_THICKNESS / 2;

void GraphicActorTriangle::render(int displayShiftX, int displayShiftY, Actor *actor) {
	const Sint16 shiftX = (Sint16) (actor->getX() + displayShiftX),
		   shiftY = (Sint16) (actor->getY() + displayShiftY);
	Game* game = Game::Instance();
	int actorWidth = actor->getWidth();
	Sint16 x1 = 0;
	Sint16 y1 = (Sint16) -actorWidth / 2;
	double c, s, x2, y2, x3, y3;
	double angle = 2.0 / 3 * M_PI;
	// rotate second point
	s = sin(angle);
	c = cos(angle);
	x2 = x1 * c - y1 * s;
	y2 = x1 * s + y1 * c;
	s = sin(angle * 2);
	c = cos(angle * 2);
	x3 = x1 * c - y1 * s;
	y3 = x1 * s + y1 * c;

	if (actor->isHollow()) {
		std::pair<Sint16, Sint16> sides[] = {
			// 4 corners, the rim adjustments are to align the attacks
			{shiftX + x1, shiftY + y1},
			{shiftX + (Sint16) x2,  shiftY + (Sint16) y2},
			{shiftX + (Sint16) x3,  shiftY + (Sint16) y3},
			{shiftX + x1, shiftY + y1}
		};
		for (int i = 0; i < 3; ++i) {
			thickLineRGBA(
				game->getRenderer(),
				sides[i].first, sides[i].second, sides[i + 1].first, sides[i + 1].second,
				ACTOR_RIM_THICKNESS,
				actor->getRed(), actor->getGreen(), actor->getBlue(), 255
			);
		}
	}
	else {
		const Sint16 xs[3] = {(Sint16) (shiftX + x1), (Sint16) (shiftX + x2), (Sint16) (shiftX + x3)};
		const Sint16 ys[3] = {(Sint16) (shiftY + y1), (Sint16) (shiftY + y2), (Sint16) (shiftY + y3)};
		filledPolygonRGBA(
			game->getRenderer(),
			xs, ys, 3, actor->getRed(), actor->getGreen(), actor->getBlue(), 255
		);
	}
}

std::map<int, SDL_Rect> GraphicActorTriangle::getAttacks(Actor* actor __attribute__((unused)), bool full __attribute__((unused))) {
	std::map<int, SDL_Rect> attackAreas;
	return attackAreas;
}

int GraphicActorTriangle::canTouch(Actor* actor1 __attribute__((unused)), Actor* actor2 __attribute__((unused))) {
	return -1;
}
