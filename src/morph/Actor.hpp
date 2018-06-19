#ifndef __ACTOR__
#define __ACTOR__

#include <memory>
#include <string>

class Behaviour;
class GraphicActor;
class Engine;
class Map;
class ActorType;

class Actor {
	private:
	int m_iHealth = 0;
	int m_iMaxHealth = 0;
	int m_iAttack = 0;

	unsigned char m_cRed = 0;
	unsigned char m_cGreen = 0;
	unsigned char m_cBlue = 0;

	ActorType &m_type;

	int m_iX = 0;
	int m_iY = 0;
	int m_iSpeed = 2;

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
	void setAttack(int attack);

	bool isDead();

	void setX(int x);
	void setY(int y);
	void setColor(unsigned char red, unsigned char green, unsigned char blue);
	int getX();
	int getY();
	int getSpeed();
	unsigned char getRed();
	unsigned char getGreen();
	unsigned char getBlue();

	void setLastTimeHit();
	uint32_t getLastTimeHit();

	void update(Engine *engine);
	void render(int displayShiftX, int displayShiftY);

	void attack(std::shared_ptr<Actor> target);
};

#endif
