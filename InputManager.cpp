#include "InputManager.h"

DIRECTION InputManager::InputPathway()
{
	char c = _getch();
	if (c == 72 || c == 'w')
		return DIRECTION::UP;
	else if (c == 75 || c == 'a')
		return DIRECTION::LEFT;
	else if (c == 80 || c == 's')
		return DIRECTION::DOWN;
	else if (c == 77 || c == 'd')
		return DIRECTION::RIGHT;
	return DIRECTION::NONE;
}
