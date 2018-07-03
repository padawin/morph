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
void Actor::setStamina(int stamina) { m_fStamina = (double) stamina; }
double Actor::getStamina() { return m_fStamina; }
int Actor::getMaxStamina() { return m_type.getData().stamina; }
int Actor::getAttack() { return m_type.getData().attack; }

bool Actor::isDead() {
	return m_iHealth <= 0;
}

void Actor::setX(double x) { m_dX = x; }
void Actor::setY(double y) { m_dY = y; }
double Actor::getX() { return m_dX; }
double Actor::getY() { return m_dY; }
const Vector2D Actor::getPosition() {
	return Vector2D((float) m_dX, (float) m_dY);
}
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
	hitbox.x = (int) (m_dX - getHitboxWidth() / 2);
	hitbox.y = (int) (m_dY - getHitboxHeight() / 2);
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
	for (int attackSide = 0; attackSide < 4; ++attackSide) {
		if (m_iAttackDuration[attackSide] > 0) {
			m_iAttackDuration[attackSide] -= getSpeed() * 2;
		}
		else {
			m_iAttackDuration[attackSide] = 0;
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

void Actor::attack(int attackSide) {
	if (m_iAttackDuration[attackSide] > 0) {
		return;
	}

	m_iAttackDuration[attackSide] = 100;
}

void Actor::cancelAttacks() {
	m_iAttackDuration[0] = 0;
	m_iAttackDuration[1] = 0;
	m_iAttackDuration[2] = 0;
	m_iAttackDuration[3] = 0;
}

std::map<int, SDL_Rect> Actor::getAttacks() {
	return m_graphic->getAttacks(this);
}

int Actor::getAttackProgress(int attackSide) {
	return m_iAttackDuration[attackSide];
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
