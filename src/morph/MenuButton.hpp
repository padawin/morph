#ifndef __MenuButton__
#define __MenuButton__

#include <cstddef>

class MenuButton {
	protected:
	void (*m_callback)() = NULL;
	bool m_bActive = false;

	public:
	void setActive(const bool active);
	void setAction(void (*callback)());
	void executeAction();
};

#endif
