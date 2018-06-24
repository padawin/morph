#ifndef __TYPES__
#define __TYPES__

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

typedef std::pair<int, int> t_coordinates;

#endif
