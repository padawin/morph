#include <iostream>
#include "Actor.hpp"
#include "Engine.hpp"
#include "Behaviour/Behaviour.hpp"
#include "GUI/Actor.hpp"
#include <limits.h>
#include <SDL2/SDL.h>

#define LIMIT_FIELD_OF_VIEW 6

Actor::Actor(ActorType &type) :
	m_type(type),
	m_behaviour(0),
	m_graphic(0)
{
}

void Actor::setHealth(int health) { m_iHealth = health; }
int Actor::getHealth() { return m_iHealth; }
int Actor::getMaxHealth() { return m_type.getData().health; }
int Actor::getAttack() { return m_type.getData().attack; }

bool Actor::isDead() {
	return m_iHealth == 0;
}

void Actor::setX(int x) { m_iX = x; }
void Actor::setY(int y) { m_iY = y; }
int Actor::getX() { return m_iX; }
int Actor::getY() { return m_iY; }
int Actor::getSpeed() { return m_iSpeed; }
unsigned char Actor::getRed() { return m_type.getData().red; }
unsigned char Actor::getGreen() { return m_type.getData().green; }
unsigned char Actor::getBlue() { return m_type.getData().blue; }
ActorType &Actor::getType() { return m_type; }

void Actor::setBehaviour(Behaviour* b) {
	m_behaviour = b;
}

void Actor::setGraphic(GraphicActor* g) {
	m_graphic = g;
}

void Actor::setLastTimeHit() {
	m_iLastTimeHit = SDL_GetTicks();
}

uint32_t Actor::getLastTimeHit() {
	return m_iLastTimeHit;
}

void Actor::update(Engine *engine) {
	if (m_behaviour != 0) {
		m_behaviour->update(engine, this);
	}
	for (int attack = 0; attack < 4; ++attack) {
		if (m_iAttackDuration[attack] > 0) {
			--m_iAttackDuration[attack];
		}
	}
}

void Actor::render(int displayShiftX, int displayShiftY) {
	if (m_graphic != 0) {
		m_graphic->render(displayShiftX, displayShiftY, this);
	}
}

void Actor::attack(int attack) {
	if (m_iAttackDuration[attack] > 0) {
		return;
	}

	m_iAttackDuration[attack] = DURATION_ATTACK;
}

int Actor::getAttackDuration(int attack) {
	return m_iAttackDuration[attack];
}
