#pragma once
#include "Singleton.h"
//#include "SceneManager.h"
#include "MapViewer.h"
#include "Map.h"
#include "Enum.h"
#include <iomanip>
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#define _CRTDBG_MAP_ALLOC



class GameManager : public Singleton<GameManager>
{
public:
	void GameStart();
	void GameExit();
	void DisplayPathway() const;
	bool GameOver() { return isGameOver; }
	void SetGameOver(bool b) { isGameOver = b; }

private:
	bool isGameOver = false;
	int gameCount = 0;
};

