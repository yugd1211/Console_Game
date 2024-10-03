#pragma once
#include <vector>
#include <iostream>
#include "Position.h"
#include "Enum.h"
using namespace std;

const static string Void = "  ";
const static string Wall = "бс";

class MapViewer
{
public:

	MapViewer(int x, int y);
	MapViewer(Position pos);

	void Display() const;
	void Rendering(vector<vector<int>> &map);

private:

	void InitDisplayMap();
	void SetStraight(vector<vector<int>>& map);
	void SetCornerBoundary(vector<vector<int>>& map);
	int GetNearestPlayerForward(vector<vector<int>>& map);
	int GetPathLength(vector<vector<int>>& map, int st, int dir);
	void SetLeftEdgeWall(int cornerPosition, int cornerLenght);
	void SetRightEdgeWall(int cornerPosition, int cornerLenght);
	void SetLeftHorizontalWall(vector<vector<int>>& map, int cornerPosition, int cornerLenght);
	void SetRightHorizontalWall(vector<vector<int>>& map, int cornerPosition, int cornerLenght);
	void SetLeftVerticalWall(vector<vector<int>>& map, int cornerPosition, int cornerLenght);
	void SetRightVerticalWall(vector<vector<int>>& map, int cornerPosition, int cornerLenght);

	Position playerPos;
	vector<vector<string>> renderedMap;

};