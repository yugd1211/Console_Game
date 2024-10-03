#include "GameManager.h"
#include "SceneManager.h"
#include "BufferManager.h"
#include "Enum.h"
#include <sstream>

void GameManager::DisplayKeyGuide() const
{
	static int widthSize = WINDOW_SIZE - 1;
	std::ostringstream oss;

	for (int i = 0; i < WINDOW_SIZE; i++)
		oss << PRINT_WALL;
	oss << "\n";

	oss << PRINT_WALL << setw(widthSize * 2) << right << PRINT_WALL << "\n";

	oss << PRINT_WALL << setw(widthSize) << " 현재 스테이지 : " + to_string(SceneManager::GetInstance().GetCurrentSceneIndex()) << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize * 2) << right << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " 키보드 입력" << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize * 2) << right << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " Q : 좌로 방향전환" << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " E : 우로 방향전환" << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " W || ↑ : 위로 이동" << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " A || ← : 좌로 이동" << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " S || → : 우로 이동" << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " D || ↓ : 아래로 이동" << setw(widthSize) << PRINT_WALL << "\n";

	oss << PRINT_WALL << setw(widthSize * 2) << right << PRINT_WALL << "\n";
	for (int i = 0; i < WINDOW_SIZE; i++)
		oss << PRINT_WALL;
	oss << "\n";
	oss << "\n";
	BufferManager::GetInstance().AddToBuffer(oss.str());

}

void GameManager::DisplayWindow() const
{
	SceneManager::GetInstance().GetCurrentScene()->viewer->Rendering(
		SceneManager::GetInstance().GetCurrentScene()->map->board);
	SceneManager::GetInstance().GetCurrentScene()->viewer->Display();
	DisplayKeyGuide();
	SceneManager::GetInstance().GetCurrentScene()->map->Display();
	BufferManager::GetInstance().Render();
}


void GameManager::GameStart()
{
	DisplayWindow();
	while (true)
	{
		if (GameOver())
			Win();
		Sleep(30);
		KEY_INPUT dir = InputManager::GetInstance().GetInput();
		if (dir == KEY_INPUT::GAME_OVER)
			GameExit();
		if (dir == KEY_INPUT::NONE)
			continue;
		SceneManager::GetInstance().GetCurrentScene()->MovePlayer(dir);
		DisplayWindow();
	}
}

void GameManager::Win() const
{
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
