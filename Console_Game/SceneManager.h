#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Scene.h"
#include "Enum.h"
#include "Singleton.h"
#include "InputManager.h"
#include "BufferManager.h"

class Player;
class GamaManager;
using namespace std;

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager() : currentScene(nullptr), currentSceneIndex(-1), isGameEnd(false) {}
	~SceneManager();

	void Init();
	void AddScene(const int& index, Scene* scene);
	void RemoveScene(const int& index);
	bool SetCurrentScene(const int& index);

	Scene* MakeScene();
	Scene* MakeScene(vector<vector<int>> &board);
	Scene* GetCurrentScene();
	int GetCurrentSceneIndex();
	bool IsGameEnd();
	void SetGameEnd(bool b);
	void LoadNextScene();

private:

	map<int, Scene*>scenes;
	Scene* currentScene;
	int currentSceneIndex;
	bool isGameEnd;
};