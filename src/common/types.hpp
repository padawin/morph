#ifndef __TYPES__
#define __TYPES__

#include <utility>

struct S_ActorTypeData {
	char graphic;
	char behaviour;
	int health;
	int stamina;
	int attack;
	int speed;
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	int width;
	int height;
	int hitboxWidth;
	int hitboxHeight;
};

struct S_LevelData {
	int enemyCount = 0;
	int maxSimultaneousEnemies = 0;
	int difficulty = 0;
};

typedef std::pair<int, int> t_coordinates;

enum E_ActorAttack {ATTACK_UP, ATTACK_RIGHT, ATTACK_DOWN, ATTACK_LEFT, NO_ATTACK};

#endif
