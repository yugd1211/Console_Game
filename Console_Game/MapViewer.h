#pragma once
#include <vector>
#include <iostream>
using namespace std;
class MapViewer
{
public:
	MapViewer(int x, int y) : playerX(x), playerY(y) {}

	void DisplayMap(const vector<vector<int>>& map) const;
	void Rendering() const;
	void SetRenderedMap(const vector<vector<string>>& map);
	void Transformation(const vector<vector<int>>& map);
	void SetDisplayMap(const vector<vector<int>> &playerMap);
	void SetStraight(const vector<vector<int>> &playerMap);
	void SetOutLine(const vector<vector<int>>& playerMap);
	int GetNearestPlayerForward(const vector<vector<int>>& playerMap);
	void SetWallInBoard(vector<vector<string>>& str);
	void SetLeftEdgeWall(vector<vector<string>>& board, int in_line, int num);
	void SetRightEdgeWall(vector<vector<string>>& board, int in_line, int num);
	void SetLeftHorizontalWall(const vector<vector<int>>& playerMap, int in_line, int num);
	void SetRightHorizontalWall(const vector<vector<int>>& playerMap, int in_line, int num);
	void SetLeftVerticalWall(const vector<vector<int>>& playerMap, int in_line, int num);
	void SetRightVerticalWall(const vector<vector<int>>& playerMap, int in_line, int num);
	int GetZeroSize(const vector<vector<int>>& playerMap, int st, int dir);
private:
	vector<vector<string>> renderedMap;
	int playerX;
	int playerY;
};

