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

	void Rendering() const;
	void ApplyMap(vector<vector<int>> &map);
	void SetStraight(vector<vector<int>> &map);
	void SetOutLine(vector<vector<int>>& map);
	int GetNearestPlayerForward(vector<vector<int>>& map);
	void SetWallInBoard(vector<vector<string>>& map);
	void SetLeftEdgeWall(int in_line, int num);
	void SetRightEdgeWall(int in_line, int num);
	void SetLeftHorizontalWall(vector<vector<int>>& map, int in_line, int num);
	void SetRightHorizontalWall(vector<vector<int>>& map, int in_line, int num);
	void SetLeftVerticalWall(vector<vector<int>>& map, int in_line, int num);
	void SetRightVerticalWall(vector<vector<int>>& map, int in_line, int num);
	int GetZeroSize(vector<vector<int>>& map, int st, int dir);
	void ChangeLeftDirection(vector<vector<int>>& map);
	void ChangeRightDirection(vector<vector<int>>& map);
	void UpdatePlayerPosition(vector<vector<int>>& map);
	int playerX;
	int playerY;
	vector<vector<string>> renderedMap;
private:
	void InitDisplayMap();

};

