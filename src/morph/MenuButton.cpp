#include "MenuButton.hpp"

void MenuButton::setActive(const bool active) {
	m_bActive = active;
}

void MenuButton::setAction(void (*callback)()) {
	m_callback = callback;
}

void MenuButton::executeAction() {
	m_callback();
}
