#include "Behaviour/Factory.hpp"
#include "Behaviour/Player.hpp"

BehaviourFactory::BehaviourFactory() {
	m_vBehaviours = {
		new BehaviourPlayer()
	};
}

BehaviourFactory::~BehaviourFactory() {
	for (auto behaviour : m_vBehaviours) {
		delete behaviour;
	}
}

Behaviour *BehaviourFactory::getBehaviour(E_Behaviours behaviour) {
	return m_vBehaviours[behaviour];
}
