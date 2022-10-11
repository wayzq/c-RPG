#include "PlSelect.h"
#include "GameMgr.h"
#include<iomanip>

CPlSelect::CPlSelect()
{
	m_nCurIndex = 0;
	selectSuccess = false;
}

void CPlSelect::onRender()
{
	cout << "  名字\t\t血量\t蓝量\t攻击力\t防御力\t金钱\t描述" << endl;
	int nSize = CDataMgr::getInstance()->getMgr<CPlayerDtMgr>("PlayerDtMgr")->getSize();
	for (int i = 0; i < nSize; i++)
	{
		if (m_nCurIndex == i)
		{
			cout << "->";
		}
		else {
			cout << "  ";
		}
		CPlayerDt* pData = CDataMgr::getInstance()->getMgr<CPlayerDtMgr>("PlayerDtMgr")->getDataByID<CPlayerDt>(5001 + i);
		cout << setiosflags(ios::left) << setw(6) << pData->strName << "\t"
			<< pData->nHp << "\t"
			<< pData->nMp << "\t"
			<< pData->nAck << "\t"
			<< pData->nDef << "\t"
			<< pData->nMoney << "\t";
		if (m_nCurIndex == i)
		{
			cout << pData->strDescription;
		}
		cout << endl;
	}
	if (selectSuccess)
	{
		cout << "你等级不够" << endl;
	}
}

void CPlSelect::onUpdate()
{
	int nSize = CDataMgr::getInstance()->getMgr<CPlayerDtMgr>("PlayerDtMgr")->getSize();
	CPlayer* player = CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer();
	if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->restoreWnd();
		g_bClear = true;
		return;
	}
	if (KEY_DOWN('W'))
	{
		m_nCurIndex--;
		m_nCurIndex = m_nCurIndex < 0 ? 0 : m_nCurIndex;
		g_bClear = true;
	}
	else if (KEY_DOWN('S'))
	{
		m_nCurIndex++;
		m_nCurIndex = m_nCurIndex < nSize ? m_nCurIndex : nSize - 1;
		g_bClear = true;
	}
	if (KEY_DOWN(VK_RETURN))
	{
		if (player->getLevel() > 2)
		{
			CPlayerDt* pData = CDataMgr::getInstance()->getMgr<CPlayerDtMgr>("PlayerDtMgr")->getDataByID<CPlayerDt>(5001 + m_nCurIndex);
			player->initWithData(pData);
			CGameMgr::getInstance()->restoreWnd();
			g_bClear = true;
			return;
		}
		else {
			selectSuccess = true;
		}
	}
}
