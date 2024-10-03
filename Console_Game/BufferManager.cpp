#include "BufferManager.h"
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

	// Ŀ���� �����.
	//cci.dwSize = 1;
	//cci.bVisible = FALSE;
	// �ش� ������ �ֿܼ� ����
	//SetConsoleCursorInfo(screen[0], &cci);
	//SetConsoleCursorInfo(screen[1], &cci);
}

void BufferManager::SwitchScreenBuffer()
{
	// ȭ�� ��ȯ
	SetConsoleActiveScreenBuffer(screen[screenIndex]);
	screenIndex = !screenIndex;
}

void BufferManager::ScreenClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	// Ư�� �ܼ��� Ư�� ���ڷ� ä��� �Լ�
	// �ܼ�, ä�� ����, ä�� ���� ��, ���� ��ǥ, ������ ä���� ���� ��
	// ���ڷ� ä��� ����
	buffer.clear();
	//buffer = string();
	FillConsoleOutputCharacter(screen[screenIndex], ' ', 80 * 40, Coor, &dw);

}

void BufferManager::ScreenPrint(int x, int y, const char* string)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(screen[screenIndex], CursorPosition);
	WriteFile(screen[screenIndex], string, strlen(string), &dw, NULL);
}

void BufferManager::Render()
{
	ScreenPrint(0, 0, buffer.c_str());
	SwitchScreenBuffer();
	ScreenClear();
}

void BufferManager::AddToBuffer(const string &string)
{
	buffer += string;
}
