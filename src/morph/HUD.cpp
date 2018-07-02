#include "HUD.hpp"
#include "Actor.hpp"
#include "SDL2_framework/Game.h"

void HUD::render(Game *game, std::shared_ptr<Actor> hero) {
	int healthWidth = 16;
	SDL_Rect r;
	r.x = game->getScreenWidth() - healthWidth;
	r.w = healthWidth;
	r.h = hero->getHealth() * game->getScreenHeight() / hero->getMaxHealth();
	r.y = game->getScreenHeight() - r.h;
	SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(game->getRenderer(), &r);
	r.h = game->getScreenHeight();
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);
	SDL_RenderDrawRect(game->getRenderer(), &r);
}
