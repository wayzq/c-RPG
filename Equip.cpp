#include "Equip.h"
#include"DataMgr.h"
#include "GameMgr.h"
CEquip::CEquip()
{
	this->init();
}

void CEquip::init()
{
	m_mapEquip["head"] = nullptr;
	m_mapEquip["hand"] = nullptr;
	m_mapEquip["body"] = nullptr;
	m_mapEquip["foot"] = nullptr;
	m_mapInfo = CDataMgr::getInstance()->getMgr<CItemDtMgr>("ItemDtMgr")->getEquipInfo();
}

void CEquip::showEquip()
{
	cout << "×°±¸À¸" << endl;
	for (map<string, string>::iterator iter = m_mapInfo.begin(); iter != m_mapInfo.end(); iter++)
	{
		cout << iter->second << ":";
		string strInfo = m_mapEquip[iter->first] ? m_mapEquip[iter->first]->getName() : "ÎÞ";
		cout << strInfo << endl;
	}
}

CItem* CEquip::addEquip(string Type, CItem* equip)
{
	CPlayer* player = CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer();
	int nCount = m_mapInfo.count(Type);
	if (nCount == 0)
	{
		return nullptr;
	}
	if (!m_mapEquip[Type])
	{
		m_mapEquip[Type] = equip;
		player->setAck(player->getAck() + equip->getAck());
		player->setDef(player->getDef() + equip->getDef());
		player->setMaxHp(player->getMaxHp() + equip->getHp());
		player->setMaxMp(player->getMaxMp() + equip->getMp());

		return nullptr;
	}
	CItem* tempEquip = m_mapEquip[Type];
	m_mapEquip[Type] = equip;
	player->setAck(player->getAck() + equip->getAck() - tempEquip->getAck());
	player->setDef(player->getDef() + equip->getDef() - tempEquip->getDef());
	player->setMaxHp(player->getMaxHp() + equip->getHp() - tempEquip->getHp());
	player->setMaxMp(player->getMaxMp() + equip->getMp() - tempEquip->getMp());
	return tempEquip;
}
