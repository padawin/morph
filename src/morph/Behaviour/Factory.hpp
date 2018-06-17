#ifndef __BEHAVIOUR__FACTORY__
#define __BEHAVIOUR__FACTORY__

#include <vector>

class Behaviour;

enum E_Behaviours {BEHAVIOUR_PLAYER};

class BehaviourFactory {
	private:
	std::vector<Behaviour*> m_vBehaviours = {};

	public:
	BehaviourFactory();
	~BehaviourFactory();
	Behaviour *getBehaviour(E_Behaviours behaviour);

};

#endif
