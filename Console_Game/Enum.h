#pragma once

#define MAX_GAME_COUNT 3
#define BOARD_SIZE 15
#define PRINT_PLAYER "★"
#define PRINT_WALL "■"
#define PRINT_OBSTACLE "▩"
#define PRINT_EXIT " E"


#define MAP_SIZE 72
#define FIXEL_SIZE 3
const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };



enum KEY_INPUT
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
	TURN_LEFT,
	TURN_RIGHT,
	GAME_OVER,
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

