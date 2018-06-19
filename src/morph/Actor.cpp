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
void Actor::setMaxHealth(int maxHealth) { m_iMaxHealth = maxHealth; }
void Actor::setAttack(int attackValue) { m_iAttack = attackValue; }
int Actor::getHealth() { return m_iHealth; }
int Actor::getMaxHealth() { return m_iMaxHealth; }
int Actor::getAttack() { return m_iAttack; }

bool Actor::isDead() {
	return m_iHealth == 0;
}

void Actor::setX(int x) { m_iX = x; }
void Actor::setY(int y) { m_iY = y; }
void Actor::setColor(unsigned char red, unsigned char green, unsigned char blue) {
	m_cRed = red;
	m_cGreen = green;
	m_cBlue = blue;
}
int Actor::getX() { return m_iX; }
int Actor::getY() { return m_iY; }
int Actor::getSpeed() { return m_iSpeed; }
unsigned char Actor::getRed() { return m_cRed; }
unsigned char Actor::getGreen() { return m_cGreen; }
unsigned char Actor::getBlue() { return m_cBlue; }
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
}

void Actor::render(int displayShiftX, int displayShiftY) {
	if (m_graphic != 0) {
		m_graphic->render(displayShiftX, displayShiftY, this);
	}
}

void Actor::attack(std::shared_ptr<Actor> target) {
	target->m_iHealth -= m_iAttack;
	if (target->m_iHealth < 0) {
		target->m_iHealth = 0;
	}
	target->setLastTimeHit();
}
