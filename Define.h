#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <map>
using namespace std;
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code)&0x8000?1:0)
#define SAFE_DEL(p) if(p){delete p; p = nullptr;}
enum
{
	E_MENU_START,
	E_MENU_SET,
	E_MENU_EXIT
};

enum {
	E_SHOP_FAIL,
	E_SHOP_SUCCESS,
	E_SHOP_IDLE
};

enum
{
	E_DIR_NONE,
	E_DIR_UP,
	E_DIR_DOWN,
	E_DIR_LEFT,
	E_DIR_RIGHT
};

enum {
	E_BATTLE_IDLE,
	E_BATTLE_PLAYER,
	E_BATTLE_ENEMY
};

enum {
	E_ACTION_NONE,
	E_ACTION_BATTLE,
	E_ACTION_ITEM,
	E_ACTION_RUN
};
extern bool g_bClear;

#define SYN_THE_SIZE(valueType,valueName,funcName)\
public:\
	valueType get##funcName()\
	{\
		return valueName;\
	}\
	void set##funcName(valueType nID)\
	{\
		valueName = nID;\
	}\
protected:\
	valueType valueName;


#define SYN_THE_SIZE_READONLY(valueType,valueName,funcName)\
public:\
	valueType get##funcName()\
	{\
		return valueName;\
	}\
protected:\
	valueType valueName;







