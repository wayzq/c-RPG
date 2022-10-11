#pragma once
#include"Define.h"
#include"Vec2.h"
#include"DataStruct.h"
#include"RoleBase.h"
class CMonster:public CRoleBase
{
public:
	CMonster();
	void initWithData(CMonsterDt* data);
	bool isMonster(int i, int j, int mapID);
	void onUpdate(map<int, CVec2> mapDir);
	SYN_THE_SIZE(int, m_nItemID, ItemID);
	SYN_THE_SIZE(int, m_nMove, Move);
	SYN_THE_SIZE(int, m_nMoveInterval, MoveInterval);
	SYN_THE_SIZE(int, m_nAttackType, AttackType);
	SYN_THE_SIZE(int, m_nMapID, MapID);
private:
	int m_nTime;
	int m_nDir;
};

