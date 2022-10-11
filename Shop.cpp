#include "Shop.h"
#include "Define.h"
#include "GameMgr.h"
#include "DataMgr.h"
#include<iomanip>
CShop::CShop()
{
	m_nCurIndex = 0;
	m_bOperatorBag = false;
	m_nState = E_SHOP_IDLE;
	m_nTime = 0;
}

void CShop::onUpdate()
{
	m_nTime++;
	if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->restoreWnd();
		g_bClear = true;
		return;
	}
	if (KEY_DOWN(VK_SPACE))
	{
		m_bOperatorBag = !m_bOperatorBag;
	}
	if (m_bOperatorBag)
	{
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getBag()->onUpdate();
		return;
	}
	else {
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
		if (KEY_DOWN(VK_RETURN))
		{
			m_nState = CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->buyItem(m_vecDatas[m_nCurIndex]);
			m_nTime = 0;
			g_bClear = true;
		}
	}
	if (m_nTime > 10)
	{
		m_nState = E_SHOP_IDLE;
	}
}

void CShop::onRender()
{ 
	cout << "  物品\t\t血量\t蓝量\t攻击力\t防御力\t售价\t描述" << endl;
	for (int i = 0; i < m_vecDatas.size(); i++)
	{
		if (m_nCurIndex == i&& !m_bOperatorBag)
		{
			cout << "->";
		}
		else {
			cout << "  ";
		}
		cout << setiosflags(ios::left) << setw(6) << m_vecDatas[i]->strName << "\t"
			<< m_vecDatas[i]->nHp << "\t"
			<< m_vecDatas[i]->nMp << "\t"
			<< m_vecDatas[i]->nAck << "\t"
			<< m_vecDatas[i]->nDef << "\t"
			<< m_vecDatas[i]->nPrice << "\t";
		if (m_nCurIndex == i)
		{
			cout << m_vecDatas[i]->strDescription;
		}
		cout << endl;
	}
	if (m_nState == E_SHOP_IDLE)
	{
		cout << "              ";
	}
	else if (m_nState)
	{
		cout << "购买成功";
	}
	else {
		cout << "余额不足";
	}
	cout << endl;
	CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getBag()->onRender();
	cout << "你的米:" << CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getMoney();
}

void CShop::refreshItemDt(int nNpcID)
{
	m_vecDatas = CDataMgr::getInstance()->getMgr<CItemDtMgr>("ItemDtMgr")->getDataByNpcID(nNpcID);
	m_nCurIndex = 0;
	CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getBag()->setCurIndex(0);
}
