#pragma once
#include "GameMenu.h"
#include "DataMgr.h"
#include "WndBase.h"
#include "GameMap.h"
#include "Shop.h"
class CGameMgr
{
public:
	void onUpdate();
	void onRender();
	void changeWnd(CWndBase* pWnd);
	void restoreWnd();
	template <class T>
	T* getWndByName(string strName)
	{
		if (strName.empty())
		{
			return nullptr;
		}
		if (m_pCurWnd && m_pCurWnd->getName() == strName)
		{
			return static_cast<T*>(m_pCurWnd);
		}
		for (CWndBase* pWnd : m_vecWnds)
		{
			if (strName == pWnd->getName())
			{
				return static_cast<T*>(pWnd);
			}
		}
		return nullptr;
	}
	CWndBase* getCurWnd() {
		return m_pCurWnd;
	}
	static CGameMgr* getInstance();
private:
	CWndBase* m_pCurWnd;
	vector<CWndBase*> m_vecWnds;
	CGameMgr();
	static CGameMgr* m_spInstance;
};

