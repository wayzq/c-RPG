#pragma once
#include "WndBase.h"
#include "Player.h"
#include "Monster.h"
#include "MessageMgr.h"
class CBattle :public CWndBase
{
public:
	CBattle();
	~CBattle();
	CBattle(CPlayer* pPlayer, CMonster* pMonster);
	void Battle();
	void onUpdate();
	void onRender();
	SYN_THE_SIZE( bool, m_bPlayerRound, PlayerRound);
	SYN_THE_SIZE( bool, m_bOperatorBag, OperatorBag);
	SYN_THE_SIZE( int, m_nPlayerAction, PlayerAction);
	SYN_THE_SIZE_READONLY(CMessageMgr*, m_pMessageMgr, MessageMgr);
private:
	CPlayer* m_pFightPlayer;
	CMonster* m_pFightMonster;
};

