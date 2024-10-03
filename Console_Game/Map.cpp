#include "Map.h"
#include "BufferManager.h"
#include <queue>
using namespace std;

// bfs
bool ValidateMapPath(vector<vector<int>>& board, Position st)
{
	if (board.empty() || board[0].empty())
		return false;
	
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

void CreateRandomMap(vector<vector<int>>& board, int size, Position playerPos, Position exitPos)
{
	board.clear();
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
			board[i][j] = rand() % RANDOM_MAP_DIFFICULTY != 0 ? MAP_ELEMENT::WALL : 0;
		}
	}
	board[playerPos.x][playerPos.y] = MAP_ELEMENT::PLAYER;
	board[exitPos.x][exitPos.y] = MAP_ELEMENT::EXIT;
}

Map::Map(Scene* scene, const vector<vector<int>>& board) : scene(scene), board(board), size(board.size())
{
}

Map::Map(Scene* scene, int size, Position playerPos, Position exitPos) : scene(scene), size(size)
{
	while  (!ValidateMapPath(board, playerPos))
		CreateRandomMap(board, size, playerPos, exitPos);
}

Map::~Map() 
{
	for (int i = 0; i < board.size(); i++)
	{
		board[i].clear();
		std::vector<int>().swap(board[i]);
	}
	board.clear();
	std::vector<std::vector<int>>().swap(board);
}

void Map::Display() const
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (board[i][j] == MAP_ELEMENT::PLAYER)
				BufferManager::GetInstance().AddToBuffer(PRINT_PLAYER);
			else if (board[i][j] == MAP_ELEMENT::WALL)
				BufferManager::GetInstance().AddToBuffer(PRINT_WALL);
			else if (board[i][j] == MAP_ELEMENT::OBSTACLE)
				BufferManager::GetInstance().AddToBuffer(PRINT_OBSTACLE);
			else if (board[i][j] == MAP_ELEMENT::EXIT)
				BufferManager::GetInstance().AddToBuffer(PRINT_EXIT);
			else
				BufferManager::GetInstance().AddToBuffer("  ");
		}
		BufferManager::GetInstance().AddToBuffer("\n");
	}
}

MAP_ELEMENT Map::CheckPosition(Position& pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= size || pos.y >= size)
		return MAP_ELEMENT::WALL;
	// 비트 마스킹으로 해도될듯
	if (board[pos.x][pos.y] == MAP_ELEMENT::WALL ||
		board[pos.x][pos.y] == MAP_ELEMENT::OBSTACLE ||
		board[pos.x][pos.y] == MAP_ELEMENT::ENEMY ||
		board[pos.x][pos.y] == MAP_ELEMENT::OTHER)
		return MAP_ELEMENT::WALL;
	else if (board[pos.x][pos.y] == MAP_ELEMENT::EXIT)
		return MAP_ELEMENT::EXIT;
	return MAP_ELEMENT::EMPTY;
}

void Map::Swap(Position a, Position b)
{
	swap(board[a.x][a.y], board[b.x][b.y]);
}

void Map::UpdatePlayerPosition()
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (board[i][j] == MAP_ELEMENT::PLAYER)
				scene->player->pos = Position(i, j);

}

void Map::ChangeLeftDirection()
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < i; j++)
			swap(board[i][j], board[j][i]);

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size / 2; j++)
			swap(board[i][j], board[i][size - j - 1]);
	UpdatePlayerPosition();
}

void Map::ChangeRightDirection()
{
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
			swap(board[i][j], board[size - j - 1][size - i - 1]);

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size / 2; j++)
			swap(board[i][j], board[i][size - j - 1]);
	UpdatePlayerPosition();
}


