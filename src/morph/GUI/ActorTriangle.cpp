#include <iostream>
#include <math.h>
#include "ActorTriangle.hpp"
#include "../Actor.hpp"
#include "types.hpp"
#include "SDL2_framework/Game.h"
#include "Physics.hpp"
#include "SDL2/SDL2_gfxPrimitives.h"

int GraphicActorTriangle::getAttackDuration() {
	return 200;
}

unsigned int GraphicActorTriangle::_getCountCorners() {
	return 3;
}

double GraphicActorTriangle::_getAngleCorners() {
	return 2.0 / 3 * M_PI;
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
	std::vector<std::pair<E_ActorAttack, SDL_Rect>> attackAreas;
	const int attackWidth = 2;
	const int attackDuration = getAttackDuration();
	const int maxLengthAttack = 70;
	int attackLength = maxLengthAttack;
	// percentage of the attack the ray is acting
	const int rayDuration = 50;
	for (int side = 0; side < 4; ++side) {
		E_ActorAttack a = (E_ActorAttack) side;
		bool isHorizontal = a == ATTACK_LEFT || a == ATTACK_RIGHT;
		int attack = actor->getAttackProgress(a);
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
		std::pair<std::vector<Sint16>, std::vector<Sint16>> corners = _getCorners(
			actor, a, 0
		);
		for (long unsigned c = 0; c < _getCountCorners(); ++c) {
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
					if (a == ATTACK_LEFT) {
						ray.x = (int) corners.first[c] - 2 - attackLength;
					}
					else {
						ray.x = (int) corners.first[c] + 2;
					}
					ray.y = (int) corners.second[c] - 1;
					ray.w = attackLength;
					ray.h = attackWidth;
				}
				else {
					if (a == ATTACK_UP) {
						ray.y = (int) corners.second[c] - 2 - attackLength;
					}
					else {
						ray.y = (int) corners.second[c] + 2;
					}
					ray.x = (int) corners.first[c] - 1;
					ray.w = attackWidth;
					ray.h = attackLength;
				}
				attackAreas.push_back({a, ray});
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
