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
	Scene(SceneManager *sceneManager);
	~Scene();

	void MovePlayer(KEY_INPUT dir);
	void EXIT();

	Player* player;
	Map* map;
	MapViewer* viewer;
private:
	SceneManager* sceneManager;
};

