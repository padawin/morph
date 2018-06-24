#ifndef __ACTOR_TYPE__
#define __ACTOR_TYPE__

#include "types.hpp"
#include <string>
#include <memory>
#include <vector>

class Actor;

class ActorType {
	private:
	S_ActorTypeData m_data;

	public:
	ActorType(S_ActorTypeData data);
	std::shared_ptr<Actor> createActor();
	S_ActorTypeData& getData();
};

#endif
