#pragma once
#include "Singleton.h"
#include "Enum.h"
#include <conio.h>
class InputManager : public Singleton<InputManager>
{
public:
	KEY_INPUT InputPathway();
};

