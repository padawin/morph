#include <SDL2/SDL.h>
#include <sstream>
#include <string>
#include "ActorType.hpp"
#include "Actor.hpp"
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"

ActorType::ActorType(S_ActorTypeData data) :
	m_data(data)
{
}

std::shared_ptr<Actor> ActorType::createActor(GraphicFactory& graphicFactory) {
	std::shared_ptr<Actor> actor(std::make_shared<Actor>(*this));
	actor->setHealth(actor->getMaxHealth());
	actor->setGraphic(graphicFactory.getGraphicActor(m_data.graphic));
	return actor;
}

S_ActorTypeData& ActorType::getData() {
	return m_data;
}
