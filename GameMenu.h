#pragma once
#include "WndBase.h"
#include "GameMgr.h"
#include "Define.h"
class CGameMenu : public CWndBase
{
public:
	CGameMenu();
	virtual void onUpdate();
	virtual void onRender();
private:
	int m_nMenuState;
};

