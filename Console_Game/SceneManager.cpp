#include "SceneManager.h"
#include "Player.h"
#include "GameManager.h"
//#include "Enum.h"

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

void InitMap(vector<vector<int>>& board, int size, Position playerPos)
{
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

	for (int i = 1; i < size - 1; i++)
	{
		for (int j = 1; j < size - 1; j++)
		{
			if (board[i][j] != 0)
				continue;
			board[i][j] = rand() % MAP_WALL_RAN != 0 ? MAP_ELEMENT::WALL : 0;
		}
	}
	board[playerPos.x][playerPos.y] = MAP_ELEMENT::PLAYER;
	board[size - 2][size - 2] = MAP_ELEMENT::EXIT;
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
		board = playerMap1;
		playerPos = Position(board.size() - 2, 1);
	}
	else if (cnt == 2)
	{
		board = playerMap2;
		playerPos = Position(board.size() - 2, 1);
	}
	else
		InitMap(board, BOARD_SIZE, playerPos);
	while (!CheckCurrectPath(board, playerPos, Position(board.size() - 2, board.size() - 2)))
		InitMap(board, BOARD_SIZE, playerPos);
	scene->player = new Player(scene, playerPos);
	scene->map = new Map(scene, board);
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
