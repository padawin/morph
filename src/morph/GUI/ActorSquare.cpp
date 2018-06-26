#include "ActorSquare.hpp"
#include <iostream>
#include "../Actor.hpp"
#include "SDL2_framework/Game.h"

void GraphicActorSquare::render(int displayShiftX, int displayShiftY, Actor *actor) {
	Game* game = Game::Instance();
	SDL_Rect r;
	int actorWidth = actor->getWidth();
	int actorHeight = actor->getHeight();
	r.x = actor->getX() - actorWidth / 2 + displayShiftX;
	r.y = actor->getY() - actorHeight / 2 + displayShiftY;
	r.w = actorWidth;
	r.h = actorHeight;
	SDL_SetRenderDrawColor(
		game->getRenderer(),
		actor->getRed(), actor->getGreen(), actor->getBlue(), 0
	);
	SDL_RenderFillRect(game->getRenderer(), &r);

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

std::map<int, SDL_Rect> GraphicActorSquare::getAttacks(Actor* actor, bool full) {
	const int attackUp = actor->getAttackProgress(ATTACK_UP),
		attackRight = actor->getAttackProgress(ATTACK_RIGHT),
		attackDown = actor->getAttackProgress(ATTACK_DOWN),
		attackLeft = actor->getAttackProgress(ATTACK_LEFT),
		maxLengthAttack = 20,
		// Center of the actor on the screen coords
		baseX = actor->getX(),
		baseY = actor->getY(),
		actorWidth = actor->getWidth(),
		actorHeight = actor->getHeight();
	int attackLength = maxLengthAttack;
	std::map<int, SDL_Rect> attacks;
	if (full || attackUp) {
		if (!full) {
			attackLength = maxLengthAttack - (attackUp * maxLengthAttack) / 100;
		}
		SDL_Rect r;
		r.x = baseX - actorWidth / 2;
		r.y = baseY - actorHeight / 2 - attackLength;
		r.w = actorWidth;
		r.h = attackLength;
		attacks[ATTACK_UP] = r;
	}
	if (full || attackRight) {
		if (!full) {
			attackLength = maxLengthAttack - (attackRight * maxLengthAttack) / 100;
		}
		SDL_Rect r;
		r.x = baseX + actorWidth / 2;
		r.y = baseY - actorHeight / 2;
		r.w = attackLength;
		r.h = actorHeight;
		attacks[ATTACK_RIGHT] = r;
	}
	if (full || attackDown) {
		if (!full) {
			attackLength = maxLengthAttack - (attackDown * maxLengthAttack) / 100;
		}
		SDL_Rect r;
		r.x = baseX - actorWidth / 2;
		r.y = baseY + actorHeight / 2;
		r.w = actorWidth;
		r.h = attackLength;
		attacks[ATTACK_DOWN] = r;
	}
	if (full || attackLeft) {
		if (!full) {
			attackLength = maxLengthAttack - (attackLeft * maxLengthAttack) / 100;
		}
		SDL_Rect r;
		r.x = baseX - actorWidth / 2 - attackLength;
		r.y = baseY - actorHeight / 2;
		r.w = attackLength;
		r.h = actorHeight;
		attacks[ATTACK_LEFT] = r;
	}

	return attacks;
}

void GraphicActorSquare::_renderAttack(
	const SDL_Rect r,
	const unsigned char red,
	const unsigned char green,
	const unsigned char blue
) {
	Game* game = Game::Instance();
	SDL_SetRenderDrawColor(game->getRenderer(), red, green, blue, 0);
	SDL_RenderFillRect(game->getRenderer(), &r);
}
