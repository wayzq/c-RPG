#pragma once
#include "Npc.h"
class CNpcMgr
{
public:
	CNpcMgr();
	CNpc* getNpc(int i, int j, int mapID);
private:
	void createNpc();
	vector<CNpc*> m_vecNpc;
};

