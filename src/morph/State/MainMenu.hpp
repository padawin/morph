#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include "Menu.hpp"
#include "Engine.hpp"

class MainMenuState : public MenuState {
	private:
	static const std::string s_stateID;
	Engine& m_engine;

	public:
	MainMenuState(Engine& engine);
	bool onEnter();
	virtual std::string getStateID() const;
	// Menu actions
	static void startGame();
	static void quitGame();
};

#endif
