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

int g_player_x;
int g_player_y;

int GetPlayerPoston(const vector<vector<int>>& playerMap)
{
	for (int i = 0; i < playerMap.size(); i++)
	{
		if (playerMap[i][g_player_y] == 2)
			return i;
	}
	return -1;
}

void DisplayBoard(vector<vector<string>>& str)
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

int GetNearestPlayerForward(const vector<vector<int>>& playerMap)
{
	for (int i = g_player_x; g_player_x > 0; i--)
	{
		if (playerMap[i][g_player_y] == 1)
			return i;
	}
	return 0;
}
void SetLeftEdgeWall(vector<vector<string>>& board, int in_line, int num)
{
	int out_line = in_line + num;
	for (int i = in_line; i < out_line; i++)
	{
		if (i < 0 || i >= MAP_SIZE / 2 - 1)
			continue;
		board[i][i] = Wall;
		board[MAP_SIZE - i - 1][i] = Wall;
	}
}

void SetRightEdgeWall(vector<vector<string>>& board, int in_line, int num)
{
	int out_line = in_line - num;

	for (int i = in_line; i > out_line; i--)
	{
		if (i < MAP_SIZE / 2 || i >= MAP_SIZE)
			continue;
		board[i][i] = Wall;
		board[MAP_SIZE - i - 1][i] = Wall;
	}
}

void SetLeftHorizontalWall(vector<vector<string>>& board, const vector<vector<int>>& playerMap, int in_line, int num)
{
	int playerFor = GetNearestPlayerForward(playerMap);
	//cout << "SetLeftVerticalWall st\n";
	//cout << "inline = " << in_line << ", num = " << num << "\n";
	//cout << "playerFor = " << playerFor << "\n";
	//cout << "(g_player_x - playerFor) * MOVE_STEP_SIZE = " << (g_player_x - playerFor) * MOVE_STEP_SIZE << "\n";
	//cout << "num = " << num << "\n";
	//cout << "SetLeftVerticalWall en\n\n";

	if ((g_player_x - playerFor) * MOVE_STEP_SIZE < in_line)
		return;
	for (int i = 0; i < num; i++)
	{
		board[in_line + num][in_line + i] = Void;
		board[MAP_SIZE - 1 - (in_line + num)][in_line + i] = Void;
	}

}

void SetRightHorizontalWall(vector<vector<string>>& board, const vector<vector<int>>& playerMap, int in_line, int num)
{
	int playerFor = GetNearestPlayerForward(playerMap);

	if (MAP_SIZE - (g_player_x - playerFor) * MOVE_STEP_SIZE > in_line)
		return;
	for (int i = 0; i < num; i++)
	{
		board[in_line - num][in_line - i] = Void;
		board[MAP_SIZE - 1 - (in_line - num)][in_line - i] = Void;
	}
}

void SetLeftVerticalWall(vector<vector<string>>& board, const vector<vector<int>>& playerMap, int in_line, int num)
{
	int playerFor = GetNearestPlayerForward(playerMap);
	for (int i = in_line; i < MAP_SIZE - in_line; i++)
	{
		if (in_line - 1 > ((g_player_x - playerFor) * MOVE_STEP_SIZE))
			continue;
		board[i][in_line] = Void;
	}

	int out_line = in_line + num;
	if ((g_player_x - playerFor) * MOVE_STEP_SIZE <= in_line + num)
		return;
	for (int i = out_line; i < MAP_SIZE - out_line; i++)
	{
		if (in_line - 1 > ((g_player_x - playerFor) * MOVE_STEP_SIZE))
			continue;
		board[i][out_line] = Void;
	}

}

void SetRightVerticalWall(vector<vector<string>>& board, const vector<vector<int>>& playerMap, int in_line, int num)
{
	int playerFor = GetNearestPlayerForward(playerMap);
	//오른쪽에서 코너까지의 벽
	for (int i = MAP_SIZE - in_line; i < in_line; i++)
	{
		if (in_line - 1 < MAP_SIZE - ((g_player_x - playerFor) * MOVE_STEP_SIZE))
			continue;
		//if (i >= 0 && i <= MAP_SIZE && in_line >= MAP_SIZE / 2 - 2)
		board[i][in_line - 1] = Void;
	}
	//코너에서 전방까지의 벽
	int out_line = in_line - num - 1;
	for (int i = MAP_SIZE - in_line + num; i <= out_line; i++)
	{
		if (out_line < MAP_SIZE - ((g_player_x - playerFor) * MOVE_STEP_SIZE))
			continue;
		//if (i >= 0 && i < MAP_SIZE && out_line >= MAP_SIZE / 2 - 2)
		board[i][out_line] = Void;
	}
}



void SetStraight(vector<vector<string>>& displayBoard, vector<vector<int>> playerMap)
{
	SetWallInBoard(displayBoard);
	// 전방 벽
	int forward = GetNearestPlayerForward(playerMap);
	int in_line = (g_player_x - forward) * MOVE_STEP_SIZE;
	for (int i = in_line; i < MAP_SIZE - in_line; i++)
	{
		// 상
		displayBoard[in_line][i] = Void;
		// 하
		displayBoard[MAP_SIZE - in_line - 1][i] = Void;
		// 좌
		if (playerMap[forward + 1][g_player_y - 1] == 1)
			displayBoard[i][in_line] = Void;
		// 우
		if (playerMap[forward + 1][g_player_y + 1] == 1)
			displayBoard[i][MAP_SIZE - in_line - 1] = Void;
	}

	////모서리 선 모두 그리기
	for (int i = 0; i < in_line; i++)
	{
		if (playerMap[forward + 1][g_player_y - 1] == 1)
		{
			displayBoard[i][i] = Void;
			displayBoard[MAP_SIZE - i - 1][i] = Void;
		}
		//if (playerMap[forward + 1][g_player_y + 1] == 1)
		//{
			//displayBoard[i][MAP_SIZE - i - 1] = Void;
			//displayBoard[MAP_SIZE - i - 1][MAP_SIZE - i - 1] = Void;
		//}
	}

	// 플레이어 위치부터 시작하는 방식으로 재설계
	// 플레이어 위치에서 정면의 벽을 만날때 까지
	for (int i = g_player_x; i > forward; i--)
	{
		//벽이 있는 특정 부분만 채우기
		if (playerMap[i][g_player_y - 1] == 1)
		{
			for (int j = 0; j < MOVE_STEP_SIZE; j++)
			{
				displayBoard[MAP_SIZE - (((g_player_x - i) * MOVE_STEP_SIZE) + j) - 1][((g_player_x - i) * MOVE_STEP_SIZE) + j] = Void;
				displayBoard[((g_player_x - i) * MOVE_STEP_SIZE) + j][((g_player_x - i) * MOVE_STEP_SIZE) + j] = Void;
			}
		}
	}


	//플레이어 위치부터 시작하는 방식으로 재설계
	for (int i = g_player_x; i > forward; i--)
	{
		if (playerMap[i][g_player_y + 1] == 1)
		{
			for (int j = 0; j < MOVE_STEP_SIZE; j++)
			{
				displayBoard[((g_player_x - i) * MOVE_STEP_SIZE) + j][MAP_SIZE - (((g_player_x - i) * MOVE_STEP_SIZE) + j) - 1] = Void;
				displayBoard[MAP_SIZE - (((g_player_x - i) * MOVE_STEP_SIZE) + j) - 1][MAP_SIZE - (((g_player_x - i) * MOVE_STEP_SIZE) + j) - 1] = Void;
			}
		}
	}
}

int GetZeroSize(const vector<vector<int>>& playerMap, int st, int dir)
{
	int cnt = 0;
	for (int i = st; i > 0; i--)
	{
		if (playerMap[i][g_player_y] == 1)
			break;
		if (playerMap[i][g_player_y + dir] == 1)
			break;
		cnt++;
	}
	return cnt;
}

// 왼쪽 코너가 벽과 붙어있지 않은상황
// in_line : 왼쪽위부터 전방 벽까지의 거리인듯
void SetOutLine(vector<vector<string>>& displayBoard, const vector<vector<int>>& playerMap)
{
	int playerFor = GetNearestPlayerForward(playerMap);
	for (int i = g_player_x; i > 0; i--)
	{
		if (playerMap[i][g_player_y] == 1)
			break;
		if (playerMap[i][g_player_y - 1] == 0)
		{
			int leftPathCnt = GetZeroSize(playerMap, i, -1);
			SetLeftEdgeWall(displayBoard, (g_player_x - i) * MOVE_STEP_SIZE, MOVE_STEP_SIZE * leftPathCnt);
			SetLeftVerticalWall(displayBoard, playerMap, (g_player_x - i) * MOVE_STEP_SIZE, MOVE_STEP_SIZE * leftPathCnt);
			SetLeftHorizontalWall(displayBoard, playerMap, (g_player_x - i) * MOVE_STEP_SIZE, MOVE_STEP_SIZE * leftPathCnt);

			i -= leftPathCnt;
		}
	}

	for (int i = g_player_x; i > 0; i--)
	{
		if (playerMap[i][g_player_y] == 1)
			break;
		if (playerMap[i][g_player_y + 1] == 0)
		{

			int rightPathCnt = GetZeroSize(playerMap, i, 1);
			cout << "rightPathCnt = " << rightPathCnt << "\n";
			SetRightEdgeWall(displayBoard, (MAP_SIZE - 1) - (g_player_x - i) * MOVE_STEP_SIZE, MOVE_STEP_SIZE * rightPathCnt);
			SetRightVerticalWall(displayBoard, playerMap, (MAP_SIZE)-(g_player_x - i) * MOVE_STEP_SIZE, MOVE_STEP_SIZE * rightPathCnt);
			SetRightHorizontalWall(displayBoard, playerMap, (MAP_SIZE - 1) - (g_player_x - i) * MOVE_STEP_SIZE, MOVE_STEP_SIZE * rightPathCnt);

			i -= rightPathCnt;
		}
	}
}


void DisplayMap(vector<vector<int>> map)
{
	for (auto nxt : map)
	{
		for (auto nxt1 : nxt)
		{
			if (nxt1 == 1)
				cout << "■";
			else if (nxt1 == 2)
				cout << "★";
			else if (nxt1 == 0)
				cout << "  ";
		}
		cout << "\n";
	}
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
	SetOutLine(map, playerMap);
}


void InitMap(vector<vector<int>>& board, int size)
{
	board = vector<vector<int>>(size);
	for (int i = 0; i < board.size(); i++)
		board[i] = vector<int>(size);

	//for (int i = 0; i < size; i++)
	//{
	//	board[0][i] = 1;
	//	board[i][0] = 1;
	//	board[size - 1][i] = 1;
	//	board[i][size - 1] = 1;
	//}
	//for (int i = 1; i < size - 1; i++)
	//{
	//	for (int j = 1; j < size - 1; j++)
	//	{
	//		if (board[i][j] != 0)
	//			continue;
	//		board[i][j] = rand() % 6 >= 4 ? 1 : 0;
	//	}
	//}
}

void UpdatePlayerPosition(vector<vector<int>>& map)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map.size(); j++)
		{
			if (map[i][j] == 2)
			{
				g_player_x = i;
				g_player_y = j;
				return;
			}

		}
	}
}

void ChangeLeftDirection(vector<vector<int>>& map)
{
	for (int i = 0; i < map.size() - 1; i++)
		for (int j = 0; j < i; j++)
			swap(map[i][j], map[j][i]);

	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map.size() / 2; j++)
			swap(map[i][j], map[i][map.size() - 1 - j]);
	UpdatePlayerPosition(map);
}

void ChangeRightDirection(vector<vector<int>>& map)
{
	for (int i = 0; i < map.size() - 1; i++)
		for (int j = 0; j < map.size() - i - 1; j++)
			swap(map[i][j], map[map.size() - j - 1][map.size() - i - 1]);

	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map.size() / 2; j++)
			swap(map[i][j], map[i][map.size() - j - 1]);


	UpdatePlayerPosition(map);
}

int main()
{
	srand(time(NULL));
	vector<vector<int>> map = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 1, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 1, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};
	//vector<vector<int>> map = {
	//	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	//	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	//};
	//vector<vector<int>> map;
	//InitMap(map, 10);
	vector<vector<string>> displayMap(MAP_SIZE);
	InitDisplayMap(displayMap);
	g_player_x = 1;
	g_player_y = 1;
	map[g_player_x][g_player_y] = 2;
	DisplayMap(map);
	SetDisplayMap(displayMap, map);
	DisplayBoard(displayMap);
	while (1)
	{
		Sleep(30);
		cout << g_player_x << endl;
		char c = _getch();
		if (c == 'q')
		{
			ChangeLeftDirection(map);
		}
		if (c == 'e')
		{
			ChangeRightDirection(map);
		}
		if (c == 'w')
		{
			if (map[g_player_x - 1][g_player_y] != 1 && g_player_x > 0)
			{
				map[g_player_x--][g_player_y] = 0;
				map[g_player_x][g_player_y] = 2;
			}

		}
		if (c == 's')
		{
			if (map[g_player_x + 1][g_player_y] != 1)
			{
				map[g_player_x++][g_player_y] = 0;
				map[g_player_x][g_player_y] = 2;
			}
		}
		if (c == 'a')
		{
			if (map[g_player_x][g_player_y - 1] != 1)
			{
				map[g_player_x][g_player_y--] = 0;
				map[g_player_x][g_player_y] = 2;
			}
		}
		if (c == 'd')
		{
			if (map[g_player_x][g_player_y + 1] != 1)
			{
				map[g_player_x][g_player_y++] = 0;
				map[g_player_x][g_player_y] = 2;
			}
		}
		if (c == 'z')
			exit(0);

		system("cls");
		SetDisplayMap(displayMap, map);
		DisplayMap(map);

		DisplayBoard(displayMap);
	}
	//GameManager::GetInstance().GameStart();
}
