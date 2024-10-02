#include "MapViewer.h"

MapViewer::MapViewer(int x, int y) : playerX(x), playerY(y)
{
	renderedMap = vector<vector<string>>(MAP_SIZE);
	InitDisplayMap();
}

MapViewer::MapViewer(Position pos) :playerX(pos.x), playerY(pos.y)
{
	renderedMap = vector<vector<string>>(MAP_SIZE);
	InitDisplayMap();
}

void MapViewer::Rendering() const
{
	for (auto vec : renderedMap)
	{
		for (auto iter : vec)
			cout << iter;
	}
	cout << endl;
}

void MapViewer::ApplyMap(vector<vector<int>>& map)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == MAP_ELEMENT::PLAYER)
			{
				playerX = i;
				playerY = j;
			}
		}
	}
	SetStraight(map);
	SetOutLine(map);
}

void MapViewer::SetStraight(vector<vector<int>>& map)
{
	SetWallInBoard(renderedMap);
	// 전방 벽
	int forward = GetNearestPlayerForward(map);
	int in_line = (playerX - forward) * FIXEL_SIZE;
	for (int i = in_line; i < MAP_SIZE - in_line; i++)
	{
		// 상
		renderedMap[in_line][i] = Void;
		// 하
		renderedMap[MAP_SIZE - in_line - 1][i] = Void;
		// 좌
		if (map[forward + 1][playerY - 1] == MAP_ELEMENT::WALL)
			renderedMap[i][in_line] = Void;
		// 우
		if (map[forward + 1][playerY + 1] == MAP_ELEMENT::WALL)
			renderedMap[i][MAP_SIZE - in_line - 1] = Void;
	}
	////모서리 선 모두 그리기
	for (int i = 0; i < in_line; i++)
	{
		if (map[forward + 1][playerY - 1] == MAP_ELEMENT::WALL)
		{
			renderedMap[i][i] = Void;
			renderedMap[MAP_SIZE - i - 1][i] = Void;
		}
	}

	// 플레이어 위치부터 시작하는 방식으로 재설계
	// 플레이어 위치에서 정면의 벽을 만날때 까지
	for (int i = playerX; i > forward; i--)
	{
		//벽이 있는 특정 부분만 채우기
		if (map[i][playerY - 1] == MAP_ELEMENT::WALL)
		{
			for (int j = 0; j < FIXEL_SIZE; j++)
			{
				renderedMap[MAP_SIZE - (((playerX - i) * FIXEL_SIZE) + j) - 1][((playerX - i) * FIXEL_SIZE) + j] = Void;
				renderedMap[((playerX - i) * FIXEL_SIZE) + j][((playerX - i) * FIXEL_SIZE) + j] = Void;
			}
		}
	}


	//플레이어 위치부터 시작하는 방식으로 재설계
	for (int i = playerX; i > forward; i--)
	{
		if (map[i][playerY + 1] == MAP_ELEMENT::WALL)
		{
			for (int j = 0; j < FIXEL_SIZE; j++)
			{
				renderedMap[((playerX - i) * FIXEL_SIZE) + j][MAP_SIZE - (((playerX - i) * FIXEL_SIZE) + j) - 1] = Void;
				renderedMap[MAP_SIZE - (((playerX - i) * FIXEL_SIZE) + j) - 1][MAP_SIZE - (((playerX - i) * FIXEL_SIZE) + j) - 1] = Void;
			}
		}
	}
	for (int i = playerX; i > forward; i--)
	{
		if (map[i][playerY] == MAP_ELEMENT::EXIT)
		{
			// 72 / 3 / 2 = 12
			for (int i = 0; i < (MAP_SIZE / FIXEL_SIZE / 2) - (playerX - forward); i++)
			{
				for (int j = 0; j < (MAP_SIZE / FIXEL_SIZE / 2) - (playerX - forward); j+=2)
				{
					renderedMap[MAP_SIZE / 2 + i][MAP_SIZE / 2 + j - (playerX - forward)] = "EX";
					renderedMap[MAP_SIZE / 2 + i][MAP_SIZE / 2 + 1 + j - (playerX - forward)] = "IT";
					renderedMap[MAP_SIZE / 2 - i][MAP_SIZE / 2 + j - (playerX - forward)] = "EX";
					renderedMap[MAP_SIZE / 2 - i][MAP_SIZE / 2 + 1 + j - (playerX - forward)] = "IT";
				}
				for (int j = (MAP_SIZE / FIXEL_SIZE / 2) - (playerX - forward); j > 0; j -= 2)
				{
					renderedMap[MAP_SIZE / 2 + i][MAP_SIZE / 2 + j] = "EX";
					renderedMap[MAP_SIZE / 2 + i][MAP_SIZE / 2 + 1 + j] = "IT";
					renderedMap[MAP_SIZE / 2 - i][MAP_SIZE / 2 + j] = "EX";
					renderedMap[MAP_SIZE / 2 - i][MAP_SIZE / 2 + 1 + j] = "IT";
				}

			}
		}
	}

}

int MapViewer::GetNearestPlayerForward(vector<vector<int>>& map)
{
	for (int i = playerX; playerX > 0; i--)
	{
		if (map[i][playerY] == MAP_ELEMENT::WALL)
			return i;
	}
	return 0;
}

void MapViewer::SetWallInBoard(vector<vector<string>>& map)
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			renderedMap[i][j] = Wall;
		}
	}
}

void MapViewer::SetLeftEdgeWall(int in_line, int num)
{
	int out_line = in_line + num;
	for (int i = in_line; i < out_line; i++)
	{
		if (i < 0 || i >= MAP_SIZE / 2 - 1)
			continue;
		renderedMap[i][i] = Wall;
		renderedMap[MAP_SIZE - i - 1][i] = Wall;
	}
}

void MapViewer::SetRightEdgeWall(int in_line, int num)
{
	int out_line = in_line - num;

	for (int i = in_line; i > out_line; i--)
	{
		if (i < MAP_SIZE / 2 || i >= MAP_SIZE)
			continue;
		renderedMap[i][i] = Wall;
		renderedMap[MAP_SIZE - i - 1][i] = Wall;
	}
}

void MapViewer::SetLeftHorizontalWall(vector<vector<int>>& map, int in_line, int num)
{
	int playerFor = GetNearestPlayerForward(map);

	if ((playerX - playerFor) * FIXEL_SIZE < in_line)
		return;
	if (in_line + num > MAP_SIZE / 2)
	{
		//아직버그있음 시간 남으면 고칠것
		//int n = in_line + num - MAP_SIZE / 2;
		//in_line -= n;
		return;
	}
	for (int i = 0; i < num; i++)
	{
		renderedMap[in_line + num][in_line + i] = Void;
		renderedMap[MAP_SIZE - 1 - (in_line + num)][in_line + i] = Void;
	}

}

void MapViewer::SetRightHorizontalWall(vector<vector<int>>& map, int in_line, int num)
{
	int playerFor = GetNearestPlayerForward(map);

	if (MAP_SIZE - (playerX - playerFor) * FIXEL_SIZE > in_line)
		return;
	if (in_line - num < MAP_SIZE / 2)
	{
		//int n = MAP_SIZE / 2 - in_line - num;
		//in_line += n;
		return;
	}
	for (int i = 0; i < num; i++)
	{
		renderedMap[in_line - num][in_line - i] = Void;
		renderedMap[MAP_SIZE - 1 - (in_line - num)][in_line - i] = Void;
	}
}

void MapViewer::SetLeftVerticalWall(vector<vector<int>>& map, int in_line, int num)
{
	int playerFor = GetNearestPlayerForward(map);
	for (int i = in_line; i < MAP_SIZE - in_line; i++)
	{
		if (in_line - 1 > ((playerX - playerFor) * FIXEL_SIZE))
			continue;
		renderedMap[i][in_line] = Void;
	}

	int out_line = in_line + num;
	if ((playerX - playerFor) * FIXEL_SIZE <= in_line + num)
		return;
	for (int i = out_line; i < MAP_SIZE - out_line; i++)
	{
		if (in_line - 1 > ((playerX - playerFor) * FIXEL_SIZE))
			continue;
		renderedMap[i][out_line] = Void;
	}
}

void MapViewer::SetRightVerticalWall(vector<vector<int>>& map, int in_line, int num)
{
	int playerFor = GetNearestPlayerForward(map);
	//오른쪽에서 코너까지의 벽
	for (int i = MAP_SIZE - in_line - 1; i <= in_line; i++)
	{
		if (in_line < MAP_SIZE - ((playerX - playerFor) * FIXEL_SIZE))
			continue;
		//if (i >= 0 && i <= MAP_SIZE && in_line >= MAP_SIZE / 2 - 2)
		renderedMap[i][in_line] = Void;
	}
	//코너에서 전방까지의 벽
	int out_line = in_line - num;
	for (int i = MAP_SIZE - out_line - 1; i <= out_line; i++)
	{
		if (out_line < MAP_SIZE - ((playerX - playerFor) * FIXEL_SIZE))
			continue;
		//if (i >= 0 && i < MAP_SIZE && out_line >= MAP_SIZE / 2 - 2)
		renderedMap[i][out_line] = Void;
	}
}

int MapViewer::GetZeroSize(vector<vector<int>>& map, int st, int dir)
{
	int cnt = 0;
	for (int i = st; i > 0; i--)
	{
		if (map[i][playerY] == MAP_ELEMENT::WALL)
			break;
		if (map[i][playerY + dir] == MAP_ELEMENT::WALL)
			break;
		cnt++;
	}
	return cnt;
}

void MapViewer::SetOutLine(vector<vector<int>>& map)
{
	int playerFor = GetNearestPlayerForward(map);
	for (int i = playerX; i > 0; i--)
	{
		if (map[i][playerY] == MAP_ELEMENT::WALL)
			break;
		if (map[i][playerY - 1] == MAP_ELEMENT::VOID)
		{
			int leftPathCnt = GetZeroSize(map, i, -1);
			SetLeftEdgeWall((playerX - i) * FIXEL_SIZE, FIXEL_SIZE * leftPathCnt);
			SetLeftVerticalWall(map, (playerX - i) * FIXEL_SIZE, FIXEL_SIZE * leftPathCnt);
			SetLeftHorizontalWall(map, (playerX - i) * FIXEL_SIZE, FIXEL_SIZE * leftPathCnt);

			i -= leftPathCnt;
		}
	}

	for (int i = playerX; i > 0; i--)
	{
		if (map[i][playerY] == MAP_ELEMENT::WALL)
			break;
		if (map[i][playerY + 1] == MAP_ELEMENT::VOID)
		{

			int rightPathCnt = GetZeroSize(map, i, 1);
			SetRightEdgeWall((MAP_SIZE - 1) - (playerX - i) * FIXEL_SIZE, FIXEL_SIZE * rightPathCnt);
			SetRightVerticalWall(map, (MAP_SIZE - 1) - (playerX - i) * FIXEL_SIZE, FIXEL_SIZE * rightPathCnt);
			SetRightHorizontalWall(map, (MAP_SIZE - 1) - (playerX - i) * FIXEL_SIZE, FIXEL_SIZE * rightPathCnt);

			i -= rightPathCnt;
		}
	}
}

void MapViewer::ChangeLeftDirection(vector<vector<int>>& map)
{
	for (int i = 0; i < map.size() - 1; i++)
		for (int j = 0; j < i; j++)
			swap(map[i][j], map[j][i]);

	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map.size() / 2; j++)
			swap(map[i][j], map[i][map.size() - 1 - j]);
	UpdatePlayerPosition(map);
}

void MapViewer::ChangeRightDirection(vector<vector<int>>& map)
{
	for (int i = 0; i < map.size() - 1; i++)
		for (int j = 0; j < map.size() - i - 1; j++)
			swap(map[i][j], map[map.size() - j - 1][map.size() - i - 1]);

	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map.size() / 2; j++)
			swap(map[i][j], map[i][map.size() - j - 1]);

	UpdatePlayerPosition(map);
}

void MapViewer::UpdatePlayerPosition(vector<vector<int>>& map)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map.size(); j++)
		{
			if (map[i][j] == 2)
			{
				playerX = i;
				playerY = j;
				return;
			}
		}
	}
}

void MapViewer::InitDisplayMap()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
			renderedMap[i].push_back(Wall);
		renderedMap[i].push_back("\n");
	}
}
