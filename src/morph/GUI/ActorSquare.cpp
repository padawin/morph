#include "ActorSquare.hpp"
#include <iostream>
#include "../Actor.hpp"
#include "SDL2_framework/Game.h"

void GraphicActorSquare::render(int displayShiftX, int displayShiftY, Actor *actor) {
	Game* game = Game::Instance();
	SDL_Rect r;
	r.x = actor->getX() - TILE_WIDTH / 2 + displayShiftX;
	r.y = actor->getY() - TILE_HEIGHT / 2 + displayShiftY;
	r.w = TILE_WIDTH;
	r.h = TILE_HEIGHT;
	SDL_SetRenderDrawColor(
		game->getRenderer(),
		actor->getRed(), actor->getGreen(), actor->getBlue(), 0
	);
	SDL_RenderFillRect(game->getRenderer(), &r);

	_renderAttacks(displayShiftX, displayShiftY, actor);
}

void GraphicActorSquare::_renderAttacks(int displayShiftX, int displayShiftY, Actor *actor) {
	const int attackUp = actor->getAttackDuration(ATTACK_UP),
		attackRight = actor->getAttackDuration(ATTACK_RIGHT),
		attackDown = actor->getAttackDuration(ATTACK_DOWN),
		attackLeft = actor->getAttackDuration(ATTACK_LEFT),
		maxLengthAttack = 20,
		attackWidth = TILE_WIDTH,
		// Center of the actor on the screen coords
		baseX = actor->getX() + displayShiftX,
		baseY = actor->getY() + displayShiftY;
	const unsigned char red = actor->getRed(),
		green = actor->getGreen(),
		blue = actor->getBlue();
	int attackLength = attackUp * maxLengthAttack / DURATION_ATTACK;
	SDL_Rect r;
	if (attackUp) {
		attackLength = attackUp * maxLengthAttack / DURATION_ATTACK,
		r.x = baseX - TILE_WIDTH / 2;
		r.y = baseY - TILE_HEIGHT / 2 - attackLength;
		r.w = attackWidth;
		r.h = attackLength;
		_renderAttack(r, red, green, blue);
	}
	if (attackRight) {
		attackLength = attackRight * maxLengthAttack / DURATION_ATTACK,
		r.x = baseX + TILE_WIDTH / 2;
		r.y = baseY - TILE_HEIGHT / 2;
		r.w = attackLength;
		r.h = attackWidth;
		_renderAttack(r, red, green, blue);
	}
	if (attackDown) {
		attackLength = attackDown * maxLengthAttack / DURATION_ATTACK,
		r.x = baseX - TILE_WIDTH / 2;
		r.y = baseY + TILE_HEIGHT / 2;
		r.w = attackWidth;
		r.h = attackLength;
		_renderAttack(r, red, green, blue);
	}
	if (attackLeft) {
		attackLength = attackLeft * maxLengthAttack / DURATION_ATTACK,
		r.x = baseX - TILE_WIDTH / 2 - attackLength;
		r.y = baseY - TILE_HEIGHT / 2;
		r.w = attackLength;
		r.h = attackWidth;
		_renderAttack(r, red, green, blue);
	}
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
