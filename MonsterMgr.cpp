#include "MonsterMgr.h"
#include "DataMgr.h"
#include "Define.h"
#include "GameMgr.h"
CMonsterMgr::CMonsterMgr()
{
	this->createMonster();
	m_mapDir[E_DIR_NONE] = CVec2(0, 0);
	m_mapDir[E_DIR_UP] = CVec2(-1, 0);
	m_mapDir[E_DIR_DOWN] = CVec2(1, 0);
	m_mapDir[E_DIR_LEFT] = CVec2(0, -1);
	m_mapDir[E_DIR_RIGHT] = CVec2(0, 1);
}

void CMonsterMgr::createMonster()
{
	int nSize = CDataMgr::getInstance()->getMgr<CMonsterDtMgr>("MonsterDtMgr")->getSize();
	for (int i = 0; i < nSize; i++)
	{
		CMonsterDt* pData = CDataMgr::getInstance()->getMgr<CMonsterDtMgr>("MonsterDtMgr")->getDataByID<CMonsterDt>(4001 + i);
		int nCount = pData->nCountInMap;
		CMapDt* pMapDt = CDataMgr::getInstance()->getMgr<CMapDtMgr>("MapDtMgr")->getDataByID<CMapDt>(pData->nMapID);
		for (int j = 0; j < nCount; j++)
		{
			CMonster* pMonster = new CMonster();
			int nRandomRow = 1 + rand() % (pMapDt->nRowSize - 2);
			int nRandomCol = 1 + rand() % (pMapDt->nColSize - 2);
			pMonster->setPosition(nRandomRow, nRandomCol);
			pMonster->initWithData(pData);
			m_vecMonster.push_back(pMonster);
		}
	}
}

void CMonsterMgr::onUpdate()
{
	for (int i = 0; i < m_vecMonster.size(); i++)
	{
		m_vecMonster[i]->onUpdate(m_mapDir);
	}
	CMapDt* pCurMapDt = CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getCurMap();
	for (int i = 0; i < m_vecMonster.size(); i++)
	{
		CVec2 vPos = m_vecMonster[i]->getPosition();
		if (1 == pCurMapDt->pMap[vPos.x][vPos.y])
		{
			m_vecMonster[i]->onRestore();
		}
	}
}

CMonster* CMonsterMgr::getMonster(int nRow, int nCol, int nMapID)
{
	for (CMonster* monster : m_vecMonster)
	{
		if (monster->isMonster(nRow, nCol, nMapID))
		{
			return monster;
		}
	}
	return nullptr;
}

void CMonsterMgr::deleteMonster(CMonster* monster)
{
	for (int i = 0; i < m_vecMonster.size(); i++)
	{
		if (m_vecMonster[i]->getID() == monster->getID())
		{
			CVec2 monsterVec2 = monster->getPosition();
			CVec2 m_vecMonsterVec2 = m_vecMonster[i]->getPosition();
			if (m_vecMonsterVec2.x== monsterVec2.x&& m_vecMonsterVec2.y== monsterVec2.y)
			{
				m_vecMonster.erase(m_vecMonster.begin() + i);
				return;
			}
		}
	}
}
