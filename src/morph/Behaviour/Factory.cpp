#include "Behaviour/Factory.hpp"
#include "Behaviour/Player.hpp"
#include "Behaviour/EnemySquare.hpp"

BehaviourFactory::BehaviourFactory() {
	m_vBehaviours = {
		new BehaviourPlayer(),
		new BehaviourEnemySquare()
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
