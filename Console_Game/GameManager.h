#pragma once
#include "Singleton.h"
#include "SceneManager.h"
#include "InputManager.h"
#include <iomanip> 
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <conio.h>
#define _CRTDBG_MAP_ALLOC


class GameManager : public Singleton<GameManager>
{
public:
	void GameStart();
	void GameExit();

private:
	int gameCount = 0;
};

