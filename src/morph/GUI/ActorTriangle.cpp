#include <iostream>
#include <math.h>
#include "ActorTriangle.hpp"
#include "../Actor.hpp"
#include "SDL2_framework/Game.h"
#include "Physics.hpp"
#include "SDL2/SDL2_gfxPrimitives.h"

const int ACTOR_RIM_THICKNESS = 2;
const int ACTOR_RIM_HALF_THICKNESS = ACTOR_RIM_THICKNESS / 2;

int GraphicActorTriangle::getAttackDuration() {
	return 200;
}

std::vector<std::pair<Sint16, Sint16>> GraphicActorTriangle::_getCorners(Actor *actor) {
	int actorWidth = actor->getWidth();
	double c, s, xOrig, yOrig, x, y;
	double angle = 2.0 / 3 * M_PI;
	// to change depending on the orientation
	xOrig = 0;
	yOrig = -actorWidth / 2;
	std::vector<std::pair<Sint16, Sint16>> corners;
	for (int i = 0; i < 3 ; ++i) {
		s = sin(angle * i);
		c = cos(angle * i);
		x = xOrig * c - yOrig * s;
		y = xOrig * s + yOrig * c;
		corners.push_back({(Sint16) x, (Sint16) y});
	}
	return corners;
}

void GraphicActorTriangle::render(int displayShiftX, int displayShiftY, Actor *actor) {
	const Sint16 shiftX = (Sint16) (actor->getX() + displayShiftX),
		   shiftY = (Sint16) (actor->getY() + displayShiftY);
	Game* game = Game::Instance();
	std::vector<std::pair<Sint16, Sint16>> corners = _getCorners(actor);

	Sint16 x1 = corners[0].first, y1 = corners[0].second,
		   x2 = corners[1].first, y2 = corners[1].second,
		   x3 = corners[2].first, y3 = corners[2].second;
	if (actor->isHollow()) {
		std::pair<Sint16, Sint16> sides[] = {
			// 4 corners, the rim adjustments are to align the attacks
			{shiftX + x1, shiftY + y1},
			{shiftX + x2, shiftY + y2},
			{shiftX + x3, shiftY + y3},
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

std::vector<std::pair<int, SDL_Rect>> GraphicActorTriangle::getAttacks(Actor* actor __attribute__((unused)), bool full __attribute__((unused))) {
	std::vector<std::pair<int, SDL_Rect>> attackAreas;
	return attackAreas;
}

int GraphicActorTriangle::canTouch(Actor* actor1 __attribute__((unused)), Actor* actor2 __attribute__((unused))) {
	return -1;
}
