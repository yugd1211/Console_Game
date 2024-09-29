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
#include <windows.h>

#define MAP_SIZE 72
#define MOVE_STEP_SIZE 3
#define PATH_SIZE MOVE_STEP_SIZE * 2
const static string Void = "  ";
const static string Wall = "■";

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

void SetOutLineLeft(vector<vector<string>>& displayBoard, int in_line, int num, const vector<vector<int>>& playerMap)
{
	in_line *= MOVE_STEP_SIZE;
	SetWallInBoard(displayBoard);
	// 각 모서리
	for (int i = 0; i < in_line; i++)
	{
		if (i < in_line - num || i >= in_line + num)
		{
			displayBoard[i][i] = Void;
			displayBoard[MAP_SIZE - i - 1][i] = Void;
		}
		displayBoard[MAP_SIZE - i - 1][MAP_SIZE - i - 1] = Void;
		displayBoard[i][MAP_SIZE - i - 1] = Void;
	}

	// 왼쪽 벽
	if (in_line - num >= 0)
	{
		for (int i = in_line - num; i < MAP_SIZE - in_line + num; i++)
		{
			displayBoard[i][in_line - num] = Void;
		}
	}

	// 전방 벽
	for (int i = in_line; i < MAP_SIZE - in_line; i++)
	{
		displayBoard[in_line][i] = Void;
		displayBoard[MAP_SIZE - in_line - 1][i] = Void;
		displayBoard[i][in_line] = Void;
		displayBoard[i][MAP_SIZE - in_line - 1] = Void;
	}
	bool isWall = false;

	// 해당 길로 갈때 (벽과 길이 닿아있을때)
	if (isWall)
	{
		for (int i = in_line + 1; i < MAP_SIZE - in_line - 1; i++)
			displayBoard[i][in_line] = Wall;

		for (int i = 1; i <= num; i++)
		{
			if (in_line - i == 38)
			{
				displayBoard[in_line - 4][in_line - 5] = "  ";
				displayBoard[in_line - 3][in_line - 5] = "  ";
			}
			if (in_line - i > MAP_SIZE / 2)
				break;
			displayBoard[in_line][in_line - i] = Void;
			displayBoard[MAP_SIZE - in_line - 1][in_line - i] = Void;
		}
	}
	else
	{
		// 전방 벽과 왼쪽 통로간의 가름선을 지움
		//for (int i = in_line + 1; i < MAP_SIZE - in_line - 1; i++)
		//	displayBoard[i][in_line] = Wall;

		for (int i = 1; i <= num; i++)
		{
			if (in_line - i < 0)
				continue;
			// 디테일 살리기용 엄청 멀어졌을때 전방벽과, 왼쪽 벽을 이어주는 가로 선
			if (in_line - i == MAP_SIZE / 2 + 2)
			{
				displayBoard[in_line - 4][in_line - 5] = "  ";
				displayBoard[in_line - 3][in_line - 5] = "  ";
			}
			if (in_line - i > MAP_SIZE / 2)
				break;
			// 전방 벽에서 왼쪽 통로로 이어지는 것처럼보이게하는 가로 선들
			displayBoard[in_line][in_line - i] = Void;
			displayBoard[MAP_SIZE - in_line - 1][in_line - i] = Void;
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

int main()
{
	srand(time(NULL));
	// 모두 꽉채우기(전체가 벽)
	vector<vector<int>> map(18);
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
	map[map.size() - 1][1] = 1;
	map[map.size() - 2][1] = 1;
	vector<vector<string>> displayMap(MAP_SIZE);
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
			displayMap[i].push_back(Wall);
		displayMap[i].push_back("\n");
	}
	int currPos = 4;
	map[currPos][1] = 2;
	DisplayMap(map);
	SetOutLineLeft(displayMap, currPos, PATH_SIZE, map);
	//SetOutLine(displayMap, currPos * 2);
	DisplayBoard(displayMap);
	while (1)
	{
		Sleep(50);
		cout << currPos << endl;
		char c = _getch();
		if (c == 'w')
		{
			// SetOutLineLeft 에서 2 이하로 내려가면 에러
			// 해당 구역은 반드시 벽이긴함
			// 2로 잡은 이유는 랜덤배열 설정하고, 이를 두배로 복사 해야함
			// 움직임을 더 표현할 수 있음(한번에 점프하는게 아니라 천천히 움직이게끔)
			cout << currPos << "\n";
			if (/*map[currPos - 1][1] != 1 && */currPos > 1)
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
		DisplayMap(map);
		// 앞 뒤만 뚫려있음
		SetOutLineLeft(displayMap, currPos, PATH_SIZE, map);
		//SetOutLine(displayMap, currPos * 2);
		DisplayBoard(displayMap);
	}
	//GameManager::GetInstance().GameStart();
}
