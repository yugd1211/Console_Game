#pragma once
#include <iostream>

class Player;
class Map;
class SceneManager;
#include "Position.h"
#include "Enum.h"
#include "MapViewer.h"
using namespace std;


class Scene
{
public:
	Scene(SceneManager *sceneManager) : 
		sceneManager(sceneManager), player(nullptr), map(nullptr), viewer(nullptr) {};
	~Scene() 
	{
		cout << "scene ¼Ò¸êÀÚ\n";
		if (player)
			delete player;
		if (map)
			delete map;
	}
	void SetPlayerPosition(Position pos);
	Position GetPlayerPosition() const;
	void MovePlayer(KEY_INPUT dir);
	void EXIT();

	Player* player;
	Map* map;
	MapViewer* viewer;
	Position playerPos;
private:
	SceneManager* sceneManager;
};

