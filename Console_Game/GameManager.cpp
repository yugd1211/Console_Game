#include "GameManager.h"
#include "Enum.h"
#include "SceneManager.h"

// state.Pathway
void GameManager::DisplayPathway() const
{

	for (int i = 0; i < 72; i++)
		cout << PRINT_WALL;
	cout << endl;
	string stage = " 현재 스테이지 : ";
	stage += SceneManager::GetInstance().GetCurrentSceneIndex() + '0';
	cout << PRINT_WALL << setw(140) << left << stage << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(140) << left << " 키보드 입력" << PRINT_WALL <<"\n";
	cout << PRINT_WALL << setw(140) << left << " w || ↑ : 위로이동" << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(140) << left << " a || ← : 좌로이동" << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(140) << left << " s || → : 우로이동" << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(140) << left << " d || ↓ : 아래로이동" << PRINT_WALL<< "\n";
	for (int i = 0; i < 72; i++)
		cout << PRINT_WALL;
	cout << endl;
}

// state.Pathway
KEY_INPUT InputPathway()
{
	char c = _getch();
	if (c == 72 || c == 'w')
		return KEY_INPUT::UP;
	else if (c == 75 || c == 'a')
		return KEY_INPUT::LEFT;
	else if (c == 80 || c == 's')
		return KEY_INPUT::DOWN;
	else if (c == 77 || c == 'd')
		return KEY_INPUT::RIGHT;
	return KEY_INPUT::NONE;
}


void GameManager::GameStart()
{
	//vector<vector<int>> playerMap = {
//	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
//	{1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
//	{1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
//	{1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
//	{1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
//	{1, 0, 1, 0, 0, 0, 1, 1, 0, 1},
//	{1, 0, 1, 0, 0, 0, 1, 1, 0, 1},
//	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//};
	vector<vector<int>> playerMap = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 2, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	if (MAX_GAME_COUNT < 1)
		return ;
	for (int i = 1; i <= MAX_GAME_COUNT; i++)
		SceneManager::GetInstance().AddScene(i, SceneManager::GetInstance().MakeScene());
	SceneManager::GetInstance().SetCurrentScene(1);
	while (!GameOver())
	{
		Sleep(30);
		KEY_INPUT dir = InputManager::GetInstance().InputPathway();
		if (dir == KEY_INPUT::GAME_OVER)
			GameExit();
		if (dir == KEY_INPUT::NONE)
			continue;
		system("cls");
		if (dir == KEY_INPUT::TURN_LEFT || dir == KEY_INPUT::TURN_RIGHT)
		{
			if (dir == KEY_INPUT::TURN_LEFT)
				SceneManager::GetInstance().GetCurrentScene()->map->ChangeLeftDirection();
			else if (dir == KEY_INPUT::TURN_RIGHT)
				SceneManager::GetInstance().GetCurrentScene()->map->ChangeRightDirection();
		}
		else
			SceneManager::GetInstance().GetCurrentScene()->MovePlayer(dir);
		SceneManager::GetInstance().GetCurrentScene()->viewer->ApplyMap(SceneManager::GetInstance().GetCurrentScene()->map->board);
		SceneManager::GetInstance().GetCurrentScene()->map->DisplayMap();

		SceneManager::GetInstance().GetCurrentScene()->viewer->Rendering();

		DisplayPathway();
	}
}

void GameManager::GameExit()
{
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~" << endl;
	exit(0);
}
