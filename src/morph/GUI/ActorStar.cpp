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
		_renderPolygon(displayShiftX, displayShiftY, actor, _getCorners(actor, it.first, 20), true);
	}
}

std::vector<std::pair<E_ActorAttack, SDL_Rect>> GraphicActorStar::getAttacks(Actor* actor __attribute__((unused)), bool full __attribute__((unused))) {
	std::vector<std::pair<E_ActorAttack, SDL_Rect>> attackAreas;
	return attackAreas;
}

E_ActorAttack GraphicActorStar::canTouch(Actor* actor1 __attribute__((unused)), Actor* actor2 __attribute__((unused))) {
	return NO_ATTACK;
}
