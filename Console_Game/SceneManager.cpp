#include "SceneManager.h"
#include "Player.h"
#include "GameManager.h"
#include "BufferManager.h"
#include <queue>

SceneManager::~SceneManager()
{
	for (auto& pair : scenes)
	{
		if (pair.second == nullptr)
			continue;
		delete pair.second;
		pair.second = nullptr;
	}
	scenes.clear();
}

void SceneManager::Init()
{
	for (int i = 1; i <= MAX_GAME_COUNT; i++)
		SceneManager::GetInstance().AddScene(i, SceneManager::GetInstance().MakeScene());
	SceneManager::GetInstance().SetCurrentScene(1);
}

void SceneManager::AddScene(const int& index, Scene* scene)
{
	scenes[index] = scene;
}

void SceneManager::RemoveScene(const int& index)
{
	auto iter = scenes.find(index);
	if (iter != scenes.end())
	{
		delete iter->second;
		scenes.erase(iter);
	}
	else
		BufferManager::GetInstance().AddToBuffer("해당 씬은 존재하지 않습니다.\n");
}

bool SceneManager::SetCurrentScene(const int& index)
{
	auto iter = scenes.find(index);
	if (iter != scenes.end())
	{
		currentSceneIndex = iter->first;
		currentScene = iter->second;
		return true;
	}
	else
		return false;
}

std::vector<std::vector<int>> tutorial1 = {
	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
	{3, 0, 0, 0, 0, 0, 0, 0, 2, 3},
	{3, 0, 3, 3, 3, 3, 3, 3, 3, 3},
	{3, 0, 3, 3, 3, 3, 3, 3, 3, 3},
	{3, 0, 3, 3, 3, 3, 3, 3, 3, 3},
	{3, 0, 3, 3, 3, 3, 3, 3, 3, 3},
	{3, 0, 3, 3, 3, 3, 3, 3, 3, 3},
	{3, 0, 3, 3, 3, 3, 3, 3, 3, 3},
	{3, 1, 3, 3, 3, 3, 3, 3, 3, 3},
	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
};

std::vector<std::vector<int>> tutorial2 = {
	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
	{3, 0, 0, 0, 3, 0, 0, 0, 0, 3},
	{3, 0, 3, 0, 3, 0, 3, 3, 0, 3},
	{3, 0, 3, 0, 3, 0, 3, 3, 0, 3},
	{3, 0, 3, 0, 3, 0, 3, 3, 0, 3},
	{3, 0, 3, 0, 3, 0, 3, 3, 0, 3},
	{3, 0, 3, 0, 3, 0, 3, 3, 0, 3},
	{3, 0, 3, 0, 0, 0, 3, 3, 0, 3},
	{3, 1, 3, 0, 0, 0, 3, 3, 2, 3},
	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
};

// 맵도 같이 생성
Scene* SceneManager::MakeScene()
{
	static int cnt = 0;
	cnt++;
	vector<vector<int>> board;
	Scene* scene = new Scene(this);
	Position playerPos(1, 1);
	if (cnt == 1)
	{
		playerPos = Position(tutorial1.size() - 2, 1);
		scene->map = new Map(scene, tutorial1);
	}
	else if (cnt == 2)
	{
		playerPos = Position(tutorial2.size() - 2, 1);
		scene->map = new Map(scene, tutorial2);
	}
	else
		scene->map = new Map(scene, BOARD_SIZE, playerPos, Position(BOARD_SIZE - 2, BOARD_SIZE - 2));
	scene->player = new Player(scene, playerPos);
	scene->viewer = new MapViewer(playerPos);
	return scene;
}

Scene* SceneManager::MakeScene(vector<vector<int>>& board)
{
	return nullptr;
}

Scene* SceneManager::GetCurrentScene()
{
	if (currentSceneIndex == -1)
		nullptr;
	return scenes[currentSceneIndex];
}

int SceneManager::GetCurrentSceneIndex()
{
	return currentSceneIndex;
}

bool SceneManager::IsGameEnd()
{
	return isGameEnd;
}

void SceneManager::SetGameEnd(bool b)
{
	isGameEnd = b;
}

void SceneManager::LoadNextScene()
{
	if (!SetCurrentScene(currentSceneIndex + 1))
	{
		GameManager::GetInstance().SetGameOver(true);
	}
}
