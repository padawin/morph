#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include "Menu.hpp"

class MainMenuState : public Menu {
	private:
	static const std::string s_stateID;

	public:
	virtual std::string getStateID() const;
};

#endif
