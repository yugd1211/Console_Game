#include "Map.h"

Map::Map(Scene* scene, const vector<vector<int>>& board) : scene(scene), board(board), size(board.size())
{
}

void Map::DisplayMap() const
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
	return MAP_ELEMENT::VOID;
}

void Map::Swap(Position a, Position b)
{
	int tmp = board[a.x][a.y];
	board[a.x][a.y] = board[b.x][b.y];
	board[b.x][b.y] = tmp;
}


