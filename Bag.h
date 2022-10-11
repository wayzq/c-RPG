#pragma once
#include "Item.h"
#include "Define.h"
#include "WndBase.h"
class CBag :public CWndBase
{
public:
	CBag();
	void addItem(CItemDt* data);
	void useItem(CItem* item);
	void changeItemNum(CItem* item, bool bDelete);
	void onUpdate();
	void onRender();
	void onUpdateInBattle();
	void onRenderInBattle();
	SYN_THE_SIZE(int, m_nCurIndex, CurIndex);
	SYN_THE_SIZE(int, m_nCurIndexInBattle, CurIndexInBattle);
private:
	vector<int> m_vecConsumables;
	vector<CItem*> m_vecDatas;
};

