#include "ActorSquare.hpp"
#include "../Actor.hpp"
#include "SDL2_framework/Game.h"
#include "Physics.hpp"
#include "SDL2/SDL2_gfxPrimitives.h"

const int ACTOR_RIM_THICKNESS = 2;
const int ACTOR_RIM_HALF_THICKNESS = ACTOR_RIM_THICKNESS / 2;

int GraphicActorSquare::getAttackDuration() {
	return 100;
}

void GraphicActorSquare::render(int displayShiftX, int displayShiftY, Actor *actor) {
	Game* game = Game::Instance();
	int actorWidth = actor->getWidth();
	int actorHeight = actor->getHeight();
	Sint16 x1 = (Sint16) (actor->getX() - actorWidth / 2 + displayShiftX);
	Sint16 y1 = (Sint16) (actor->getY() - actorHeight / 2 + displayShiftY);
	Sint16 x2 = (Sint16) (x1 + actorWidth);
	Sint16 y2 = (Sint16) (y1 + actorHeight);
	std::pair<Sint16, Sint16> sides[] = {
		// 4 corners, the rim adjustments are to align the attacks
		{x1 + ACTOR_RIM_HALF_THICKNESS, y1 + ACTOR_RIM_HALF_THICKNESS},
		{x2, y1 + ACTOR_RIM_HALF_THICKNESS},
		{x2, y2},
		{x1 + ACTOR_RIM_HALF_THICKNESS, y2},
		{x1 + ACTOR_RIM_HALF_THICKNESS, y1 + ACTOR_RIM_HALF_THICKNESS}
	};
	for (int i = 0; i < 4; ++i) {
		thickLineRGBA(
			game->getRenderer(),
			sides[i].first, sides[i].second, sides[i + 1].first, sides[i + 1].second,
			ACTOR_RIM_THICKNESS,
			actor->getRed(), actor->getGreen(), actor->getBlue(), 255
		);
	}
	if (!actor->isHollow()) {
		boxRGBA(game->getRenderer(),
			x1, y1, x2, y2,
			actor->getRed(), actor->getGreen(), actor->getBlue(), 255
		);
	}

	_renderAttacks(displayShiftX, displayShiftY, actor);
}

void GraphicActorSquare::_renderAttacks(int displayShiftX, int displayShiftY, Actor *actor) {
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

std::vector<std::pair<int, SDL_Rect>> GraphicActorSquare::getAttacks(Actor* actor, bool full) {
	const int attacks[4] = {
		ATTACK_UP, ATTACK_RIGHT, ATTACK_DOWN, ATTACK_LEFT
	};
	std::vector<std::pair<int, SDL_Rect>> attackAreas;
	const int maxLengthAttack = 20,
			  // Center of the actor on the screen coords
			  actorWidth = actor->getWidth(),
			  actorHeight = actor->getHeight();
	double baseX = actor->getX(),
		   baseY = actor->getY();
	int attackLength;
	for (int side = 0; side < 4; ++side) {
		int attack = actor->getAttackProgress(attacks[side]);
		if (!attack && !full) {
			continue;
		}
		if (full) {
			attackLength = maxLengthAttack;
		}
		else {
			attackLength = maxLengthAttack - (attack * maxLengthAttack) / getAttackDuration();
		}
		SDL_Rect r;

		if (attacks[side] == ATTACK_UP || attacks[side] == ATTACK_DOWN) {
			if (attacks[side] == ATTACK_UP) {
				r.x = (int) (baseX - actorWidth / 2);
				r.y = (int) (baseY - actorHeight / 2 - attackLength);
			}
			else {
				r.x = (int) (baseX - actorWidth / 2);
				r.y = (int) (baseY + actorHeight / 2);
			}
			r.w = actorWidth;
			r.h = attackLength;
		}
		else {
			if (attacks[side] == ATTACK_LEFT) {
				r.x = (int) (baseX - actorWidth / 2 - attackLength);
				r.y = (int) (baseY - actorHeight / 2);
			}
			else {
				r.x = (int) (baseX + actorWidth / 2);
				r.y = (int) (baseY - actorHeight / 2);
			}
			r.w = attackLength;
			r.h = actorHeight;
		}
		attackAreas.push_back({attacks[side], r});
	}

	return attackAreas;
}

void GraphicActorSquare::_renderAttack(
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

int GraphicActorSquare::canTouch(Actor* actor1, Actor* actor2) {
	for (auto const& it : getAttacks(actor1, true)) {
		if (physics::areRectIntersecting(it.second, actor2->getHitbox())) {
			return it.first;
		}
	}
	return -1;
}
