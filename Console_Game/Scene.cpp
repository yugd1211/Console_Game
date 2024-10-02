#include "Scene.h"
#include "Player.h"
#include "SceneManager.h"

void Scene::SetPlayerPosition(Position pos)
{
	playerPos = pos;
}

Position Scene::GetPlayerPosition() const
{
	return playerPos;
}

void Scene::MovePlayer(KEY_INPUT dir)
{
	Position nxt = Position(player->pos);
	nxt.x = player->pos.x + dx[dir];
	nxt.y = player->pos.y + dy[dir];
	MAP_ELEMENT nxtElement = map->CheckPosition(nxt);
	if (nxtElement == MAP_ELEMENT::VOID)
	{
		map->Swap(player->pos, nxt);
		player->pos = nxt;
	}
	else if (nxtElement == MAP_ELEMENT::EXIT)
		EXIT();
}

void Scene::EXIT()
{
	sceneManager->LoadNextScene();
}
