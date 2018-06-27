#ifndef __ACTOR__
#define __ACTOR__

#include <memory>
#include <string>

#define ATTACK_UP 0
#define ATTACK_RIGHT 1
#define ATTACK_DOWN 2
#define ATTACK_LEFT 3
#define DURATION_ATTACK 10

class Behaviour;
class GraphicActor;
class Engine;
class Map;
class ActorType;

class Actor {
	private:
	int m_iHealth = 0;

	ActorType &m_type;

	int m_iX = 0;
	int m_iY = 0;

	char m_iAttackDuration[4] = {0, 0, 0, 0};

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
	int getAttack();
	void setHealth(int health);
	void setMaxHealth(int maxHealth);

	bool isDead();

	void setX(int x);
	void setY(int y);

	int getX();
	int getY();
	int getSpeed();
	unsigned char getRed();
	unsigned char getGreen();
	unsigned char getBlue();

	int getWidth();
	int getHeight();
	int getHitboxWidth();
	int getHitboxHeight();

	void setLastTimeHit();
	uint32_t getLastTimeHit();

	void update(Engine *engine);
	void render(int displayShiftX, int displayShiftY);

	void attack(int attack);
	int getAttackDuration(int attack);
};

#endif
