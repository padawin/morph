#ifndef __MAP__
#define __MAP__

#include <memory>
#include <vector>
#include "SDL2_framework/Vector2D.h"

class Actor;

class Map {
	private:
	int m_iWidth = 0;
	int m_iHeight = 0;
	Vector2D m_sStartPoint;
	std::vector<std::shared_ptr<Actor>> m_vActors;

	public:
	Map();
	~Map();

	void clear();

	void setDimensions(int x, int y);
	void setStartPoint(float x, float y);

	int getWidth();
	int getHeight();

	void clearDeadActors();

	bool areCoordinatesValid(int x, int y);

	void addActor(std::shared_ptr<Actor> actor);
	std::vector<std::shared_ptr<Actor>> &getActors();
};

#endif
