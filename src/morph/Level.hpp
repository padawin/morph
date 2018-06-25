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

	public:
	Level(ActorFactory& actorFactory);
	void update(Map& m);
	bool parseLevels(const char* filePath);
};

#endif
