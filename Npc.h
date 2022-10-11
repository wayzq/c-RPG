#pragma once
#include "Vec2.h"
#include "DataStruct.h"
#include "Define.h"
class CNpc
{
public:
	CNpc();
	void onRender();
	void initWithData(CNpcDt* data);
	bool isNpc(int i, int j,int mapID);
	SYN_THE_SIZE(int, m_nID, ID);
	SYN_THE_SIZE(string, m_sName, Name);
	SYN_THE_SIZE(CVec2, m_vPos, Pos);
	SYN_THE_SIZE(int, m_nMapId, MapID);
	SYN_THE_SIZE(string, m_sPic, Pic);
	SYN_THE_SIZE(int, m_nType, Type);
};

