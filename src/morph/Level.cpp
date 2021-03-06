#include <stdlib.h>
#include "Actor.hpp"
#include "Level.hpp"
#include "ResourceManager.hpp"

Level::Level(ActorFactory& actorFactory) : m_actorFactory(actorFactory) {
}

void Level::update(Map& m) {
	S_LevelData& currentLevel = m_vLevelsData[m_iCurrentLevel];
	if (!currentLevel.enemyCount) {
		return;
	}

	int minX = -20,
		maxX = 20,
		minY = -20,
		maxY = 20;
	if ((signed) m.getActors().size() < currentLevel.maxSimultaneousEnemies + 1) {
		int generateEnemy = rand() % 1000;
		if (generateEnemy > 700) {
			std::shared_ptr<Actor> actor = _createActor();
			int side = rand() % 4,
				x, y;
			switch (side) {
				case 0: // up
					x = minX + rand() % (m.getWidth() + maxX - minX);
					y = minY;
					break;
				case 1: // right
					x = m.getWidth() + maxX;
					y = minY + rand() % (m.getWidth() + maxY - minY);
					break;
				case 2: // down
					x = minX + rand() % (m.getWidth() + maxX - minX);
					y = m.getHeight() + maxY;
					break;
				default: // 3, left
					x = minX;
					y = minY + rand() % (m.getWidth() + maxY - minY);
					break;
			}
			actor->setX(x);
			actor->setY(y);
			actor->setHollow(true);
			m.addActor(actor);
			currentLevel.enemyCount -= 1;
		}
	}
}

std::shared_ptr<Actor> Level::_createActor() {
	// first type is the player
	int difficulty = m_vLevelsData[m_iCurrentLevel].difficulty;
	if (difficulty >= NB_TYPES) {
		difficulty = NB_TYPES - 1;
	}
	E_ActorTypes type = (E_ActorTypes) (1 + rand() % difficulty);
	return m_actorFactory.createActor(type);
}

bool Level::parseLevels(const char* filePath) {
	ResourceManager<S_LevelData> resourceManager;
	if (!resourceManager.setResourceFile(filePath)) {
		return false;
	}

	resourceManager.parseBinaryFile();
	for (auto typeData : resourceManager.getParsedResources()) {
		S_LevelData level(typeData.second);
		m_vLevelsData.push_back(level);
	}

	return true;
}

bool Level::isFinished() {
	return !m_vLevelsData[m_iCurrentLevel].enemyCount;
}

bool Level::load(int index) {
	int nextIndex = (int) m_iCurrentLevel + index;
	if (nextIndex < 0 || (unsigned) nextIndex > m_vLevelsData.size() - 1) {
		return false;
	}
	else {
		m_iCurrentLevel = (unsigned) nextIndex;
		return true;
	}
}
