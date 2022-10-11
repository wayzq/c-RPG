#include "Battle.h"
#include "GameMgr.h"
//#include "GameMap.h"
#include <string>
CBattle::CBattle()
{
	m_pFightMonster = nullptr;
	m_pFightPlayer = nullptr;
	m_bPlayerRound = true;
	m_nPlayerAction = E_ACTION_NONE;
	m_pMessageMgr = new CMessageMgr();
	m_bOperatorBag = false;
}

CBattle::~CBattle()
{
	SAFE_DEL(m_pFightMonster);
	SAFE_DEL(m_pFightPlayer);
	SAFE_DEL(m_pMessageMgr);
}

CBattle::CBattle(CPlayer* pPlayer, CMonster* pMonster)
{
	m_pFightMonster = pMonster;
	m_pFightPlayer = pPlayer;
	m_bPlayerRound = true;
	m_nPlayerAction = E_ACTION_BATTLE;
	m_pMessageMgr = new CMessageMgr();
	m_bOperatorBag = false;
	string message = "你遇到了" + pMonster->getName();
	m_pMessageMgr->addMessage(message);
}

void CBattle::Battle()
{
	if (m_bPlayerRound && !m_bOperatorBag)
	{
		if (KEY_DOWN('A'))
		{
			m_nPlayerAction--;
			if (m_nPlayerAction < 1)
			{
				m_nPlayerAction = 1;
			}
		}
		else if (KEY_DOWN('D'))
		{
			m_nPlayerAction++;
			if (m_nPlayerAction > 3)
			{
				m_nPlayerAction = 3;
			}
		}
		else if (KEY_DOWN('F'))
		{
			m_bOperatorBag = false;
			g_bClear = true;
			if (m_nPlayerAction == E_ACTION_BATTLE)
			{
				int damage = m_pFightPlayer->getAck() > m_pFightMonster->getDef() ? (m_pFightPlayer->getAck() - m_pFightMonster->getDef()) : 1;
				m_pFightMonster->onDamage(damage);
				string message = m_pFightPlayer->getName() + "打了" + m_pFightMonster->getName() + to_string(damage) + "血";
				m_pMessageMgr->addMessage(message);
				m_bPlayerRound = !m_bPlayerRound;
				m_nPlayerAction = E_ACTION_NONE;
			}
			else if (m_nPlayerAction == E_ACTION_ITEM)
			{
				m_bOperatorBag = true;
				m_nPlayerAction = E_ACTION_NONE;
			}
			else {
				CGameMgr::getInstance()->restoreWnd();
				g_bClear = true;
				return;
			}
		}
	}
	else if (!m_bPlayerRound) {
		int damage = m_pFightMonster->getAck() > m_pFightPlayer->getDef() ? (m_pFightMonster->getAck() - m_pFightPlayer->getDef()) : 1;
		m_pFightPlayer->onDamage(damage);
		string message = m_pFightPlayer->getName() + "被" + m_pFightMonster->getName() + "打了" + to_string(damage) + "血";
		m_pMessageMgr->addMessage(message);
		m_bPlayerRound = !m_bPlayerRound;
		m_nPlayerAction = E_ACTION_BATTLE;
	}
}

void CBattle::onUpdate()
{
	if (m_pFightPlayer->getHp() <= 0)
	{
		exit(0);
		return;
	}
	if (m_pFightMonster->getHp() <= 0)
	{
		m_pFightPlayer->setExp(m_pFightMonster->getExp() + m_pFightPlayer->getExp());
		m_pFightPlayer->setMoney(1 + rand() % (m_pFightMonster->getMoney()) + m_pFightPlayer->getMoney());
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getMonsterMgr()->deleteMonster(m_pFightMonster);
		CGameMgr::getInstance()->restoreWnd();
		g_bClear = true;
		return;
	}
	m_pMessageMgr->onUpdate();
	Battle();
	if (m_bOperatorBag)
	{
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getBag()->onUpdateInBattle();
	}
	if (KEY_DOWN(VK_ESCAPE) && m_bOperatorBag)
	{
		m_bOperatorBag = false;
		m_nPlayerAction = E_ACTION_ITEM;
		g_bClear = true;
	}
}

void CBattle::onRender()
{
	cout << "怪物" << endl;
	cout << "名  字：" << m_pFightMonster->getName() << endl;
	cout << "血  量：" << m_pFightMonster->getHp() << "       " << endl;
	cout << "蓝  量：" << m_pFightMonster->getMp() << "       " << endl;
	cout << "攻击力：" << m_pFightMonster->getAck() << endl;
	cout << "防御力：" << m_pFightMonster->getDef() << endl;
	cout << "信息栏:" << endl;
	m_pMessageMgr->onRender();
	cout << "玩家" << endl;
	cout << "职  业：" << m_pFightPlayer->getName() << endl;
	cout << "血  量：" << m_pFightPlayer->getHp() << "/" << m_pFightPlayer->getMaxHp() << "       " << endl;
	cout << "蓝  量：" << m_pFightPlayer->getMp() << "/" << m_pFightPlayer->getMaxMp() << "       " << endl;
	cout << "攻击力：" << m_pFightPlayer->getAck() << endl;
	cout << "防御力：" << m_pFightPlayer->getDef() << endl;
	if (m_nPlayerAction == E_ACTION_NONE)
	{
		cout << "  战斗" << "    " << "  道具" << "    " << "  逃跑";
	}
	else if (m_nPlayerAction == E_ACTION_BATTLE)
	{
		cout << "->战斗" << "    " << "  道具" << "    " << "  逃跑";
	}
	else if (m_nPlayerAction == E_ACTION_ITEM)
	{
		cout << "  战斗" << "    " << "->道具" << "    " << "  逃跑";
	}
	else if (m_nPlayerAction == E_ACTION_RUN)
	{
		cout << "  战斗" << "    " << "  道具" << "    " << "->逃跑";
	}
	cout << endl;
	if (m_bOperatorBag)
	{
		CGameMgr::getInstance()->getWndByName<CGameMap>("GameMap")->getPlayer()->getBag()->onRenderInBattle();
	}
}
