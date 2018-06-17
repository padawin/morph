#include "Actor.hpp"
#include <iostream>
#include "../Actor.hpp"
#include "ActorType.hpp"
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"

const int TIME_DISPLAY_HP = 5000;

GraphicActor::GraphicActor() {
	m_game = Game::Instance();
}

GraphicActor::GraphicActor(const GraphicActor &r) :
	m_game(r.m_game)
{
}

GraphicActor & GraphicActor::operator=(const GraphicActor &r) {
	// check for "self assignment" and do nothing in that case
	if (this == &r) {
		return *this;
	}

	m_game = r.m_game;
	return *this;
}

GraphicActor::~GraphicActor() {}

void GraphicActor::render(int displayShiftX, int displayShiftY, Actor *actor) {
	_renderActor(displayShiftX, displayShiftY, actor);

	if (actor->getLastTimeHit() && SDL_GetTicks() - actor->getLastTimeHit() < TIME_DISPLAY_HP) {
		_renderHP(displayShiftX, displayShiftY, actor);
	}
}

void GraphicActor::_renderActor(int displayShiftX, int displayShiftY, Actor *actor) {
	SDL_Rect r;
	r.x = actor->getX() - TILE_WIDTH / 2 + displayShiftX;
	r.y = actor->getY() - TILE_HEIGHT / 2 + displayShiftY;
	r.w = TILE_WIDTH;
	r.h = TILE_HEIGHT;
	SDL_SetRenderDrawColor(
		m_game->getRenderer(),
		actor->getRed(), actor->getGreen(), actor->getBlue(), 0
	);
	SDL_RenderFillRect(m_game->getRenderer(), &r);
}

void GraphicActor::_renderHP(int displayShiftX, int displayShiftY, Actor *actor) {
	int xScreen = actor->getX() * TILE_WIDTH + displayShiftX;
	int yScreen = actor->getY() * TILE_HEIGHT + displayShiftY;
	int health = 0;
	if (actor->getHealth() > 0) {
		health = actor->getHealth();
	}
	SDL_Rect r;
	r.x = xScreen;
	r.y = yScreen;
	r.w = (TILE_WIDTH * health / actor->getMaxHealth());
	r.h = 2;
	SDL_SetRenderDrawColor(m_game->getRenderer(), 0xff, 0, 0, 255);
	SDL_RenderFillRect(m_game->getRenderer(), &r);
}
