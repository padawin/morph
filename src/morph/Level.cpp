#include "Level.hpp"
#include "ResourceManager.hpp"

Level::Level(ActorFactory& actorFactory) : m_actorFactory(actorFactory) {
}

void Level::update(Map& m) {
	S_LevelData& currentLevel = m_vLevelsData[m_iCurrentLevel];
	if ((signed) m.getActors().size() < currentLevel.maxSimultaneousEnemies + 1) {
		int generateEnemy = rand() % 1000;
		if (generateEnemy > 700) {
			m.addActor(m_actorFactory.createActor(TYPE_GREEN_SQUARE));
			currentLevel.enemyCount -= 1;
		}
	}
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
