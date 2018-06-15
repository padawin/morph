#include "Behaviour/Factory.hpp"
#include "Behaviour/Behaviour.hpp"

BehaviourFactory::BehaviourFactory() {
	m_vBehaviours = {
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
