#include "GameMenu.h"
#include "GameMgr.h"
#include "Define.h"
#include "GameMap.h"
#include "MenuSet.h"
#include "PlSelect.h"
CGameMenu::CGameMenu()
{
	m_nMenuState = E_MENU_START;
}

void CGameMenu::onUpdate()
{
	if (KEY_DOWN(VK_RETURN))
	{
		if (E_MENU_START == m_nMenuState)
		{
			
			CGameMap* pGameMap = new CGameMap();
			pGameMap->setName("GameMap");
			CGameMgr::getInstance()->changeWnd(pGameMap);
		}
		if (E_MENU_SET==m_nMenuState)
		{
			CMenuSet* pMenuSet = new CMenuSet();
			pMenuSet->setName("MenuSet");
			CGameMgr::getInstance()->changeWnd(pMenuSet);
		}
		if (E_MENU_EXIT==m_nMenuState)
		{
			exit(0);
		}
		g_bClear = true;
		return;
	}
	if (KEY_DOWN('W'))
	{
		m_nMenuState--;
		if (m_nMenuState < E_MENU_START)
		{
			m_nMenuState = E_MENU_EXIT;
		}
	}
	else if (KEY_DOWN('S'))
	{
		m_nMenuState++;
		if (m_nMenuState > E_MENU_EXIT)
		{
			m_nMenuState = E_MENU_START;
		}
	}
}

void CGameMenu::onRender()
{
	if (E_MENU_START == m_nMenuState)
	{
		cout << "->游戏开始" << endl;
		cout << "  游戏设置" << endl;
		cout << "  游戏结束" << endl;
	}
	else if (E_MENU_SET == m_nMenuState)
	{
		cout << "  游戏开始" << endl;
		cout << "->游戏设置" << endl;
		cout << "  游戏结束" << endl;
	}
	else if (E_MENU_EXIT == m_nMenuState)
	{
		cout << "  游戏开始" << endl;
		cout << "  游戏设置" << endl;
		cout << "->游戏结束" << endl;
	}
}
