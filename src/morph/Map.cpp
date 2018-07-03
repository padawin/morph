#include "Map.hpp"
#include "Actor.hpp"

Map::Map() :
	m_sStartPoint(Vector2D()),
	m_vActors({}) {
}

Map::~Map() {
	clear();
}

void Map::clear() {
	m_vActors.clear();
}

void Map::clearActors(bool deadOnly) {
	long unsigned i = 0;
	for (auto it = m_vActors.begin(); it != m_vActors.end();) {
		if (m_vActors[i]->isDead() || !deadOnly) {
			it = m_vActors.erase(it);
		}
		else {
			++it;
			++i;
		}
	}
}

void Map::clearDeadActors() {
	clearActors(true);
}

void Map::setStartPoint(float x, float y) {
	m_sStartPoint.setX(x);
	m_sStartPoint.setY(y);
}

void Map::setDimensions(int w, int h) {
	m_iWidth = w;
	m_iHeight = h;
}

int Map::getWidth() {
	return m_iWidth;
}

int Map::getHeight() {
	return m_iHeight;
}

void Map::addActor(std::shared_ptr<Actor> actor) {
	m_vActors.push_back(actor);
}

bool Map::areCoordinatesValid(int x, int y) {
	return x >= 0 && y >= 0 && x < m_iWidth && y < m_iHeight;
}

std::vector<std::shared_ptr<Actor>> &Map::getActors() {
	return m_vActors;
}
