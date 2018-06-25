#include "Level.hpp"
#include "ResourceManager.hpp"

Level::Level(ActorFactory& actorFactory) : m_actorFactory(actorFactory) {
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
