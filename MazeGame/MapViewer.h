#pragma once
#include <vector>
#include <iostream>
#include "Position.h"
#include "Enum.h"

const static std::string Void = "  ";
const static std::string Wall = "бс";

class MapViewer
{
public:

	MapViewer(int x, int y);
	MapViewer(Position pos);

	void Display() const;
	void Rendering(std::vector<std::vector<int>> &map);

private:

	void InitDisplayMap();
	void SetStraight(std::vector<std::vector<int>>& map);
	void SetCornerBoundary(std::vector<std::vector<int>>& map);
	int GetNearestPlayerForward(std::vector<std::vector<int>>& map);
	int GetPathLength(std::vector<std::vector<int>>& map, int st, int dir);
	void SetLeftEdgeWall(int cornerPosition, int cornerLenght);
	void SetRightEdgeWall(int cornerPosition, int cornerLenght);
	void SetLeftHorizontalWall(std::vector<std::vector<int>>& map, int cornerPosition, int cornerLenght);
	void SetRightHorizontalWall(std::vector<std::vector<int>>& map, int cornerPosition, int cornerLenght);
	void SetLeftVerticalWall(std::vector<std::vector<int>>& map, int cornerPosition, int cornerLenght);
	void SetRightVerticalWall(std::vector<std::vector<int>>& map, int cornerPosition, int cornerLenght);

	Position playerPos;
	std::vector<std::vector<std::string>> renderedMap;

};