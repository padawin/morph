#include "MainMenu.hpp"

const int NB_MENU_ITEMS = 2;

const std::string MainMenuState::s_stateID = "MAIN_MENU";

MainMenuState::MainMenuState(Engine& engine) :
MenuState(NB_MENU_ITEMS), m_engine(engine)
{
	s_vActions.push_back(MainMenuState::startGame);
	s_vActions.push_back(MainMenuState::quitGame);
}

std::string MainMenuState::getStateID() const {
	return s_stateID;
}

bool MainMenuState::onEnter() {
	return true;
}

void MainMenuState::startGame() {
}


void MainMenuState::quitGame() {
}
