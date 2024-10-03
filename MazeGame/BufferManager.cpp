#include "BufferManager.h"
#include "Enum.h"
using namespace std;

void BufferManager::Init()
{
	CONSOLE_CURSOR_INFO cci;

	// �ܼ� ���� ���� �Լ�
	// 1. ����� ��� ����
	// 2. ���� ��� ���� �ش� �ܼ��� ������ �� � ��带 ������ ������
	// 3. ���� �Ӽ�(�ڽ� ���μ���) ����
	// 4. ���� ���(CLI, GUI) ����
	// 5. �ʱⰪ
	screen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// �ܼ� Ŀ�� ���� (�Ⱥ��̰� ����)
	cci.bVisible = FALSE;
	// �ش� Ŀ�� ������ �ֿܼ� ����
	SetConsoleCursorInfo(screen[0], &cci);
	SetConsoleCursorInfo(screen[1], &cci);
}

void BufferManager::SwitchScreenBuffer()
{
	// ȭ�� ��ȯ
	SetConsoleActiveScreenBuffer(screen[screenIndex]);
	screenIndex = !screenIndex;
}

void BufferManager::Render()
{
	SetConsoleCursorPosition(screen[screenIndex], {0, 0});
	WriteFile(screen[screenIndex], buffer.c_str(), buffer.size(), NULL, NULL);
	SwitchScreenBuffer();
	buffer.clear();
	buffer = string();
}

void BufferManager::AddToBuffer(const string &string)
{
	buffer += string;
}
