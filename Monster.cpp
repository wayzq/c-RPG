#include "Monster.h"
#include "GameMgr.h"
#include <map>
CMonster::CMonster()
{
	m_nTime = 0;
	m_nDir = E_DIR_NONE;
	m_nMove = 0;
	m_nMapID = 0;
	m_nItemID = 0;
	m_nMoveInterval = 0;
	m_nAttackType = 0;
}
void CMonster::initWithData(CMonsterDt* data)
{
	m_nID = data->nID;
	m_nHp = data->nHp;
	m_nMp = data->nMp;
	m_nAck = data->nAck;
	m_nDef = data->nDef;
	m_strName = data->strName;
	m_strPic = data->strPic;
	m_nExp = data->nExp;
	m_nMoney = data->nMoney;
	m_nItemID = data->nItemID;
	m_nMove = data->nMove;
	m_nMoveInterval = data->nMoveInterval;
	m_nAttackType = data->nAttackType;
	m_nMapID = data->nMapID;
	m_nMaxHp = data->nHp;
	m_nMaxMp = data->nMp;

}

bool CMonster::isMonster(int i, int j, int mapID)
{
	return i == m_vPos.x && j == m_vPos.y && mapID == m_nMapID;
}

void CMonster::onUpdate(map<int, CVec2> mapDir)
{
	if (0 == m_nMove)
	{
		return;
	}
	if (CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getCurMap()->nID != m_nMapID)
	{
		return;
	}
	m_nTime++;
	if (m_nTime >= m_nMoveInterval)
	{
		m_nDir = rand() % 4 + 1;
		m_nTime = 0;
	}

	this->onBackUp();
	if (m_nTime>1)
	{
		m_vPos.x += mapDir[m_nDir].x;
		m_vPos.y += mapDir[m_nDir].y;
	}
}
