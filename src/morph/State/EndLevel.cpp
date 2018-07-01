#include <iostream>
#include "EndLevel.hpp"
#include "Play.hpp"
#include "SDL2_framework/Game.h"
#include "SDL2_framework/ServiceProvider.h"

const std::string EndLevelState::s_stateID = "GAME_OVER";

EndLevelState::EndLevelState(Engine& engine) : m_engine(engine) {}

void EndLevelState::update() {
	if (ServiceProvider::getUserActions()->getActionState("CONFIRM")) {
		if (m_engine.loadNextLevel()) {
			Game::Instance()->getStateMachine()->changeState(
					new PlayState(m_engine)
					);
		}
		else {
			Game::Instance()->quit();
		}
	}
}

void EndLevelState::render() {
}

bool EndLevelState::onEnter() {
	bool ret = true;
	return ret;
}

bool EndLevelState::onExit() {
	return true;
}

std::string EndLevelState::getStateID() const {
	return s_stateID;
}
