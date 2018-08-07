#include "ActorStar.hpp"
#include "../Actor.hpp"
#include "types.hpp"
#include "SDL2_framework/Game.h"
#include "Physics.hpp"
#include "SDL2/SDL2_gfxPrimitives.h"

const int ACTOR_RIM_THICKNESS = 2;
const int ACTOR_RIM_HALF_THICKNESS = ACTOR_RIM_THICKNESS / 2;

double GraphicActorStar::_getRenderRatio() {
	return 1.7;
}

int GraphicActorStar::getAttackDuration() {
	return 200;
}

unsigned int GraphicActorStar::_getCountCorners() {
	return 5;
}

double GraphicActorStar::_getAngleCorners() {
	return 2 * 2.0 * M_PI / 5;
}

void GraphicActorStar::_renderAttacks(int displayShiftX, int displayShiftY, Actor *actor) {
	for (auto const& it : getAttacks(actor)) {
		_renderPolygon(
			displayShiftX, displayShiftY, actor,
			_getCorners(
				actor, it.first, it.second.w / 2,
				it.second.w * M_PI / 50
			),
			false
		);
	}
}

std::vector<std::pair<E_ActorAttack, SDL_Rect>> GraphicActorStar::getAttacks(Actor* actor, bool full) {
	const int maxLengthAttack = 50;
	std::vector<std::pair<E_ActorAttack, SDL_Rect>> attackAreas;
	for (int side = 0; side < 4; ++side) {
		int attack = actor->getAttackProgress((E_ActorAttack) side);
		if (!full && !attack) {
			continue;
		}

		// Make the attack a percentage
		if (full) {
			attack = maxLengthAttack;
		}
		else {
			attack = maxLengthAttack - attack * maxLengthAttack / getAttackDuration();
		}
		SDL_Rect r = {
			(int) (actor->getX() - attack),
			(int) (actor->getY() - attack),
			attack * 2,
			attack * 2
		};
		attackAreas.push_back({(E_ActorAttack) side, r});
	}
	return attackAreas;
}

E_ActorAttack GraphicActorStar::canTouch(Actor* actor1, Actor* actor2) {
	std::vector<std::pair<E_ActorAttack, SDL_Rect>> attacks = getAttacks(actor1, true);
	double distActorsX = actor2->getX() - actor1->getX();
	double distActorsY = actor2->getY() - actor1->getY();
	double distActors = distActorsX * distActorsX + distActorsY * distActorsY;
	for (auto attack : attacks) {
		if (attack.second.w * attack.second.w > distActors) {
			return attack.first;
		}
	}

	return NO_ATTACK;
}
