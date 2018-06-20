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
}
