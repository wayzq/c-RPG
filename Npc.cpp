#include "Npc.h"
#include "Vec2.h"
CNpc::CNpc()
{
	m_nID = 0;
	m_sName = "";
	m_vPos = CVec2();
	m_nMapId = 0;
	m_sPic = "";
	m_nType = 0;
}
void CNpc::onRender()
{
	cout << m_sPic;
}

void CNpc::initWithData(CNpcDt* data)
{
	m_nID = data->nID;
	m_sName = data->strName;
	m_vPos.x = data->nRow;
	m_vPos.y = data->nCol;
	m_nMapId = data->nMapID;
	m_nType = data->nType;
	m_sPic = data->strPic;
}

bool CNpc::isNpc(int i, int j, int mapID)
{
	return m_vPos.x == i && m_vPos.y == j && m_nMapId == mapID;
}
