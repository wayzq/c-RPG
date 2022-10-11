#pragma once
#include"GameMenu.h"
class CMenuSet :public CWndBase
{
public:
	CMenuSet();
	~CMenuSet();
	virtual void onUpdate();
	virtual void onRender();
};

