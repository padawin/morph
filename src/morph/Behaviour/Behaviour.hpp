#ifndef __BEHAVIOUR__
#define __BEHAVIOUR__

class Engine;
class Actor;

class Behaviour {
	public:
	virtual bool update(Engine *engine, Actor *actor) = 0;
	virtual ~Behaviour() {};
};

#endif
