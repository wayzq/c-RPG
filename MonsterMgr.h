#pragma once
#include"Monster.h"
class CMonsterMgr
{
public:
	CMonsterMgr();
	void createMonster();
	void onUpdate();
	CMonster* getMonster(int nRow, int nCol, int nMapID);
	void deleteMonster(CMonster* monster);
private:
	vector<CMonster*> m_vecMonster;
	map<int, CVec2> m_mapDir;
};

