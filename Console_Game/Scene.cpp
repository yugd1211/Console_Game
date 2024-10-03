#include "Scene.h"
#include "Player.h"
#include "SceneManager.h"
#include "Map.h"

Scene::Scene(SceneManager* sceneManager) :
	sceneManager(sceneManager), player(nullptr), map(nullptr), viewer(nullptr) 
{
}

Scene::~Scene()
{
	if (player)
		delete player;
	if (map)
		delete map;
}

void Scene::MovePlayer(KEY_INPUT dir)
{
	if (dir == KEY_INPUT::TURN_LEFT)
		map->ChangeLeftDirection();
	else if (dir == KEY_INPUT::TURN_RIGHT)
		map->ChangeRightDirection();
	else
	{
		Position nxt = Position(player->pos);
		nxt.x = player->pos.x + dx[dir];
		nxt.y = player->pos.y + dy[dir];
		MAP_ELEMENT nxtElement = map->CheckPosition(nxt);
		if (nxtElement == MAP_ELEMENT::EMPTY)
		{
			map->Swap(player->pos, nxt);
			player->pos = nxt;
		}
		else if (nxtElement == MAP_ELEMENT::EXIT)
			EXIT();
	}
}

void Scene::EXIT()
{
	sceneManager->LoadNextScene();
}
