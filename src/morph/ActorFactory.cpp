#include "ActorFactory.hpp"
#include "ResourceManager.hpp"
#include "GUI/Actor.hpp"
#include "Actor.hpp"
#include <fstream>
#include <libgen.h>

ActorFactory::ActorFactory(GraphicFactory &graphicFactory) :
	m_behaviourFactory(BehaviourFactory()),
	m_graphicFactory(graphicFactory)
{
}

bool ActorFactory::parseTaxonomy(const char* taxonomyFile) {
	ResourceManager<S_ActorTypeData> resourceManager;
	if (!resourceManager.setResourceFile(taxonomyFile)) {
		return false;
	}

	resourceManager.parseBinaryFile();
	for (auto typeData : resourceManager.getParsedResources()) {
		ActorType type(typeData.second);
		m_mTaxonomy.push_back(type);
	}

	return true;
}

std::shared_ptr<Actor> ActorFactory::createActor(E_ActorTypes type) {
	if ((size_t) type >= m_mTaxonomy.size()) {
		return NULL;
	}

	return m_mTaxonomy[type].createActor();
}

std::shared_ptr<Actor> ActorFactory::createEnemy(E_ActorTypes type) {
	std::shared_ptr<Actor> actor = createActor(type);
	actor->setGraphic(m_graphicFactory.getGraphicActor(GRAPHIC_ACTOR_SQUARE));
	return actor;
}

std::shared_ptr<Actor> ActorFactory::createHero() {
	std::shared_ptr<Actor> hero = createActor(TYPE_PLAYER);
	hero->setBehaviour(m_behaviourFactory.getBehaviour(BEHAVIOUR_PLAYER));
	hero->setGraphic(m_graphicFactory.getGraphicActor(GRAPHIC_ACTOR_SQUARE));
	return hero;
}
