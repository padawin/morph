#include <iostream>
#include <math.h>
#include "ActorTriangle.hpp"
#include "../Actor.hpp"
#include "types.hpp"
#include "SDL2_framework/Game.h"
#include "Physics.hpp"
#include "SDL2/SDL2_gfxPrimitives.h"

const int ACTOR_RIM_THICKNESS = 2;
const int ACTOR_RIM_HALF_THICKNESS = ACTOR_RIM_THICKNESS / 2;

int GraphicActorTriangle::getAttackDuration() {
	return 200;
}

std::vector<std::pair<Sint16, Sint16>> GraphicActorTriangle::_getCorners(
	Actor *actor, E_ActorAttack orientation
) {
	int actorSize = actor->getSize();
	double c, s, xOrig, yOrig, x, y;
	double angle = 2.0 / 3 * M_PI;
	xOrig = 0;
	yOrig = -actorSize / 2;
	if (orientation == ATTACK_RIGHT) {
		xOrig = actorSize / 2;
		yOrig = 0;
	}
	else if (orientation == ATTACK_DOWN) {
		xOrig = 0;
		yOrig = actorSize / 2;
	}
	else if (orientation == ATTACK_LEFT) {
		xOrig = -actorSize / 2;
		yOrig = 0;
	}
	std::vector<std::pair<Sint16, Sint16>> corners;
	for (int i = 0; i < 3 ; ++i) {
		s = sin(angle * i);
		c = cos(angle * i);
		x = xOrig * c - yOrig * s;
		y = xOrig * s + yOrig * c;
		corners.push_back({
			(Sint16) (actor->getX() + x),
			(Sint16) (actor->getY() + y)
		});
	}
	return corners;
}

void GraphicActorTriangle::render(int displayShiftX, int displayShiftY, Actor *actor) {
	Game* game = Game::Instance();
	std::vector<std::pair<Sint16, Sint16>> corners = _getCorners(actor, m_lastAttack);

	Sint16 x1 = (Sint16) (displayShiftX + corners[0].first),
		   y1 = (Sint16) (displayShiftY + corners[0].second),
		   x2 = (Sint16) (displayShiftX + corners[1].first),
		   y2 = (Sint16) (displayShiftY + corners[1].second),
		   x3 = (Sint16) (displayShiftX + corners[2].first),
		   y3 = (Sint16) (displayShiftY + corners[2].second);
	if (actor->isHollow()) {
		std::pair<Sint16, Sint16> sides[] = {
			{x1, y1}, {x2, y2}, {x3, y3}, {x1, y1}
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
		const Sint16 xs[3] = {x1, x2, x3};
		const Sint16 ys[3] = {y1, y2, y3};
		filledPolygonRGBA(
			game->getRenderer(),
			xs, ys,
			3, actor->getRed(), actor->getGreen(), actor->getBlue(), 255
		);
	}

	_renderAttacks(displayShiftX, displayShiftY, actor);
}

void GraphicActorTriangle::_renderAttacks(int displayShiftX, int displayShiftY, Actor *actor) {
	const unsigned char red = actor->getRed(),
		green = actor->getGreen(),
		blue = actor->getBlue();
	for (auto const& it : getAttacks(actor)) {
		SDL_Rect attack = it.second;
		attack.x += displayShiftX;
		attack.y += displayShiftY;
		_renderAttack(attack, red, green, blue);
	}
}

std::vector<std::pair<E_ActorAttack, SDL_Rect>> GraphicActorTriangle::getAttacks(Actor* actor, bool full) {
	const E_ActorAttack attacks[4] = {
		ATTACK_UP, ATTACK_RIGHT, ATTACK_DOWN, ATTACK_LEFT
	};
	std::vector<std::pair<E_ActorAttack, SDL_Rect>> attackAreas;
	const int attackWidth = 2;
	const int attackDuration = getAttackDuration();
	const int maxLengthAttack = 70;
	int attackLength = maxLengthAttack;
	// percentage of the attack the ray is acting
	const int rayDuration = 50;
	for (int side = 0; side < 4; ++side) {
		bool isHorizontal = side == ATTACK_LEFT || side == ATTACK_RIGHT;
		int attack = actor->getAttackProgress(attacks[side]);
		if (!full && !attack) {
			continue;
		}

		// Make the attack a percentage
		if (full) {
			attack = 100;
		}
		else {
			attack = 100 - attack * 100 / attackDuration;
		}
		int r = 0;
		for (auto corner : _getCorners(actor, attacks[side])) {
			const int minBracket = 25 * r,
				  maxBracket = rayDuration + 25 * r;
			if (full || (minBracket < attack && attack < maxBracket)) {
				SDL_Rect ray;
				if (full) {
					attackLength = maxLengthAttack;
				}
				else {
					attackLength = (attack - minBracket) * maxLengthAttack / rayDuration;
				}
				if (isHorizontal) {
					if (side == ATTACK_LEFT) {
						ray.x = (int) corner.first - 2 - attackLength;
					}
					else {
						ray.x = (int) corner.first + 2;
					}
					ray.y = (int) corner.second - 1;
					ray.w = attackLength;
					ray.h = attackWidth;
				}
				else {
					if (side == ATTACK_UP) {
						ray.y = (int) corner.second - 2 - attackLength;
					}
					else {
						ray.y = (int) corner.second + 2;
					}
					ray.x = (int) corner.first - 1;
					ray.w = attackWidth;
					ray.h = attackLength;
				}
				attackAreas.push_back({attacks[side], ray});
			}
			++r;
		}
	}
	return attackAreas;
}

void GraphicActorTriangle::_renderAttack(
	const SDL_Rect r,
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue
) {
	Game* game = Game::Instance();
	Sint16 x1 = (Sint16) r.x,
		   y1 = (Sint16) r.y,
		   x2 = (Sint16) (r.x + r.w),
		   y2 = (Sint16) (r.y + r.h);
	boxRGBA(game->getRenderer(),
		x1, y1, x2, y2, red, green, blue, 255
	);
}

E_ActorAttack GraphicActorTriangle::canTouch(Actor* actor1, Actor* actor2) {
	for (auto const& it : getAttacks(actor1, true)) {
		if (physics::areRectIntersecting(it.second, actor2->getHitbox())) {
			return it.first;
		}
	}
	return NO_ATTACK;
}
