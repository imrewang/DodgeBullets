#include"sleep.h"


void sleep(DWORD ms)  // 精确延时函数
{
	static DWORD oldtime = GetTickCount();
	while (GetTickCount() - oldtime < ms)
		Sleep(1);
	oldtime = GetTickCount();
}