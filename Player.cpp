#include "Player.h"
#include "Define.h"
CPlayer::CPlayer()
{
	m_vPos.x = 0;
	m_vPos.y = 0;
	m_pBag = new CBag();
	m_pEquip = new CEquip();
	m_strPic = "人";
	m_nHp = 1000;
	m_nMp = 100;
	m_nMoney = 1000;
	m_nAck = 10;
	m_nDef = 10;
	m_nMaxHp = m_nHp;
	m_nMaxMp = m_nMp;
	m_strName = "菜鸟";
	Level = 1;
	LevelNeed = 100;
	Hp = 100;
	Mp = 10;
}

void CPlayer::initWithData(CPlayerDt* pData)
{
	m_strPic = pData->strPic;
	m_nHp = pData->nHp * m_nHp;
	m_nAck = pData->nAck * m_nAck;
	m_nMaxHp = pData->nHp * m_nMaxHp;
	m_nMp = pData->nMp * m_nMp;
	m_nMaxMp = pData->nMp * m_nMp;
	m_strName = pData->strName;
	Hp = pData->nHp * Hp;
	Mp = pData->nMp * Mp;
}

void CPlayer::onUpdate()
{
	while (m_nExp >= LevelNeed)
	{
		m_nExp -= LevelNeed;
		LevelNeed *= 2;
		Level++;
		m_nMaxHp += Hp;
		m_nMaxMp += Mp;
		m_nHp = m_nMaxHp;
		m_nMp = m_nMaxMp;
		g_bClear = true;
	}
	this->onBackUp();
	if (m_nHp > m_nMaxHp)
	{
		m_nHp = m_nMaxHp;
		g_bClear = true;
	}
	if (m_nMp > m_nMaxMp)
	{
		m_nMp = m_nMaxMp;
		g_bClear = true;
	}
	if (KEY_DOWN('W'))
	{
		m_vPos.x--;
	}
	else if (KEY_DOWN('S'))
	{
		m_vPos.x++;
	}
	else if (KEY_DOWN('A'))
	{
		m_vPos.y--;
	}
	else if (KEY_DOWN('D'))
	{
		m_vPos.y++;
	}
}

void CPlayer::showStatus()
{
	cout << "属性" << endl;
	cout << "职业:" << m_strName << endl;
	cout << "等级:" << Level << endl;
	cout << "经验:" << m_nExp << "/" << LevelNeed << endl;
	cout << "血量:" << m_nHp << "/" << m_nMaxHp << endl;
	cout << "蓝量:" << m_nMp << "/" << m_nMaxMp << endl;
	cout << "金钱:" << m_nMoney << endl;
}

int CPlayer::buyItem(CItemDt* itemDt)
{
	if (m_nMoney >= itemDt->nPrice)
	{
		m_nMoney -= itemDt->nPrice;
		m_pBag->addItem(itemDt);
		return 1;
	}
	return 0;
}

