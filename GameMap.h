#pragma once
#include "DataStruct.h"
#include "Player.h"
#include "NpcMgr.h"
#include"MonsterMgr.h"
#include "Define.h"
class CGameMap :public CWndBase
{
public:
	CGameMap();
	~CGameMap();
	void onUpdate();
	void onRender();
	SYN_THE_SIZE_READONLY(CMapDt*, m_pCurMapDt, CurMap);
	SYN_THE_SIZE_READONLY(CPlayer*, m_pPlayer, Player);
	SYN_THE_SIZE_READONLY(CMonsterMgr*, m_pMonsterMgr, MonsterMgr);
	SYN_THE_SIZE_READONLY(CNpcMgr*, m_pNpcMgr, NpcMgr);
};

