#include <iostream>
#include "HUD.hpp"
#include "Actor.hpp"
#include "SDL2_framework/Game.h"

void HUD::render(Game *game, std::shared_ptr<Actor> hero) {
	int healthWidth = 16;
	int staminaWidth = 16;
	int healthHeight = game->getScreenHeight() / 2;
	int staminaHeight = game->getScreenHeight() / 2;
	SDL_Rect r;
	r.x = game->getScreenWidth() - healthWidth;
	r.w = healthWidth;
	r.h = hero->getHealth() * healthHeight / hero->getMaxHealth();
	r.y = healthHeight - r.h;
	SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(game->getRenderer(), &r);
	r.h = healthHeight;
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);
	SDL_RenderDrawRect(game->getRenderer(), &r);

	r.x = game->getScreenWidth() - healthWidth;
	r.w = staminaWidth;
	r.h = (int) (hero->getStamina() * staminaHeight / hero->getMaxStamina());
	r.y = healthHeight + staminaHeight - r.h;
	SDL_SetRenderDrawColor(game->getRenderer(), 96, 133, 255, 255);
	SDL_RenderFillRect(game->getRenderer(), &r);
	r.h = staminaHeight;
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);
	SDL_RenderDrawRect(game->getRenderer(), &r);
}
