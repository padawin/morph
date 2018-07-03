#ifndef __LEVEL__
#define __LEVEL__

#include "types.hpp"
#include "ActorFactory.hpp"
#include "Map.hpp"
#include <vector>

class Level {
	private:
	long unsigned int m_iCurrentLevel = 0;
	std::vector<S_LevelData> m_vLevelsData = {};
	ActorFactory& m_actorFactory;

	std::shared_ptr<Actor> _createActor();

	public:
	Level(ActorFactory& actorFactory);
	void update(Map& m);
	bool parseLevels(const char* filePath);
	bool isFinished();
	bool loadNext();
};

#endif
