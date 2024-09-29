#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Scene.h"
#include "Enum.h"
#include "Singleton.h"

class Player;
using namespace std;

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager() : currentScene(nullptr), currentSceneIndex(-1), isGameEnd(false) {}
	~SceneManager();

	void AddScene(const int& index, Scene* scene);
	void RemoveScene(const int& index);
	bool SetCurrentScene(const int& index);

	Scene* MakeScene();
	Scene* GetCurrentScene();
	int GetCurrentSceneIndex();
	bool IsGameEnd();
	void SetGameEnd(bool b);
	void LoadNextScene();

private:
	// 로그라이크 방식으로진행할거면
	// 씬을 트리형식으로 start부터 뻗어나가도 괜찮을듯
	// 씬의 자식 클래스로 전투, 마을, 상점, 물약등의 이벤트들로 구성
	// 가지 또한 랜덤으로 생성 -> 구성되어 있는 이벤트 랜덤
	// 전투 -> 포켓몬
	map<int, Scene*>scenes;
	Scene* currentScene;
	int currentSceneIndex;
	bool isGameEnd;
};