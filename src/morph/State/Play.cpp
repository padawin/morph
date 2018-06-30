#include "Play.hpp"
#include "Utils.hpp"
#include "GameOver.hpp"
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

	GameState::update();
}

void PlayState::render() {
	m_engine.render();
	GameState::render();
}

bool PlayState::onEnter() {
	m_engine.initialise();
	bool ret = true;
	ret &= m_engine.loadTaxonomy(
		Game::Instance()->getBinaryPath() + "/../resources/taxonomy.dat"
	);
	ret &= m_engine.loadLevels(
		Game::Instance()->getBinaryPath() + "/../resources/levels.dat"
	);
	if (ret) {
		m_engine.initialiseHero();
	}
	return ret;
}

bool PlayState::onExit() {
	return true;
}

std::string PlayState::getStateID() const {
	return s_stateID;
}
