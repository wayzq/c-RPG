#pragma once
#include "DataStruct.h"
#include "WndBase.h"
#include "Player.h"
class CPlSelect:public CWndBase
{
public:
	CPlSelect();
	void onUpdate();
	void onRender();
private:
	int m_nCurIndex;
	bool selectSuccess;
};

