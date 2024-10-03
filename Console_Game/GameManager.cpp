#include "GameManager.h"
#include "Enum.h"
#include "SceneManager.h"

void GameManager::DisplayKeyGuide() const
{
	static int widthSize = WINDOW_SIZE - 1;
	string stage = " 현재 스테이지 : ";
	stage += SceneManager::GetInstance().GetCurrentSceneIndex() + '0';
	for (int i = 0; i < WINDOW_SIZE; i++)
		cout << PRINT_WALL;
	cout << endl;
	cout << PRINT_WALL << setw(widthSize * 2) << right << PRINT_WALL << "\n";

	cout << PRINT_WALL << setw(widthSize) << stage << setw(widthSize) << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(widthSize * 2) << right << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(widthSize) << " 키보드 입력" << setw(widthSize) << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(widthSize * 2) << right << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(widthSize) << " w || ↑ : 위로이동" << setw(widthSize) << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(widthSize) << " a || ← : 좌로이동" << setw(widthSize) << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(widthSize) << " s || → : 우로이동" << setw(widthSize) << PRINT_WALL << "\n";
	cout << PRINT_WALL << setw(widthSize) << " d || ↓ : 아래로이동" << setw(widthSize) << PRINT_WALL<< "\n";
	
	cout << PRINT_WALL << setw(widthSize * 2) << right << PRINT_WALL << "\n";
	for (int i = 0; i < WINDOW_SIZE; i++)
		cout << PRINT_WALL;
	cout << endl;
	cout << endl;
}

void GameManager::DisplayWindow() const
{
	SceneManager::GetInstance().GetCurrentScene()->viewer->Rendering(
		SceneManager::GetInstance().GetCurrentScene()->map->board);
	SceneManager::GetInstance().GetCurrentScene()->viewer->Display();
	DisplayKeyGuide();
	SceneManager::GetInstance().GetCurrentScene()->map->Display();
	//BufferManager::GetInstance().Render();
}


void GameManager::GameStart()
{
	DisplayWindow();
	while (true)
	{
		if (GameOver())
			Win();
		//Sleep(30);
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

void GameManager::Win() const
{
	system("cls");
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다.\n";
	cout << "축하합니다. 게임을 클리어하셨습니다." << endl;
	exit(0);
}

void GameManager::GameExit() const
{
	system("cls");
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~\n";
	cout << "게임을 종료합니다~~~~~~~~~~~~~~~~~~~" << endl;
	exit(0);
}
