#include "BufferManager.h"
#include "Enum.h"
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

	// 콘솔 커서 설정 (안보이게 설정)
	cci.bVisible = FALSE;
	// 해당 커서 설정을 콘솔에 적용
	SetConsoleCursorInfo(screen[0], &cci);
	SetConsoleCursorInfo(screen[1], &cci);
}

void BufferManager::SwitchScreenBuffer()
{
	// 화면 전환
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
