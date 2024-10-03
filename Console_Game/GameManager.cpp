#include "GameManager.h"
#include "Enum.h"
#include "SceneManager.h"

// state.Pathway
void GameManager::DisplayKeyGuide() const
{

	for (int i = 0; i < WINDOW_SIZE; i++)
		cout << PRINT_WALL;
	cout << endl;
	string stage = " ���� �������� : ";
	stage += SceneManager::GetInstance().GetCurrentSceneIndex() + '0';
	cout << PRINT_WALL << setw(WINDOW_SIZE * 2 - 4) << left << stage << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(WINDOW_SIZE * 2 - 4) << left << " Ű���� �Է�" << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(WINDOW_SIZE * 2 - 4) << left << " w || �� : �����̵�" << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(WINDOW_SIZE * 2 - 4) << left << " a || �� : �·��̵�" << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(WINDOW_SIZE * 2 - 4) << left << " s || �� : ����̵�" << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(WINDOW_SIZE * 2 - 4) << left << " d || �� : �Ʒ����̵�" << PRINT_WALL<< "\n";
	for (int i = 0; i < WINDOW_SIZE; i++)
		cout << PRINT_WALL;
	cout << endl;
}

void GameManager::DisplayWindow() const
{
	SceneManager::GetInstance().GetCurrentScene()->viewer->Rendering(
		SceneManager::GetInstance().GetCurrentScene()->map->board);
	SceneManager::GetInstance().GetCurrentScene()->viewer->Display();
	DisplayKeyGuide();
	SceneManager::GetInstance().GetCurrentScene()->map->Display();
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
	// �� ����
	for (int i = 1; i <= MAX_GAME_COUNT; i++)
		SceneManager::GetInstance().AddScene(i, SceneManager::GetInstance().MakeScene());
	SceneManager::GetInstance().SetCurrentScene(1);

	DisplayWindow();
	while (true)
	{
		if (GameOver())
			GameExit();
		Sleep(30);
		KEY_INPUT dir = InputManager::GetInstance().GetInput();
		if (dir == KEY_INPUT::GAME_OVER)
			GameExit();
		if (dir == KEY_INPUT::NONE)
			continue;
		system("cls");
		SceneManager::GetInstance().GetCurrentScene()->MovePlayer(dir);
		DisplayWindow();
	}
}

void GameManager::GameExit()
{
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~" << endl;
	exit(0);
}
