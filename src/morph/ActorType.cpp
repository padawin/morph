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

std::shared_ptr<Actor> ActorType::createActor() {
	std::shared_ptr<Actor> actor(std::make_shared<Actor>(*this));
	actor->setHealth((int) m_data.health);
	actor->setMaxHealth(m_data.health);
	actor->setAttack(m_data.attack);
	actor->setColor(m_data.red, m_data.green, m_data.blue);
	return actor;
}
