#include "Map.h"

using namespace std;
Map::Map(Scene* scene, const vector<vector<int>>& board) : scene(scene), board(board), size(board.size())
{
}

void Map::Display() const
{
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board.size(); j++)
		{
			if (board[i][j] == MAP_ELEMENT::PLAYER)
			{
				cout << PRINT_PLAYER;
			}
			else if (board[i][j] == MAP_ELEMENT::WALL)
				cout << PRINT_WALL;
			else if (board[i][j] == MAP_ELEMENT::OBSTACLE)
				cout << PRINT_OBSTACLE;
			else if (board[i][j] == MAP_ELEMENT::EXIT)
				cout << PRINT_EXIT;
			else
				cout << "  ";
		}
		cout << "\n";
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
	for (int i = 0; i < board.size(); i++)
		for (int j = 0; j < board.size(); j++)
			if (board[i][j] == MAP_ELEMENT::PLAYER)
				scene->player->pos = Position(i, j);

}

void Map::ChangeLeftDirection()
{
	for (int i = 0; i < board.size() - 1; i++)
		for (int j = 0; j < i; j++)
			swap(board[i][j], board[j][i]);

	for (int i = 0; i < board.size(); i++)
		for (int j = 0; j < board.size() / 2; j++)
			swap(board[i][j], board[i][board.size() - 1 - j]);
	UpdatePlayerPosition();
}

void Map::ChangeRightDirection()
{
	for (int i = 0; i < board.size() - 1; i++)
		for (int j = 0; j < board.size() - i - 1; j++)
			swap(board[i][j], board[board.size() - j - 1][board.size() - i - 1]);

	for (int i = 0; i < board.size(); i++)
		for (int j = 0; j < board.size() / 2; j++)
			swap(board[i][j], board[i][board.size() - j - 1]);
	UpdatePlayerPosition();
}


