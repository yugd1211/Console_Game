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
	// �α׶���ũ ������������ҰŸ�
	// ���� Ʈ���������� start���� ������� ��������
	// ���� �ڽ� Ŭ������ ����, ����, ����, ������� �̺�Ʈ��� ����
	// ���� ���� �������� ���� -> �����Ǿ� �ִ� �̺�Ʈ ����
	// ���� -> ���ϸ�
	map<int, Scene*>scenes;
	Scene* currentScene;
	int currentSceneIndex;
	bool isGameEnd;
};