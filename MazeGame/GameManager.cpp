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

	oss << PRINT_WALL << setw(widthSize) << " ���� �������� : " + to_string(SceneManager::GetInstance().GetCurrentSceneIndex()) << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize * 2) << right << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " Ű���� �Է�" << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize * 2) << right << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " Q : �·� ������ȯ" << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " E : ��� ������ȯ" << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " W || �� : ���� �̵�" << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " A || �� : �·� �̵�" << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " S || �� : ��� �̵�" << setw(widthSize) << PRINT_WALL << "\n";
	oss << PRINT_WALL << setw(widthSize) << " D || �� : �Ʒ��� �̵�" << setw(widthSize) << PRINT_WALL << "\n";

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
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
	cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�." << endl;
	exit(0);
}

void GameManager::GameExit() const
{
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~\n";
	cout << "������ �����մϴ�~~~~~~~~~~~~~~~~~~~" << endl;
	exit(0);
}
