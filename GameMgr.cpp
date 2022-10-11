#include "GameMgr.h"
#include "Define.h"
CGameMgr* CGameMgr::m_spInstance = nullptr;
CGameMgr* CGameMgr::getInstance()
{
	if (!m_spInstance)
	{
		m_spInstance = new CGameMgr();
	}
	return m_spInstance;
}
CGameMgr::CGameMgr()
{
	m_pCurWnd = nullptr;
}

void CGameMgr::onUpdate()
{
	m_pCurWnd->onUpdate();
}

void CGameMgr::onRender()
{
	if (g_bClear)
	{
		system("cls");
		g_bClear = false;
	}
	m_pCurWnd->onRender();
}
void CGameMgr::changeWnd(CWndBase* pWnd)
{
	if (m_pCurWnd)
	{
		m_vecWnds.push_back(m_pCurWnd);
	}
	m_pCurWnd = pWnd;
}

void CGameMgr::restoreWnd()
{
	if (m_pCurWnd->getDelete())
	{
		SAFE_DEL(m_pCurWnd);
	}
	m_pCurWnd = m_vecWnds.back();
}