#include <iostream>
#include <conio.h>
#include "Map.h"
#include "Player.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Enum.h"
#include "GameManager.h"
#include <iomanip> 
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <cmath>
#include <windows.h>

#define MAP_SIZE 72
#define MOVE_STEP_SIZE 3
#define PATH_SIZE MOVE_STEP_SIZE * 2
const static string Void = "  ";
const static string Wall = "■";

int GetPlayerPoston(const vector<vector<int>>& playerMap)
{
	for (int i = 0; i < playerMap.size(); i++)
	{
		if (playerMap[i][1] == 2)
			return i;
	}
	return -1;
}

void DisplayBoard(vector<vector<string>> &str)
{
	for (auto vec : str)
	{
		for (auto iter : vec)
			cout << iter;
	}
}

void SetWallInBoard(vector<vector<string>>& str)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			str[i][j] = Wall;
		}
	}
}

void SetOutLine(vector<vector<string>>& str, int in_line)
{
	SetWallInBoard(str);

	// 각 모서리
	for (int i = 0; i < in_line; i++)
	{
		// 왼쪽 위
		str[i][i] = Void;
		// 오른쪽 아래
		str[MAP_SIZE - i - 1][MAP_SIZE - i - 1] = Void;
		// 왼쪽 아래
		str[MAP_SIZE - i - 1][i] = Void;
		// 오른쪽 위
		str[i][MAP_SIZE - i - 1] = Void;
	}

	// 전방 벽
	for (int i = in_line; i < MAP_SIZE - in_line; i++)
	{
		str[in_line][i] = Void;
		str[MAP_SIZE - in_line - 1][i] = Void;
		str[i][in_line] = Void;
		str[i][MAP_SIZE - in_line - 1] = Void;
	}
}


void SetLeftEdgeWall(vector<vector<string>>& board, int in_line, int num)
{
	int out_line = in_line + num;
	for (int i = in_line; i < out_line; i++)
	{
		if (i < 0 || i >= MAP_SIZE / 2 - 2)
			continue;
		board[i][i] = Wall;
		board[MAP_SIZE - i - 1][i] = Wall;
	}
}

void SetLeftHorizontalWall(vector<vector<string>>& board, int in_line, int num)
{
	int out_line = in_line + num + 2;
	for (int i = 0; i < num; i++)
	{
		if (in_line + i >= MAP_SIZE / 2)
			continue;
		if (in_line + num > MAP_SIZE / 2)
			continue;
		board[in_line + num][in_line + i] = Void;
		board[MAP_SIZE - in_line - num - 1][in_line + i] = Void;
	}
}

void SetLeftVerticalWall(vector<vector<string>>& board, int in_line, int num, bool isOutline)
{

	//왼쪽에서 코너까지의 벽
	if (in_line >= 0)
	{
		for (int i = in_line; i < MAP_SIZE - in_line ; i++)
			board[i][in_line] = Void;
	}
	 //코너에서 전방까지의 벽
	if (!isOutline)
		return;
	if (in_line + num >= 0)
	{
		for (int i = in_line + num; i < MAP_SIZE - in_line - num; i++)
			board[i][in_line + num] = Void;
	}
}

int GetNearestPlayerForward(const vector<vector<int>> &playerMap)
{
	int playerPos = GetPlayerPoston(playerMap);
	for (int i = playerPos; playerPos > 0; i--)
	{
		if (playerMap[i][1] == 1)
			return i;
	}
	return 0;
}



void SetStraight(vector<vector<string>>& displayBoard, vector<vector<int>> playerMap)
{
	int in_line = 0;
	for (int i = GetPlayerPoston(playerMap); i > 0; i--)
	{
		if (playerMap[i][1] != 1)
			in_line++;
	}
	in_line *= MOVE_STEP_SIZE;
	SetWallInBoard(displayBoard);

	// 전방 벽
	int forward = GetNearestPlayerForward(playerMap);
	for (int i = in_line; i < MAP_SIZE - in_line; i++)
	{
		// 상
		displayBoard[in_line][i] = Void;
		// 하
		displayBoard[MAP_SIZE - in_line - 1][i] = Void;
		// 좌
		if (playerMap[forward][0] == 0)
			displayBoard[i][in_line] = Void;
		// 우
		displayBoard[i][MAP_SIZE - in_line - 1] = Void;
	}

	// 왼쪽 모서리 선 모두 그리기
	for (int i = 0; i < in_line; i++)
	{
		displayBoard[i][i] = Void;
		displayBoard[MAP_SIZE - i - 1][i] = Void;
		displayBoard[MAP_SIZE - i - 1][MAP_SIZE - i - 1] = Void;
		displayBoard[i][MAP_SIZE - i - 1] = Void;
	}
}

int GetZeroSize(const vector<vector<int>>& playerMap, int st)
{
	int cnt = 1;
	for (int i = 1; i < playerMap.size(); i++)
	{
		if (playerMap[st - i][0] == 0)
			cnt++;
		else
			return cnt;
	}
}

// 왼쪽 코너가 벽과 붙어있지 않은상황
// in_line : 왼쪽위부터 전방 벽까지의 거리인듯?
void SetOutLineLeft(vector<vector<string>>& displayBoard, const vector<vector<int>>& playerMap)
{
	int playerPos = GetPlayerPoston(playerMap);
	for (int i = playerPos; i > 0; i--)
	{
		if (playerMap[i][1] == 1)
			break;
		if (playerMap[i][0] == 0)
		{
			int leftPathCnt = GetZeroSize(playerMap, i);
			SetLeftEdgeWall(displayBoard, (playerPos - i) * MOVE_STEP_SIZE, MOVE_STEP_SIZE * leftPathCnt);
			if (playerMap[i - leftPathCnt - 1][1] == 0)
				SetLeftVerticalWall(displayBoard, (playerPos - i) * MOVE_STEP_SIZE, MOVE_STEP_SIZE * leftPathCnt, true);
			else
				SetLeftVerticalWall(displayBoard, (playerPos - i) * MOVE_STEP_SIZE, MOVE_STEP_SIZE * leftPathCnt, false);
			SetLeftHorizontalWall(displayBoard, (playerPos - i) * MOVE_STEP_SIZE, MOVE_STEP_SIZE * leftPathCnt);

			i -= leftPathCnt;
		}

	}
}


void DisplayMap(vector<vector<int>> map) 
{
	for (auto nxt : map)
	{
		for (auto nxt1 : nxt)
		{
			cout << nxt1 << " ";
		}
		cout << "\n";
	}
}

void InitMap(vector<vector<int>> &map)
{
	for (int i = 0; i < map.size(); i++)
	{
		map[i].push_back(1);
		map[i].push_back(0);
		map[i].push_back(1);
	}
	map[0][0] = 1;
	map[0][1] = 1;
	map[1][0] = 1;
	map[1][1] = 1;
	map[2][0] = 0;
	map[3][0] = 0;
	map[8][0] = 0;
	map[9][0] = 0;
	map[map.size() - 1][1] = 1;
	map[map.size() - 2][1] = 1;
}

void InitDisplayMap(vector<vector<string>>& map)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
			map[i].push_back(Wall);
		map[i].push_back("\n");
	}
}

void SetDisplayMap(vector<vector<string>>& map, vector<vector<int>> playerMap)
{
	SetStraight(map, playerMap);
	SetOutLineLeft(map, playerMap);
}

int main()
{
	srand(time(NULL));
	// 모두 꽉채우기(전체가 벽)
	vector<vector<int>> map(20);
	InitMap(map);
	vector<vector<string>> displayMap(MAP_SIZE);
	InitDisplayMap(displayMap);

	int currPos = 12;
	map[currPos][1] = 2;
	DisplayMap(map);
	SetDisplayMap(displayMap, map);
	DisplayBoard(displayMap);
	while (1)
	{
		Sleep(30);
		cout << currPos << endl;
		char c = _getch();
		if (c == 'w')
		{
			if (map[currPos - 1][1] != 1 && currPos > 0)
			{
				map[currPos--][1] = 0;
				map[currPos][1] = 2;
			}

		}
		if (c == 's')
		{
			if (map[currPos + 1][1] != 1)
			{
				map[currPos++][1] = 0;
				map[currPos][1] = 2;
			}
		}
		if (c == 'q')
			exit(0);
		
		system("cls");
		SetDisplayMap(displayMap, map);
		DisplayMap(map);

		DisplayBoard(displayMap);
	}
	//GameManager::GetInstance().GameStart();
}
