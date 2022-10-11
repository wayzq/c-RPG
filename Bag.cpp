#include "Bag.h"
#include "GameMgr.h"
#include "Define.h"
#include<iomanip>
#include "Battle.h"
CBag::CBag()
{
	m_nCurIndex = 0;
	m_nCurIndexInBattle = 0;
	m_bDelete = false;
}

void CBag::addItem(CItemDt* data)
{
	if (data->nOverLying == 0)
	{
		for (CItem* item : m_vecDatas) {
			if (data->nID == item->getID())
			{
				item->addCount(1);
				return;
			}
		}
	}
	CItem* pItem = new CItem(data);
	m_vecDatas.push_back(pItem);
}

void CBag::useItem(CItem* item)
{
	CPlayer* player = CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer();
	string strType = item->getType();
	if (CGameMgr::getInstance()->getCurWnd()->getName() == "Shop")
	{
		player->setMoney(player->getMoney() + (item->getPrice() >> 1));
		changeItemNum(item, true);
		return;
	}
	if ("hand" == strType || "body" == strType || "head" == strType || "foot" == strType)
	{
		CItem* equip = player->getEquip()->addEquip(item->getType(), item);
		if (equip)
		{
			m_vecDatas[m_nCurIndex] = equip;
		}
		else {
			changeItemNum(item, false);
			return;
		}
	}
	else if ("consumables" == strType)
	{
		player->setAck(player->getAck() + item->getAck());
		player->setDef(player->getDef() + item->getDef());
		int Hp = (player->getHp() + item->getHp()) > player->getMaxHp() ? player->getMaxHp() : (player->getHp() + item->getHp());
		player->setHp(Hp);
		int Mp = (player->getMp() + item->getMp()) > player->getMaxMp() ? player->getMaxMp() : (player->getMp() + item->getMp());
		player->setMp(Mp);
		if (CGameMgr::getInstance()->getCurWnd()->getName() == "Battle")
		{
			string message = player->getName() + "使用了" + item->getName();
			CGameMgr::getInstance()->getWndByName<CBattle>("Battle")->getMessageMgr()->addMessage(message);
		}
		changeItemNum(item, true);
		return;
	}
}

void CBag::changeItemNum(CItem* item, bool bDelete)
{
	if (item->getCount() > 1)
	{
		item->addCount(-1);
	}
	else {
		m_vecDatas.erase(m_vecDatas.begin() + m_nCurIndex--);
		m_nCurIndex = m_nCurIndex < 0 ? 0 : m_nCurIndex;
		if (bDelete)
		{
			SAFE_DEL(item);
		}
	}
}

void CBag::onUpdate()
{
	if (KEY_DOWN(VK_ESCAPE))
	{
		m_nCurIndex = 0;
		CGameMgr::getInstance()->restoreWnd();
		g_bClear = true;
		return;
	}
	if (m_vecDatas.empty())
	{
		return;
	}
	if (KEY_DOWN('W'))
	{
		m_nCurIndex--;
		m_nCurIndex = m_nCurIndex < 0 ? 0 : m_nCurIndex;
		g_bClear = true;
	}
	else if (KEY_DOWN('S'))
	{
		m_nCurIndex++;
		m_nCurIndex = m_nCurIndex < m_vecDatas.size() ? m_nCurIndex : m_vecDatas.size() - 1;
		g_bClear = true;
	}
	else if (KEY_DOWN(VK_RETURN)) {
		g_bClear = true;
		useItem(m_vecDatas[m_nCurIndex]);
	}
}

void CBag::onRender()
{
	cout << "  物品\t\t血量\t蓝量\t攻击力\t防御力\t售价\t数量\t描述" << endl;
	for (int i = 0; i < m_vecDatas.size(); i++)
	{
		if (m_nCurIndex == i && (CGameMgr::getInstance()->getWndByName<CShop>("Shop") &&
			CGameMgr::getInstance()->getWndByName<CShop>("Shop")->getOperatorBag() || CGameMgr::getInstance()->getCurWnd()->getName() == "Bag"))
		{
			cout << "->";
		}
		else {
			cout << "  ";
		}
		cout << setiosflags(ios::left) << setw(6) << m_vecDatas[i]->getName() << "\t"
			<< m_vecDatas[i]->getHp() << "\t"
			<< m_vecDatas[i]->getMp() << "\t"
			<< m_vecDatas[i]->getAck() << "\t"
			<< m_vecDatas[i]->getDef() << "\t"
			<< (m_vecDatas[i]->getPrice() >> 1) << "\t"
			<< m_vecDatas[i]->getCount() << "\t";
		if (m_nCurIndex == i)
		{
			cout << m_vecDatas[i]->getDescription();
		}
		cout << endl;
	}
	cout << endl;
	if (CGameMgr::getInstance()->getCurWnd()->getName() == "Bag")
	{
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getEquip()->showEquip();
	}
}

void CBag::onUpdateInBattle()
{
	m_vecConsumables.clear();
	if (m_vecDatas.empty()) {
		return;
	}
	for (int i = 0; i < m_vecDatas.size(); i++)
	{
		if (m_vecDatas[i]->getType() == "consumables")
		{
			m_vecConsumables.push_back(i);
		}
	}
	if (m_vecConsumables.empty())
	{
		return;
	}
	if (KEY_DOWN('W'))
	{
		m_nCurIndexInBattle--;
		m_nCurIndexInBattle = m_nCurIndexInBattle < 0 ? 0 : m_nCurIndexInBattle;
	}
	else if (KEY_DOWN('S'))
	{
		m_nCurIndexInBattle++;
		m_nCurIndexInBattle = m_nCurIndexInBattle < m_vecConsumables.size() ? m_nCurIndexInBattle : m_vecConsumables.size() - 1;
	}
	m_nCurIndex = m_vecConsumables[m_nCurIndexInBattle];
	if (KEY_DOWN(VK_RETURN))
	{
		g_bClear = true;
		useItem(m_vecDatas[m_nCurIndex]);
		m_nCurIndexInBattle = 0;
		CGameMgr::getInstance()->getWndByName<CBattle>("Battle")->setPlayerRound(false);
		CGameMgr::getInstance()->getWndByName<CBattle>("Battle")->setOperatorBag(false);
	}
}

void CBag::onRenderInBattle()
{
	cout << "  物品\t\t血量\t蓝量\t攻击力\t防御力\t数量" << endl;
	if (m_vecConsumables.empty() /*|| m_vecDatas.empty()*/)
	{
		return;
	}
	for (int i = 0; i < m_vecConsumables.size(); i++)
	{
		if (m_nCurIndex == m_vecConsumables[i])
		{
			cout << "->";
		}
		else {
			cout << "  ";
		}
		cout << setiosflags(ios::left) << setw(6) << m_vecDatas[m_vecConsumables[i]]->getName() << "\t"
			<< m_vecDatas[m_vecConsumables[i]]->getHp() << "\t"
			<< m_vecDatas[m_vecConsumables[i]]->getMp() << "\t"
			<< m_vecDatas[m_vecConsumables[i]]->getAck() << "\t"
			<< m_vecDatas[m_vecConsumables[i]]->getDef() << "\t"
			<< m_vecDatas[m_vecConsumables[i]]->getCount() << "\t";
		cout << endl;
	}
}
