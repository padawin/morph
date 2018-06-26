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
	for (auto attack : getAttacks(actor)) {
		attack.x += displayShiftX;
		attack.y += displayShiftY;
		_renderAttack(attack, red, green, blue);
	}
}

std::vector<SDL_Rect> GraphicActorSquare::getAttacks(Actor* actor) {
	const int attackUp = actor->getAttackProgress(ATTACK_UP),
		attackRight = actor->getAttackProgress(ATTACK_RIGHT),
		attackDown = actor->getAttackProgress(ATTACK_DOWN),
		attackLeft = actor->getAttackProgress(ATTACK_LEFT),
		maxLengthAttack = 20,
		// Center of the actor on the screen coords
		baseX = actor->getX(),
		baseY = actor->getY(),
		actorWidth = actor->getWidth(),
		actorHeight = actor->getHeight(),
		attackWidth = actorWidth;
	int attackLength;
	std::vector<SDL_Rect> attacks;
	if (attackUp) {
		attackLength = maxLengthAttack - (attackUp * maxLengthAttack) / 100;
		SDL_Rect r;
		r.x = baseX - actorWidth / 2;
		r.y = baseY - actorHeight / 2 - attackLength;
		r.w = attackWidth;
		r.h = attackLength;
		attacks.push_back(r);
	}
	if (attackRight) {
		attackLength = maxLengthAttack - (attackRight * maxLengthAttack) / 100;
		SDL_Rect r;
		r.x = baseX + actorWidth / 2;
		r.y = baseY - actorHeight / 2;
		r.w = attackLength;
		r.h = attackWidth;
		attacks.push_back(r);
	}
	if (attackDown) {
		attackLength = maxLengthAttack - (attackDown * maxLengthAttack) / 100;
		SDL_Rect r;
		r.x = baseX - actorWidth / 2;
		r.y = baseY + actorHeight / 2;
		r.w = attackWidth;
		r.h = attackLength;
		attacks.push_back(r);
	}
	if (attackLeft) {
		attackLength = maxLengthAttack - (attackLeft * maxLengthAttack) / 100;
		SDL_Rect r;
		r.x = baseX - actorWidth / 2 - attackLength;
		r.y = baseY - actorHeight / 2;
		r.w = attackLength;
		r.h = attackWidth;
		attacks.push_back(r);
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
