#ifndef __END_LEVEL_STATE__
#define __END_LEVEL_STATE__

#include "SDL2_framework/GameState.h"
#include "Engine.hpp"

class EndLevelState : public GameState {
	private:
	static const std::string s_stateID;
	Engine& m_engine;

	public:
	EndLevelState(Engine& engine);
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const;
};

#endif
