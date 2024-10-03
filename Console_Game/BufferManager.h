#pragma once
#include "Singleton.h"
#include <iostream>
#include <Windows.h>
#define BUF_SIZE 10240

class BufferManager : public Singleton<BufferManager>
{
public:
	void Init();
	void Render();
	void AddToBuffer(const std::string &string);
	void ScreenPrint(int x, int y, const char* string);
	std::string buffer;
	void ScreenClear();
private:
	int screenIndex;// �ܼ� ���� �ε���
	HANDLE screen[2];//�ܼ�2��
	void SwitchScreenBuffer();
};

