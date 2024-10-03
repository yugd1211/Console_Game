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
	Map(Scene* scene, const std::vector<std::vector<int>>& board);
	Map(Scene *scene, int size, Position playerPos, Position exitPos);
	~Map();

	void Display() const;
	MAP_ELEMENT CheckPosition(Position& pos);
	void Swap(Position a, Position b);
	void ChangeLeftDirection();
	void ChangeRightDirection();

	std::vector<std::vector<int>> board;
private:
	int size;
	Scene* scene;
	void UpdatePlayerPosition();
};

