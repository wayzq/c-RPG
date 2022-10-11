#include "DataMgr.h"
CDataMgr* CDataMgr::m_spInstance = nullptr;
CDataMgr::CDataMgr()
{

}

CDataMgr* CDataMgr::getInstance()
{
	if (!m_spInstance)
	{
		m_spInstance = new CDataMgr();
	}
	return m_spInstance;
}

void CDataMgr::addMgr(string strName, CDataBaseMgr* pMgr)
{
	if (strName.empty()||!pMgr)
	{
		return;
	}
	m_mapMgr.insert(make_pair(strName, pMgr));
}
