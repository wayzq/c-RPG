#include "MenuSet.h"
CMenuSet::CMenuSet()
{
}

CMenuSet::~CMenuSet()
{
}

void CMenuSet::onUpdate()
{
	if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->restoreWnd();
		g_bClear = true;
		return;
	}
}

void CMenuSet::onRender()
{
	cout << "ÉèÖÃ";
}
