#include "SceneManager.h"
#include "Player.h"
#include "GameManager.h"
//#include "Enum.h"

SceneManager::~SceneManager()
{
	cout << "ScceneManager 소멸자 \n";
	for (auto& pair : scenes)
	{
		if (pair.second == nullptr)
			continue;
		delete pair.second;
		pair.second = nullptr;
	}
	scenes.clear();
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
		cout << "해당 씬은 존재하지 않습니다." << endl;
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

// bfs
bool CheckCurrectPath(vector<vector<int>>& board, Position st, Position en)
{
	vector<vector<bool>> vis(board.size());
	for (int i = 0; i < board.size(); i++)
		vis[i] = vector<bool>(board.size());

	queue<Position> q;
	q.push(st);
	vis[st.x][st.y] = 1;
	while (!q.empty())
	{
		Position curr = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int nx = curr.x + dx[i];
			int ny = curr.y + dy[i];
			if (nx < 1 || ny < 1 || nx >= board.size() - 1 || ny >= board.size() - 1)
				continue;
			if (vis[nx][ny])
				continue;
			if (board[nx][ny] == MAP_ELEMENT::WALL || board[nx][ny] == MAP_ELEMENT::OBSTACLE)
				continue;
			if (board[nx][ny] == MAP_ELEMENT::EXIT)
				return true;
			vis[nx][ny] = 1;
			q.push({ nx, ny });
		}
	}
	return false;
}

Position InitMap(vector<vector<int>>& board, int size)
{
	int playerX = 1;
	int playerY = 1;
	board = vector<vector<int>>(size);
	for (int i = 0; i < board.size(); i++)
		board[i] = vector<int>(size);

	for (int i = 0; i < size; i++)
	{
		board[0][i] = MAP_ELEMENT::WALL;
		board[i][0] = MAP_ELEMENT::WALL;
		board[size - 1][i] = MAP_ELEMENT::WALL;
		board[i][size - 1] = MAP_ELEMENT::WALL;
	}
	board[playerX][playerY] = MAP_ELEMENT::PLAYER;
	board[size - 2][size - 2] = MAP_ELEMENT::EXIT;
	for (int i = 1; i < size - 1; i++)
	{
		for (int j = 1; j < size - 1; j++)
		{
			if (board[i][j] != 0)
				continue;
			board[i][j] = rand() % 6 >= 4 ? MAP_ELEMENT::WALL : 0;
		}
	}
	return Position(playerX, playerY);
}

vector<vector<int>> playerMap1 = {
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

vector<vector<int>> playerMap2 = {
	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
	{3, 0, 0, 0, 0, 0, 0, 0, 0, 3},
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
	vector<vector<int>> board;
	Scene* scene = new Scene(this);

	scene->SetPlayerPosition(InitMap(board, BOARD_SIZE));
	while (!CheckCurrectPath(board, Position(1, 1), Position(board.size() - 2, board.size() - 2)))
		scene->SetPlayerPosition(InitMap(board, BOARD_SIZE));
	scene->player = new Player(scene, scene->GetPlayerPosition());
	scene->map = new Map(scene, board);
	scene->viewer = new MapViewer(scene->GetPlayerPosition());
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
