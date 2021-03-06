#ifndef __ACTOR_FACTORY__
#define __ACTOR_FACTORY__

#include <vector>
#include <memory>
#include "Behaviour/Factory.hpp"
#include "GUI/Factory.hpp"
#include "ActorType.hpp"
#include "dataTypes.hpp"

class Actor;
class ActorType;
class BehaviourFactory;
class GraphicFactory;

class ActorFactory {
	private:
	std::vector<ActorType> m_mTaxonomy = {};
	BehaviourFactory m_behaviourFactory;
	GraphicFactory &m_graphicFactory;

	public:
	ActorFactory(GraphicFactory &graphicFactory);
	bool parseTaxonomy(const char* taxonomyFile);
	std::shared_ptr<Actor> createActor(E_ActorTypes type);
	std::shared_ptr<Actor> createHero();
};

#endif
