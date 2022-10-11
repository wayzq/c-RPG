#pragma once
#include "DataMgr.h"
#include <map>
#include "DataBase.h"
#include <functional>
typedef function<CDataBaseMgr* ()> CallBack;
class CFactory
{
public:
	CFactory();
	~CFactory();
	static CFactory* getInstance();
	void init();
	CDataBaseMgr* createTarget(string strName);
private:
	static CFactory* m_spInstance;
	map<string, CallBack> m_mapCallBack;
};

class CLoadPath :public CDataBaseMgr
{
public:
	CLoadPath();
	~CLoadPath();
	void parse(fstream& fromFile);
	vector<string> m_vecPath;
	vector<string> m_vecName;
};

class CLoader
{
public:
	static void load();
};

class CMapDt :public CDataBase
{
public:
	CMapDt()
	{
		nID = 0;
		strName = "";
		nInitRow = 0;
		nInitCol = 0;
		nRowSize = 0;
		nColSize = 0;
		pMap = nullptr;
	}
	string strName;
	int nInitRow;
	int nInitCol;
	int nRowSize;
	int nColSize;
	int** pMap;
};

//地图数据管理者
class CMapDtMgr :public CDataBaseMgr
{
public:
	CMapDtMgr();
	void parse(fstream& fromFile);
};

class CNpcDt :public CDataBase {
public:
	CNpcDt() {
		nID = 0;
		strName = "";
		nRow = 0;
		nCol = 0;
		nMapID = 0;
		strPic = "";
	}
	string strName;
	int nRow;
	int nCol;
	int nMapID;
	string strPic;
	int nType;
};

class CNpcDtMgr :public CDataBaseMgr
{
public:
	CNpcDtMgr();
	void parse(fstream& fromFile);
};

class CItemDt :public CDataBase
{
public:
	CItemDt()
	{
		nID = 0;
		strName = "";
		nHp = 0;
		nMp = 0;
		nAck = 0;
		nDef = 0;
		nPrice = 0;
		nOther = 0;
		strDescription = "";
		strType = "";
		nOverLying = 0;
		nNpcID = 0;
	}
	string strName;
	int nHp;
	int nMp;
	int nAck;
	int nDef;
	int nPrice;
	int nOther;
	string strDescription;
	int nOverLying;
	int nNpcID;
	string strType;
};

class CItemDtMgr :public CDataBaseMgr
{
public:
	CItemDtMgr();
	void loadFile(string strPath);
	void parse(fstream& fromFile);
	vector<CItemDt*> getDataByNpcID(int nNpcID);
	map<string, string> getEquipInfo()
	{
		return m_mapEquipInfo;
	}
private:
	map<string, string> m_mapEquipInfo;
};
class CMonsterDt :public CDataBase
{
public:
	CMonsterDt()
	{
		nID = 0;
		nHp = 0;
		nMp = 0;
		nAck = 0;
		nDef = 0;
		strName = "";
		strPic = "";
		nExp = 0;
		nMoney = 0;
		nItemID = 0;
		nAttackType = 0;
		nMapID = 0;
		nMove = 0;
		nMoveInterval = 0;
		nCountInMap = 0;
	}
	int nHp;
	int nMp;
	int nAck;
	int nDef;
	string strName;
	string strPic;
	int nExp;
	int nMoney;
	int nItemID;
	int nAttackType;
	int nMapID;
	int nMove;
	int nMoveInterval;
	int nCountInMap;
};

class CMonsterDtMgr :public CDataBaseMgr
{
public:
	CMonsterDtMgr();
	void parse(fstream& fromFile);
};

class CPlayerDt :public CDataBase
{
public:
	CPlayerDt() {
		strName = "";
		strPic = "";
		strDescription = "";
		nHp = 0;
		nMp = 0;
		nMoney = 0;
		nAck = 0;
		nDef = 0;
	}
	string strName;
	string strPic;
	string strDescription;
	int nHp;
	int nMp;
	int nMoney;
	int nAck;
	int nDef;
};

class CPlayerDtMgr :public CDataBaseMgr
{
public:
	CPlayerDtMgr();
	void parse(fstream& fromFile);
};