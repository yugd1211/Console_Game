#pragma once

#define MAX_GAME_COUNT 3
#define BOARD_SIZE 30
#define PRINT_PLAYER "★"
#define PRINT_WALL "■"
#define PRINT_OBSTACLE "▩"
#define PRINT_EXIT " E"

const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };



enum DIRECTION
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
	NONE,
};

enum MAP_ELEMENT
{
	VOID,
	PLAYER,
	EXIT,
	WALL,
	OBSTACLE,
	ENEMY,
	OTHER, // 다른 이벤트? 혹은 ROOM?, EXIT이랑 합쳐서 Stage를 캡슐화해서 해당 stage가 이벤트 혹은 게임 종료의 트리거로 하는 방식으로 해도 될듯 
};

