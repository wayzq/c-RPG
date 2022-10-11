#pragma once
#include"Define.h"
#include <vector>
#include "WndBase.h"
#include"DataStruct.h"
class CShop :
	public CWndBase
{
public:
	CShop();
	void onUpdate();
	void onRender();
	void refreshItemDt(int nNpcID);
private:
	vector<CItemDt*> m_vecDatas;
	int m_nState;
	int m_nTime;
	SYN_THE_SIZE(bool, m_bOperatorBag, OperatorBag);
	SYN_THE_SIZE(int, m_nCurIndex, CurIndex);
};

