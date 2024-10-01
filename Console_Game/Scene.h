#pragma once
#include <iostream>

class Player;
class Map;
class SceneManager;
#include "Position.h"
#include "Enum.h"
using namespace std;


class Scene
{
public:
	Scene(SceneManager *sceneManager) : sceneManager(sceneManager), player(nullptr), map(nullptr) {};
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
	void MovePlayer(DIRECTION dir);
	void EXIT();

	Player* player;
	Map* map;
private:
	SceneManager* sceneManager;
	Position playerPos;
};

