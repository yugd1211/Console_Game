#include "GameManager.h"
#include "Map.h"

// state.Pathway
void DisplayPathway()
{
	SceneManager::GetInstance().GetCurrentScene()->map->DisplayMap();

	string stage = " ���� �������� : ";
	stage += SceneManager::GetInstance().GetCurrentSceneIndex() + '0';
	cout << PRINT_WALL << setw(56) << left << stage << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(56) << left << " Ű���� �Է�" << PRINT_WALL <<"\n";
	cout << PRINT_WALL << setw(56) << left << " w || �� : �����̵�" << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(56) << left << " a || �� : �·��̵�" << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(56) << left << " s || �� : ����̵�" << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(56) << left << " d || �� : �Ʒ����̵�" << PRINT_WALL<< "\n";
	for (int i = 0; i < BOARD_SIZE; i++)
		cout << PRINT_WALL;
	cout << endl;
}

// state.Pathway
DIRECTION InputPathway()
{
	char c = _getch();
	if (c == 72 || c == 'w')
		return DIRECTION::UP;
	else if (c == 75 || c == 'a')
		return DIRECTION::LEFT;
	else if (c == 80 || c == 's')
		return DIRECTION::DOWN;
	else if (c == 77 || c == 'd')
		return DIRECTION::RIGHT;
	return DIRECTION::NONE;
}


void GameManager::GameStart()
{

	if (MAX_GAME_COUNT < 1)
		return ;
	for (int i = 1; i <= MAX_GAME_COUNT; i++)
		SceneManager::GetInstance().AddScene(i, SceneManager::GetInstance().MakeScene());
	SceneManager::GetInstance().SetCurrentScene(1);
	while (true)
	{
		system("cls");
		if (SceneManager::GetInstance().IsGameEnd())
		{
			cout << "���� ����~~~~~~~~~~~~~~~" << endl;
			break;
		}

		DisplayPathway();
		DIRECTION dir = InputManager::GetInstance().InputPathway();
		if (dir == NONE)
			continue;

		SceneManager::GetInstance().GetCurrentScene()->MovePlayer(dir);
	}
}

void GameManager::GameExit()
{
}
