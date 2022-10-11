#pragma once
#include "Vec2.h"
#include "Bag.h"
#include "Equip.h"
#include "RoleBase.h"
class CPlayer :public CRoleBase
{
public:
	CPlayer();
	void initWithData(CPlayerDt* pData);
	int buyItem(CItemDt* itemDt);
	void showStatus();
	void onUpdate();
	SYN_THE_SIZE_READONLY(CBag*, m_pBag, Bag);
	SYN_THE_SIZE_READONLY(CEquip*, m_pEquip, Equip);
	SYN_THE_SIZE(int, m_nMoney, Money);
	SYN_THE_SIZE(int, Level, Level);
private:
	int LevelNeed;
	int Hp;
	int Mp;
};

