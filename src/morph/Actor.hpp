#ifndef __ACTOR__
#define __ACTOR__

#include <memory>
#include <string>
#include <map>
#include "SDL2/SDL.h"
#include "SDL2_framework/Vector2D.h"

#define ATTACK_UP 0
#define ATTACK_RIGHT 1
#define ATTACK_DOWN 2
#define ATTACK_LEFT 3

class Behaviour;
class GraphicActor;
class Engine;
class Map;
class ActorType;

class Actor {
	private:
	int m_iHealth = 0;
	double m_fStamina = 0;
	int m_iStaminaCooldown = 0;

	ActorType &m_type;

	double m_dX = 0;
	double m_dY = 0;

	int m_iAttackDuration[4] = {0, 0, 0, 0};
	int m_iInvincibilityFrame = 0;

	Behaviour* m_behaviour;
	GraphicActor* m_graphic;

	// to know when to display actor health
	uint32_t m_iLastTimeHit = 0;

	public:
	Actor(ActorType &type);
	void setBehaviour(Behaviour* b);
	void setGraphic(GraphicActor* b);

	ActorType &getType();

	int getHealth();
	int getMaxHealth();
	double getStamina();
	int getMaxStamina();
	int getAttack();
	void setHealth(int health);
	void setStamina(int stamina);

	bool isDead();

	void setX(double x);
	void setY(double y);

	double getX();
	double getY();
	const Vector2D getPosition();
	int getSpeed();
	unsigned char getRed();
	unsigned char getGreen();
	unsigned char getBlue();

	int getWidth();
	int getHeight();
	int getHitboxWidth();
	int getHitboxHeight();
	SDL_Rect getHitbox();

	void setLastTimeHit();
	uint32_t getLastTimeHit();

	void update(Engine *engine);
	void render(int displayShiftX, int displayShiftY);

	void attack(int attackSide);
	void cancelAttacks();
	std::map<int, SDL_Rect> getAttacks();
	int getAttackProgress(int attackSide);

	bool hasInvincibilityFrame();
	void setInvincibilityFrame();

	int canTouch(Actor* actor);
};

#endif
