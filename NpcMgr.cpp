#include "NpcMgr.h"
#include "DataMgr.h"
#include "Define.h"
CNpcMgr::CNpcMgr()
{
	this->createNpc();
}

CNpc* CNpcMgr::getNpc(int i, int j, int mapID)
{
	for (CNpc* npc : m_vecNpc)
	{
		if (npc->isNpc(i, j, mapID))
		{
			return npc;
		}
	}
	return nullptr;
}

void CNpcMgr::createNpc()
{
	int nCount = CDataMgr::getInstance()->getMgr<CNpcDtMgr>("NpcDtMgr")->getSize();
	for (int i = 0; i < nCount; i++)
	{
		CNpc* npc = new CNpc();
		int id = i + 2001;
		CNpcDt* npcDt = CDataMgr::getInstance()->getMgr<CNpcDtMgr>("NpcDtMgr")->getDataByID<CNpcDt>(id);
		npc->initWithData(npcDt);
		m_vecNpc.push_back(npc);
	}
}
