#pragma once

#define MAX_GAME_COUNT 3
#define BOARD_SIZE 15

#define PRINT_PLAYER "★"
#define PRINT_WALL "■"
#define PRINT_OBSTACLE "▩"
#define PRINT_EXIT "Ｅ"

#define MAP_WALL_RAN 2

#define WINDOW_SIZE 90
#define FIXEL_SIZE 6

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
	EMPTY,
	PLAYER,
	EXIT,
	WALL,
	OBSTACLE,
	ENEMY,
	OTHER,
};

