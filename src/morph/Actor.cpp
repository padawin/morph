#include <iostream>
#include "Actor.hpp"
#include "Engine.hpp"
#include "Behaviour/Behaviour.hpp"
#include "GUI/Actor.hpp"
#include <limits.h>

#define LIMIT_FIELD_OF_VIEW 6
#define INVINCIBILITY_FRAME 10

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
	return m_iHealth < 0;
}

void Actor::setX(int x) { m_iX = x; }
void Actor::setY(int y) { m_iY = y; }
int Actor::getX() { return m_iX; }
int Actor::getY() { return m_iY; }
int Actor::getSpeed() { return m_type.getData().speed; }
unsigned char Actor::getRed() { return m_type.getData().red; }
unsigned char Actor::getGreen() { return m_type.getData().green; }
unsigned char Actor::getBlue() { return m_type.getData().blue; }
int Actor::getWidth() { return m_type.getData().width; }
int Actor::getHeight() { return m_type.getData().height; }
int Actor::getHitboxWidth() { return m_type.getData().hitboxWidth; }
int Actor::getHitboxHeight() { return m_type.getData().hitboxHeight; }
SDL_Rect Actor::getHitbox() {
	SDL_Rect hitbox;
	hitbox.x = m_iX - getHitboxWidth() / 2;
	hitbox.y = m_iY - getHitboxHeight() / 2;
	hitbox.w = getHitboxWidth();
	hitbox.h = getHitboxHeight();
	return hitbox;
}
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
			m_iAttackDuration[attack] -= getSpeed();
		}
		else {
			m_iAttackDuration[attack] = 0;
		}
	}
	if (m_iInvincibilityFrame > 0) {
		--m_iInvincibilityFrame;
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

	m_iAttackDuration[attack] = 100;
}

std::map<int, SDL_Rect> Actor::getAttacks() {
	return m_graphic->getAttacks(this);
}

int Actor::getAttackProgress(int attack) {
	return m_iAttackDuration[attack];
}

bool Actor::hasInvincibilityFrame() {
	return m_iInvincibilityFrame > 0;
}

void Actor::setInvincibilityFrame() {
	m_iInvincibilityFrame = INVINCIBILITY_FRAME;
}

int Actor::canTouch(Actor* actor) {
	return m_graphic->canTouch(this, actor);
}
