#include"sleep.h"


void sleep(DWORD ms)  // ��ȷ��ʱ����
{
	static DWORD oldtime = GetTickCount();
	while (GetTickCount() - oldtime < ms)
		Sleep(1);
	oldtime = GetTickCount();
}