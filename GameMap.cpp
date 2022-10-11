#include "GameMap.h"
#include "DataMgr.h"
#include "GameMgr.h"
#include "Shop.h"
#include "Battle.h"
#include "PlSelect.h"

CGameMap::CGameMap()
{
	m_pCurMapDt = CDataMgr::getInstance()->getMgr<CMapDtMgr>("MapDtMgr")->getDataByID<CMapDt>(1001);
	m_pPlayer = new CPlayer();
	m_pNpcMgr = new CNpcMgr();
	m_pMonsterMgr = new CMonsterMgr();
	m_pPlayer->setPosition(m_pCurMapDt->nInitRow, m_pCurMapDt->nInitCol);
}

CGameMap::~CGameMap()
{
	SAFE_DEL(m_pPlayer);
	SAFE_DEL(m_pMonsterMgr);
	SAFE_DEL(m_pCurMapDt);
	SAFE_DEL(m_pNpcMgr);
}

void CGameMap::onUpdate()
{
	m_pPlayer->onUpdate();
	m_pMonsterMgr->onUpdate();
	CVec2 vPos = m_pPlayer->getPosition();
	if (1 == m_pCurMapDt->pMap[vPos.x][vPos.y])
	{
		m_pPlayer->onRestore();
	}
	int nNextMapID = m_pCurMapDt->pMap[vPos.x][vPos.y];
	if (nNextMapID > 1000)
	{
		m_pCurMapDt = CDataMgr::getInstance()->getMgr<CMapDtMgr>("MapDtMgr")->getDataByID<CMapDt>(nNextMapID);
		m_pPlayer->setPosition(m_pCurMapDt->nInitRow, m_pCurMapDt->nInitCol);
		g_bClear = true;
	}
	CNpc* npc = new CNpc();
	npc = m_pNpcMgr->getNpc(vPos.x, vPos.y, m_pCurMapDt->nID);
	if (npc)
	{
		if (npc->getType() == 0)
		{
			CShop* pShop = new CShop();
			pShop->setName("Shop");
			pShop->refreshItemDt(npc->getID());
			CGameMgr::getInstance()->changeWnd(pShop);
		}
		if (npc->getID() == 2005)
		{
			CPlSelect* pPlSelect = new CPlSelect();
			pPlSelect->setName("PlSelect");
			CGameMgr::getInstance()->changeWnd(pPlSelect);
		}
		g_bClear = true;
		m_pPlayer->onRestore();
	}
	if (KEY_DOWN('I'))
	{
		m_pPlayer->getBag()->setName("Bag");
		CGameMgr::getInstance()->changeWnd(m_pPlayer->getBag());
		g_bClear = true;
		return;
	}
	CMonster* pMonster = m_pMonsterMgr->getMonster(vPos.x, vPos.y, m_pCurMapDt->nID);
	if (pMonster)
	{
		CBattle* pBattle = new CBattle(m_pPlayer, pMonster);
		pBattle->setName("Battle");
		CGameMgr::getInstance()->changeWnd(pBattle);
		g_bClear = true;
		m_pPlayer->onRestore();
	}
}

void CGameMap::onRender()
{
	m_pPlayer->showStatus();
	cout << m_pCurMapDt->strName << endl;
	for (int i = 0; i < m_pCurMapDt->nRowSize; i++)
	{
		for (int j = 0; j < m_pCurMapDt->nColSize; j++)
		{
			CNpc* pNpc = m_pNpcMgr->getNpc(i, j, m_pCurMapDt->nID);
			CMonster* pMonster = m_pMonsterMgr->getMonster(i, j, m_pCurMapDt->nID);
			if (1 == m_pCurMapDt->pMap[i][j])
			{
				cout << "║Ж";
			}
			else if (m_pPlayer->isEquals(i, j))
			{
				m_pPlayer->onRender();
			}
			else if (1000 < m_pCurMapDt->pMap[i][j])
			{
				cout << "це";
			}
			else if (pNpc)
			{
				pNpc->onRender();
			}
			else if (pMonster)
			{
				pMonster->onRender();
			}
			else
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
	m_pPlayer->getEquip()->showEquip();
}
