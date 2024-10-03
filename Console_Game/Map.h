#pragma once

#include <iostream>
#include <vector>
#include "Position.h"
#include "Scene.h"
#include "Player.h"
#include "Enum.h"

class Map
{
public:
	Map(Scene *scene, const std::vector<std::vector<int>>& board);
	~Map()
	{
		for (int i = 0; i < board.size(); i++)
		{
			board[i].clear();
			std::vector<int>().swap(board[i]);
		}
		board.clear();
		std::vector<std::vector<int>>().swap(board);
	}

	void Display() const;
	MAP_ELEMENT CheckPosition(Position& pos);
	void Swap(Position a, Position b);
	std::vector<std::vector<int>> board;
	void ChangeLeftDirection();
	void ChangeRightDirection();
	void UpdatePlayerPosition();
private:
	int size;
	Scene* scene;
};

