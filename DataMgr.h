#pragma once
#include "DataBase.h"
#include <map>
class CDataMgr:public CDataBase
{
public:
	static CDataMgr* getInstance();
	void addMgr(string strName, CDataBaseMgr* pMgr);//¥¢¥Ê–¬≈‰∂‘
	template <class T>
	T* getMgr(string strName)
	{
		if (strName.empty())
		{
			return nullptr;
		}
		int nCount = m_mapMgr.count(strName);
		if (nCount > 0)
		{
			return static_cast<T*>(m_mapMgr[strName]);
		}
		return nullptr;
	}
private:
	CDataMgr();
	static CDataMgr* m_spInstance;
	map<string, CDataBaseMgr*> m_mapMgr;
};

