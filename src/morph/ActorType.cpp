#include "ActorType.hpp"
#include "Actor.hpp"

ActorType::ActorType(S_ActorTypeData data) :
	m_data(data)
{
}

std::shared_ptr<Actor> ActorType::createActor(
	GraphicFactory& graphicFactory,
	BehaviourFactory& behaviourFactory
) {
	std::shared_ptr<Actor> actor(std::make_shared<Actor>(*this));
	actor->setHealth(actor->getMaxHealth());
	actor->setStamina(actor->getMaxStamina());
	actor->setGraphic(graphicFactory.getGraphicActor(
		(long unsigned) m_data.graphic)
	);
	actor->setBehaviour(behaviourFactory.getBehaviour(
		(long unsigned) m_data.behaviour)
	);
	return actor;
}

S_ActorTypeData& ActorType::getData() {
	return m_data;
}
