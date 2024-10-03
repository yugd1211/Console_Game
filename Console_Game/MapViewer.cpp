#include "MapViewer.h"
#include "BufferManager.h"

using namespace std;

MapViewer::MapViewer(int x, int y) : playerPos(x, y)
{
	renderedMap = vector<vector<string>>(WINDOW_SIZE);
	InitDisplayMap();
}

MapViewer::MapViewer(Position pos) : playerPos(pos)
{
	renderedMap = vector<vector<string>>(WINDOW_SIZE);
	InitDisplayMap();
}

void MapViewer::Display() const
{
	for (auto vec : renderedMap)
	{
		for (auto iter : vec)
			BufferManager::GetInstance().AddToBuffer(iter);
	}
	BufferManager::GetInstance().AddToBuffer("\n");
}

void MapViewer::Rendering(vector<vector<int>>& map)
{
	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map[i].size(); j++)
			if (map[i][j] == MAP_ELEMENT::PLAYER)
				playerPos = Position(i, j);

	for (int i = 0; i < WINDOW_SIZE; i++)
		for (int j = 0; j < WINDOW_SIZE; j++)
			renderedMap[i][j] = PRINT_WALL;
	SetStraight(map);
	SetCornerBoundary(map);
}



void MapViewer::InitDisplayMap()
{
	for (int i = 0; i < WINDOW_SIZE; i++)
	{
		for (int j = 0; j < WINDOW_SIZE; j++)
			renderedMap[i].push_back(Wall);
		renderedMap[i].push_back("\n");
	}
}

void MapViewer::SetStraight(vector<vector<int>>& map)
{
	int forward = GetNearestPlayerForward(map);
	int cornerPosition = (playerPos.x - forward) * FIXEL_SIZE;

	// 전방 벽
	for (int i = cornerPosition; i < WINDOW_SIZE - cornerPosition; i++)
	{
		renderedMap[cornerPosition][i] = PRINT_VOID;
		renderedMap[WINDOW_SIZE - cornerPosition - 1][i] = PRINT_VOID;
		if (map[forward + 1][playerPos.y - 1] == MAP_ELEMENT::WALL)
			renderedMap[i][cornerPosition] = PRINT_VOID;
		if (map[forward + 1][playerPos.y + 1] == MAP_ELEMENT::WALL)
			renderedMap[i][WINDOW_SIZE - cornerPosition - 1] = PRINT_VOID;
	}


	// 좌측 모서리
	for (int i = playerPos.x; i > forward; i--)
	{
		//벽이 있는 특정 부분만 채우기
		if (map[i][playerPos.y - 1] == MAP_ELEMENT::WALL)
		{
			for (int j = 0; j < FIXEL_SIZE; j++)
			{
				renderedMap[WINDOW_SIZE - (((playerPos.x - i) * FIXEL_SIZE) + j) - 1][((playerPos.x - i) * FIXEL_SIZE) + j] = PRINT_VOID;
				renderedMap[((playerPos.x - i) * FIXEL_SIZE) + j][((playerPos.x - i) * FIXEL_SIZE) + j] = PRINT_VOID;
			}
		}
	}

	// 우측 모서리
	for (int i = playerPos.x; i > forward; i--)
	{
		if (map[i][playerPos.y + 1] == MAP_ELEMENT::WALL)
		{
			for (int j = 0; j < FIXEL_SIZE; j++)
			{
				renderedMap[((playerPos.x - i) * FIXEL_SIZE) + j][WINDOW_SIZE - (((playerPos.x - i) * FIXEL_SIZE) + j) - 1] = PRINT_VOID;
				renderedMap[WINDOW_SIZE - (((playerPos.x - i) * FIXEL_SIZE) + j) - 1][WINDOW_SIZE - (((playerPos.x - i) * FIXEL_SIZE) + j) - 1] = PRINT_VOID;
			}
		}
	}

	// 전방 EXIT
	for (int i = playerPos.x; i >= 0; i--)
	{
		if (map[i][playerPos.y] == MAP_ELEMENT::WALL)
			return;
		if (map[i][playerPos.y] == MAP_ELEMENT::EXIT)
		{
			cornerPosition = (playerPos.x + i) * FIXEL_SIZE;
			break;
		}
	}
	for (int i = 0; i < WINDOW_SIZE - (cornerPosition * 2); i++)
	{
		for (int j = cornerPosition; j < WINDOW_SIZE - cornerPosition - 1; j += 2)
		{
			renderedMap[cornerPosition + i][j] = "EX";
			renderedMap[cornerPosition + i][j + 1] = "IT";
		}
	}
}

int MapViewer::GetNearestPlayerForward(vector<vector<int>>& map)
{
	for (int i = playerPos.x; playerPos.x > 0; i--)
		if (map[i][playerPos.y] == MAP_ELEMENT::WALL)
			return i;
	return 0;
}


void MapViewer::SetLeftEdgeWall(int cornerPosition, int cornerLenght)
{
	int endPosition = cornerPosition + cornerLenght;
	for (int i = cornerPosition; i < endPosition; i++)
	{
		if (i < 0 || i >= WINDOW_SIZE / 2 - 1)
			continue;
		renderedMap[i][i] = PRINT_WALL;
		renderedMap[WINDOW_SIZE - i - 1][i] = PRINT_WALL;
	}
}

void MapViewer::SetRightEdgeWall(int cornerPosition, int cornerLenght)
{
	int endPosition = cornerPosition - cornerLenght;

	for (int i = cornerPosition; i > endPosition; i--)
	{
		if (i < WINDOW_SIZE / 2 || i >= WINDOW_SIZE)
			continue;
		renderedMap[i][i] = PRINT_WALL;
		renderedMap[WINDOW_SIZE - i - 1][i] = PRINT_WALL;
	}
}

void MapViewer::SetLeftHorizontalWall(vector<vector<int>>& map, int cornerPosition, int cornerLenght)
{
	int playerFor = GetNearestPlayerForward(map);

	if ((playerPos.x - playerFor) * FIXEL_SIZE < cornerPosition)
		return;
	if (cornerPosition + cornerLenght > WINDOW_SIZE / 2)
		return;
	for (int i = 0; i < cornerLenght; i++)
	{
		renderedMap[cornerPosition + cornerLenght][cornerPosition + i] = PRINT_VOID;
		renderedMap[WINDOW_SIZE - 1 - (cornerPosition + cornerLenght)][cornerPosition + i] = PRINT_VOID;
	}

}

void MapViewer::SetRightHorizontalWall(vector<vector<int>>& map, int cornerPosition, int cornerLenght)
{
	int playerFor = GetNearestPlayerForward(map);

	if (WINDOW_SIZE - (playerPos.x - playerFor) * FIXEL_SIZE > cornerPosition)
		return;
	if (cornerPosition - cornerLenght < WINDOW_SIZE / 2)
		return;
	for (int i = 0; i < cornerLenght; i++)
	{
		renderedMap[cornerPosition - cornerLenght][cornerPosition - i] = PRINT_VOID;
		renderedMap[WINDOW_SIZE - 1 - (cornerPosition - cornerLenght)][cornerPosition - i] = PRINT_VOID;
	}
}

void MapViewer::SetLeftVerticalWall(vector<vector<int>>& map, int cornerPosition, int cornerLenght)
{
	int playerFor = GetNearestPlayerForward(map);
	for (int i = cornerPosition; i < WINDOW_SIZE - cornerPosition; i++)
	{
		if (cornerPosition - 1 > ((playerPos.x - playerFor) * FIXEL_SIZE))
			continue;
		renderedMap[i][cornerPosition] = PRINT_VOID;
	}

	int endPosition = cornerPosition + cornerLenght;
	if ((playerPos.x - playerFor) * FIXEL_SIZE <= cornerPosition + cornerLenght)
		return;
	for (int i = endPosition; i < WINDOW_SIZE - endPosition; i++)
	{
		if (cornerPosition - 1 > ((playerPos.x - playerFor) * FIXEL_SIZE))
			continue;
		renderedMap[i][endPosition] = PRINT_VOID;
	}
}

void MapViewer::SetRightVerticalWall(vector<vector<int>>& map, int cornerPosition, int cornerLenght)
{
	int playerFor = GetNearestPlayerForward(map);
	//오른쪽에서 코너까지의 벽
	for (int i = WINDOW_SIZE - cornerPosition - 1; i <= cornerPosition; i++)
	{
		if (cornerPosition < WINDOW_SIZE - ((playerPos.x - playerFor) * FIXEL_SIZE))
			continue;
		renderedMap[i][cornerPosition] = PRINT_VOID;
	}
	//코너에서 전방까지의 벽
	int endPosition = cornerPosition - cornerLenght;
	for (int i = WINDOW_SIZE - endPosition - 1; i <= endPosition; i++)
	{
		if (endPosition < WINDOW_SIZE - ((playerPos.x - playerFor) * FIXEL_SIZE))
			continue;
		renderedMap[i][endPosition] = PRINT_VOID;
	}
}

int MapViewer::GetPathLength(vector<vector<int>>& map, int st, int dir)
{
	int cnt = 0;
	for (int i = st; i > 0; i--)
	{
		if (map[i][playerPos.y] == MAP_ELEMENT::WALL)
			break;
		if (map[i][playerPos.y + dir] == MAP_ELEMENT::WALL)
			break;
		cnt++;
	}
	return cnt;
}

void MapViewer::SetCornerBoundary(vector<vector<int>>& map)
{
	int playerFor = GetNearestPlayerForward(map);
	for (int i = playerPos.x; i > 0; i--)
	{
		if (map[i][playerPos.y] == MAP_ELEMENT::WALL)
			break;
		if (map[i][playerPos.y - 1] != MAP_ELEMENT::WALL)
		{
			int leftPathCnt = GetPathLength(map, i, -1);
			SetLeftEdgeWall((playerPos.x - i) * FIXEL_SIZE, FIXEL_SIZE * leftPathCnt);
			SetLeftVerticalWall(map, (playerPos.x - i) * FIXEL_SIZE, FIXEL_SIZE * leftPathCnt);
			SetLeftHorizontalWall(map, (playerPos.x - i) * FIXEL_SIZE, FIXEL_SIZE * leftPathCnt);
			i -= leftPathCnt;
		}
	}

	for (int i = playerPos.x; i > 0; i--)
	{
		if (map[i][playerPos.y] == MAP_ELEMENT::WALL)
			break;
		if (map[i][playerPos.y + 1] != MAP_ELEMENT::WALL)
		{
			int rightPathCnt = GetPathLength(map, i, 1);
			SetRightEdgeWall((WINDOW_SIZE - 1) - (playerPos.x - i) * FIXEL_SIZE, FIXEL_SIZE * rightPathCnt);
			SetRightVerticalWall(map, (WINDOW_SIZE - 1) - (playerPos.x - i) * FIXEL_SIZE, FIXEL_SIZE * rightPathCnt);
			SetRightHorizontalWall(map, (WINDOW_SIZE - 1) - (playerPos.x - i) * FIXEL_SIZE, FIXEL_SIZE * rightPathCnt);
			i -= rightPathCnt;
		}
	}
}
