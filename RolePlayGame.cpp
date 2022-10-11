// RolePlayGame.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "GameMenu.h"
bool g_bClear = false;
int main()
{
	CLoader::load();
	srand((unsigned int)time(0));
	CGameMgr::getInstance()->changeWnd(new CGameMenu());
	while (true)
	{
		CONSOLE_CURSOR_INFO cursor; //定义结构体 控制台光标信息
		cursor.bVisible = 0; //设置不显示
		cursor.dwSize = 1; //bzd
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor); //设置光标信息
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
		Sleep(100);
		CGameMgr::getInstance()->onUpdate();
		CGameMgr::getInstance()->onRender();
	}
}


