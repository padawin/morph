#include "Behaviour/Factory.hpp"
#include "Behaviour/Player.hpp"
#include "Behaviour/Enemy.hpp"

BehaviourFactory::BehaviourFactory() {
	m_vBehaviours = {
		new BehaviourPlayer(),
		new BehaviourEnemy()
	};
}

BehaviourFactory::~BehaviourFactory() {
	for (auto behaviour : m_vBehaviours) {
		delete behaviour;
	}
}

Behaviour *BehaviourFactory::getBehaviour(long unsigned int behaviour) {
	return m_vBehaviours[behaviour];
}
