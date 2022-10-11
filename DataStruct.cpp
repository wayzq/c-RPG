#include "DataStruct.h"
#include <fstream>
CFactory* CFactory::m_spInstance = nullptr;//单例一定要记得置空
CMapDtMgr::CMapDtMgr()
{
}

CFactory::CFactory()
{
}

CFactory* CFactory::getInstance()
{
	if (!m_spInstance)
	{
		m_spInstance = new CFactory();
		m_spInstance->init();
	}
	return m_spInstance;
}

CFactory::~CFactory()
{
}

void CFactory::init()
{
	m_mapCallBack["MapDtMgr"] = [=]() {return new CMapDtMgr(); };
	m_mapCallBack["NpcDtMgr"] = [=]() {return new CNpcDtMgr(); };
	m_mapCallBack["ItemDtMgr"] = [=]() {return new CItemDtMgr(); };
	m_mapCallBack["MonsterDtMgr"] = [=]() {return new CMonsterDtMgr(); };
	m_mapCallBack["PlayerDtMgr"] = [=]() {return new CPlayerDtMgr(); };
}

CDataBaseMgr* CFactory::createTarget(string strName)
{
	if (strName.empty())//判断字符串是否为空
	{
		return nullptr;
	}
	int nCount = m_mapCallBack.count(strName);
	if (nCount <= 0)//判断字符串是否存在
	{
		return nullptr;
	}
	return m_mapCallBack[strName]();//返回字符串对应的函数
}

CLoadPath::CLoadPath()
{
}

CLoadPath::~CLoadPath()
{
}

void CLoadPath::parse(fstream& fromFile)
{
	string strInfo = "";
	fromFile >> strInfo;
	m_vecName.push_back(strInfo);
	fromFile >> strInfo;
	m_vecPath.push_back(strInfo);
}

void CMapDtMgr::parse(fstream& fromFile)
{
	CMapDt* pMapDt = new CMapDt();
	fromFile >> pMapDt->nID >> pMapDt->strName
		>> pMapDt->nInitRow >> pMapDt->nInitCol
		>> pMapDt->nRowSize >> pMapDt->nColSize;
	pMapDt->pMap = new int* [pMapDt->nRowSize];
	for (int i = 0; i < pMapDt->nRowSize; i++)
	{
		pMapDt->pMap[i] = new int[pMapDt->nColSize];
	}

	for (int i = 0; i < pMapDt->nRowSize; i++)
	{
		for (int j = 0; j < pMapDt->nColSize; j++)
		{
			fromFile >> pMapDt->pMap[i][j];
		}
	}
	m_vecDatas.push_back(pMapDt);
}

CNpcDtMgr::CNpcDtMgr()
{
}

void CNpcDtMgr::parse(fstream& fromFile)
{
	CNpcDt* pNpcDt = new CNpcDt();
	fromFile >> pNpcDt->nID >> pNpcDt->strName
		>> pNpcDt->nRow >> pNpcDt->nCol
		>> pNpcDt->nMapID >> pNpcDt->strPic >> pNpcDt->nType;
	m_vecDatas.push_back(pNpcDt);
}

CItemDtMgr::CItemDtMgr()
{
}

void CItemDtMgr::loadFile(string strPath)
{
	fstream fromFile(strPath);
	if (fromFile)
	{
		string strInfo = "";
		getline(fromFile, strInfo);
		int equipCount = 0;
		fromFile >> equipCount;
		vector<string> m_vecEquipType;
		for (int i = 0; i < equipCount; i++)
		{
			string equipType = "";
			fromFile >> equipType;
			m_vecEquipType.push_back(equipType);
		}
		for (int i = 0; i < m_vecEquipType.size(); i++)
		{
			string equipInfo = "";
			fromFile >> equipInfo;
			m_mapEquipInfo[m_vecEquipType[i]] = equipInfo;
		}
		int nCount = 0;
		fromFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			this->parse(fromFile);
		}
	}
}

void CItemDtMgr::parse(fstream& fromFile)
{
	CItemDt* pItemDt = new CItemDt();
	fromFile >> pItemDt->nID >> pItemDt->strName
		>> pItemDt->nHp >> pItemDt->nMp
		>> pItemDt->nAck >> pItemDt->nDef
		>> pItemDt->nPrice >> pItemDt->nOther
		>> pItemDt->strDescription >> pItemDt->nOverLying
		>> pItemDt->nNpcID >> pItemDt->strType;
	m_vecDatas.push_back(pItemDt);
}

vector<CItemDt*> CItemDtMgr::getDataByNpcID(int nNpcID)
{
	vector<CItemDt*> allDatas = this->getAllDatas<CItemDt>();
	vector<CItemDt*> vecData;
	for (CItemDt* data : allDatas)
	{
		if (data->nNpcID == nNpcID)
		{
			vecData.push_back(data);
		}
	}
	return vecData;
}

CMonsterDtMgr::CMonsterDtMgr()
{
}

void CMonsterDtMgr::parse(fstream& fromFile)
{
	CMonsterDt* pData = new CMonsterDt();
	fromFile >> pData->nID >> pData->strName
		>> pData->nHp >> pData->nMp
		>> pData->nAck >> pData->nDef
		>> pData->strPic >> pData->nExp
		>> pData->nMoney >> pData->nItemID
		>> pData->nAttackType >> pData->nMapID
		>> pData->nMove >> pData->nMoveInterval >> pData->nCountInMap;
	m_vecDatas.push_back(pData);
}

CPlayerDtMgr::CPlayerDtMgr()
{
}

void CPlayerDtMgr::parse(fstream& fromFile)
{
	CPlayerDt* pData = new CPlayerDt();
	fromFile >> pData->nID >> pData->strName
		>> pData->nHp >> pData->nMp
		>> pData->nMoney >> pData->nAck
		>> pData->nDef >> pData->strPic
		>> pData->strDescription;
	m_vecDatas.push_back(pData);
}

void CLoader::load()
{
	CLoadPath* pLoad = new CLoadPath();
	pLoad->loadFile("data/Path.txt");
	for (int i = 0; i < pLoad->m_vecName.size(); i++)
	{
		CDataBaseMgr* pMgr = CFactory::getInstance()->createTarget(pLoad->m_vecName[i]);
		pMgr->loadFile(pLoad->m_vecPath[i]);
		CDataMgr::getInstance()->addMgr(pLoad->m_vecName[i], pMgr);
	}
}

