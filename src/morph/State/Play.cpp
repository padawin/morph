#include "Play.hpp"
#include "Utils.hpp"
#include "GameOver.hpp"
#include "EndLevel.hpp"
#include "Actor.hpp"
#include "SDL2_framework/Game.h"
#include "SDL2_framework/ServiceProvider.h"

const std::string PlayState::s_stateID = "PLAY";

PlayState::PlayState(Engine& engine) : m_engine(engine) {}

void PlayState::update() {
	if (ServiceProvider::getUserActions()->getActionState("QUIT")) {
		Game::Instance()->quit();
		return;
	}

	m_engine.update();
	if (m_engine.getHero()->isDead()) {
		Game::Instance()->getStateMachine()->changeState(
			new GameOverState()
		);
	}
	else if (m_engine.isLevelFinished()) {
		Game::Instance()->getStateMachine()->changeState(
			new EndLevelState(m_engine)
		);
	}

	GameState::update();
}

void PlayState::render() {
	m_engine.render();
	GameState::render();
}

bool PlayState::onEnter() {
	return true;
}

bool PlayState::onExit() {
	return true;
}

std::string PlayState::getStateID() const {
	return s_stateID;
}
