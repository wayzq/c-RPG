#pragma once
#include"Vec2.h"
#include"Define.h"
class CRoleBase
{
public:
	CRoleBase();
	void setPosition(int nX, int nY);
	void onBackUp();
	void onRestore();
	void onRender();
	bool isEquals(int nX, int nY);
	bool onDamage(int Damage);
	SYN_THE_SIZE(CVec2, m_vPos, Position);
	SYN_THE_SIZE(int, m_nID, ID);
	SYN_THE_SIZE(int, m_nHp, Hp);
	SYN_THE_SIZE(int, m_nMp, Mp);
	SYN_THE_SIZE(int, m_nAck, Ack);
	SYN_THE_SIZE(int, m_nDef, Def);
	SYN_THE_SIZE(string, m_strName, Name);
	SYN_THE_SIZE(string, m_strPic, Pic);
	SYN_THE_SIZE(int, m_nExp, Exp);
	SYN_THE_SIZE(int, m_nMoney, Money);
	SYN_THE_SIZE(int, m_nMaxHp, MaxHp);
	SYN_THE_SIZE(int, m_nMaxMp, MaxMp);
};

