#include <math.h>
#include "ActorDisc.hpp"
#include "../Actor.hpp"
#include "types.hpp"
#include "SDL2_framework/Game.h"
#include "Physics.hpp"
#include "SDL2/SDL2_gfxPrimitives.h"

const int ACTOR_RIM_THICKNESS = 2;
const int ACTOR_RIM_HALF_THICKNESS = ACTOR_RIM_THICKNESS / 2;

const int ATTACK_RADIUS = 40;

int GraphicActorDisc::getAttackDuration() {
	return 400;
}

void GraphicActorDisc::render(int displayShiftX, int displayShiftY, Actor *actor) {
	Game* game = Game::Instance();
	if (actor->isHollow()) {
		circleRGBA(
			game->getRenderer(),
			(Sint16) actor->getX(),
			(Sint16) actor->getY(),
			(Sint16) actor->getSize() / 2,
			actor->getRed(), actor->getGreen(), actor->getBlue(), 255
		);
	}
	else {
		filledCircleRGBA(
			game->getRenderer(),
			(Sint16) actor->getX(),
			(Sint16) actor->getY(),
			(Sint16) actor->getSize() / 2,
			actor->getRed(), actor->getGreen(), actor->getBlue(), 255
		);
	}

	_renderAttacks(displayShiftX, displayShiftY, actor);
}

void GraphicActorDisc::_renderAttacks(int displayShiftX, int displayShiftY, Actor *actor) {
	Game* game = Game::Instance();
	const unsigned char red = actor->getRed(),
		green = actor->getGreen(),
		blue = actor->getBlue();
	for (auto const& it : getAttacks(actor)) {
		SDL_Rect attack = it.second;
		attack.x += displayShiftX;
		attack.y += displayShiftY;
		filledCircleRGBA(
			game->getRenderer(),
			(Sint16) (attack.x + actor->getSize() / 2),
			(Sint16) (attack.y + actor->getSize() / 2),
			(Sint16) (attack.w / 2),
			red, green, blue, 255
		);
	}
}

std::vector<std::pair<E_ActorAttack, SDL_Rect>> GraphicActorDisc::getAttacks(Actor* actor, bool full) {
	const E_ActorAttack attacks[4] = {
		ATTACK_UP, ATTACK_RIGHT, ATTACK_DOWN, ATTACK_LEFT
	};
	double c, s, angleProgress;
	double xAttack,
		  yAttack;
	double initial[][3] = {
		{1 * M_PI / 2, 0, -1},
		{2 * M_PI / 2, 1, 0},
		{3 * M_PI / 2, 0, 1},
		{4 * M_PI / 2, -1, 0}
	};
	std::vector<std::pair<E_ActorAttack, SDL_Rect>> attackAreas;
	for (int side = 0; side < 4; ++side) {
		int attack = actor->getAttackProgress(attacks[side]);
		if (!full && !attack) {
			continue;
		}

		SDL_Rect r;
		// Make the attack a percentage
		if (full) {
			r.x = (int) (actor->getX() + ATTACK_RADIUS * initial[side][1] - ATTACK_RADIUS);
			r.y = (int) (actor->getY() + ATTACK_RADIUS * initial[side][2] - ATTACK_RADIUS);
			r.w = ATTACK_RADIUS * 2;
			r.h = ATTACK_RADIUS * 2;
		}
		else {
			attack = 100 - attack * 100 / getAttackDuration();

			// place the attackCenter depending on the side and the ATTACK_RADIUS
			angleProgress = initial[side][0] + attack * 2 * M_PI / 100;
			c = cos(angleProgress);
			s = sin(angleProgress);
			// the reference position of the attack is {ATTACK_RADIUS, 0}
			// so the whole value of x is ATTACK_RADIUS * c - 0 * s
			xAttack = ATTACK_RADIUS * c;
			// same for y, the whole value is ATTACK_RADIUS * s + 0 * c
			yAttack = ATTACK_RADIUS * s;
			// shift the coordinate to be above the actor
			xAttack += actor->getX() + ATTACK_RADIUS * initial[side][1];
			yAttack += actor->getY() + ATTACK_RADIUS * initial[side][2];
			r.x = (int) (xAttack - actor->getSize() / 2);
			r.y = (int) (yAttack - actor->getSize() / 2);
			r.w = actor->getSize();
			r.h = actor->getSize();
		}
		attackAreas.push_back({attacks[side], r});
	}
	return attackAreas;
}

E_ActorAttack GraphicActorDisc::canTouch(Actor* actor1, Actor* actor2) {
	SDL_Rect hitbox = actor2->getHitbox();
	int corners[][2] = {
		{hitbox.x, hitbox.y},
		{hitbox.x + hitbox.w, hitbox.y},
		{hitbox.x, hitbox.y + hitbox.h},
		{hitbox.x + hitbox.w, hitbox.y + hitbox.h},
	};
	long minDistance = ATTACK_RADIUS - actor1->getSize() / 2;
	long maxDistance = ATTACK_RADIUS + actor1->getSize() / 2;
	// square them to avoid to do a sqrt later
	minDistance *= minDistance;
	maxDistance *= maxDistance;
	for (auto const& it : getAttacks(actor1, true)) {
		// test if any of the corner of actor2->hitBox are within actor1's
		// attack area. The attack is a disc going in a circle. So the area is a
		// disc of ATTACK_RADIUS + actorSize / 2 - the area of a disc of
		// ATTACK_RADIUS - actorSize / 2
		double centerAttack[2] = {
			(double) (it.second.x + it.second.w / 2),
			(double) (it.second.y + it.second.h / 2)
		};
		for (auto corner : corners) {
			long distanceX = (int) (centerAttack[0] - corner[0]);
			long distanceY = (int) (centerAttack[1] - corner[1]);
			long dist;
			dist = distanceX * distanceX + distanceY * distanceY;
			// The corner of the hitbox is touching;
			if (minDistance <= dist && dist <= maxDistance) {
				return it.first;
			}
		}
	}
	return NO_ATTACK;
}
