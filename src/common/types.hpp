#ifndef __TYPES__
#define __TYPES__

#include <utility>

struct S_ActorTypeData {
	int graphic;
	int health;
	int attack;
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	int width;
	int height;
	int hitboxWidth;
	int hitboxHeight;
};

struct S_LevelData {
	int enemyCount;
	int maxSimultaneousEnemies;
	int difficulty;
};

typedef std::pair<int, int> t_coordinates;

#endif
