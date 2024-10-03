#include "BufferManager.h"
using namespace std;

void BufferManager::Init()
{
	CONSOLE_CURSOR_INFO cci;

	// 콘솔 버퍼 생성 함수
	// 1. 입출력 모드 설정
	// 2. 공유 모드 설정 해당 콘솔의 공유할 때 어떤 모드를 지원할 것인지
	// 3. 보안 속성(자식 프로세스) 설정
	// 4. 버퍼 모드(CLI, GUI) 설정
	// 5. 초기값
	screen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	screen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// 커서를 숨긴다.
	//cci.dwSize = 1;
	//cci.bVisible = FALSE;
	// 해당 정보를 콘솔에 적용
	//SetConsoleCursorInfo(screen[0], &cci);
	//SetConsoleCursorInfo(screen[1], &cci);
}

void BufferManager::SwitchScreenBuffer()
{
	// 화면 전환
	SetConsoleActiveScreenBuffer(screen[screenIndex]);
	screenIndex = !screenIndex;
}

void BufferManager::ScreenClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	// 특정 콘솔을 특정 문자로 채우는 함수
	// 콘솔, 채울 문자, 채울 문자 수, 시작 좌표, 실제로 채워진 문자 수
	// 빈문자로 채우는 과정
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
