#include "DataBase.h"

CDataBaseMgr::CDataBaseMgr()
{
}

CDataBaseMgr::~CDataBaseMgr()
{
}

void CDataBaseMgr::loadFile(string strPath)
{
	fstream fromFile(strPath);
	if (fromFile)
	{
		string strInfo = "";
		getline(fromFile, strInfo);
		int nCount = 0;
		fromFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			this->parse(fromFile);
		}
	}
}
