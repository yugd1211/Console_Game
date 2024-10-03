#include "InputManager.h"

KEY_INPUT InputManager::GetInput()
{
	char c = _getch();
	if (c == 72 || c == 'w')
		return KEY_INPUT::UP;
	else if (c == 75 || c == 'a')
		return KEY_INPUT::LEFT;
	else if (c == 80 || c == 's')
		return KEY_INPUT::DOWN;
	else if (c == 77 || c == 'd')
		return KEY_INPUT::RIGHT;
	else if (c == '`')
		return KEY_INPUT::GAME_OVER;
	else if (c == 'q')
		return KEY_INPUT::TURN_LEFT;
	else if (c == 'e')
		return KEY_INPUT::TURN_RIGHT;
	return KEY_INPUT::NONE;
}
