#pragma once
#include"Define.h"
#include"DataStruct.h"
class CItem
{
public:
	CItem();
	CItem(CItemDt* pItemDt);
	void addCount(int sum) {
		m_nCount+=sum;
	}
	SYN_THE_SIZE(int, m_nID, ID);
	SYN_THE_SIZE(string, m_strName, Name);
	SYN_THE_SIZE(int, m_nHp, Hp);
	SYN_THE_SIZE(int, m_nMp, Mp);
	SYN_THE_SIZE(int, m_nAck, Ack);
	SYN_THE_SIZE(int, m_nDef, Def);
	SYN_THE_SIZE(int, m_nPrice, Price);
	SYN_THE_SIZE(string, m_strDescription, Description);
	SYN_THE_SIZE(int, m_nCount, Count);
	SYN_THE_SIZE_READONLY(int, m_nOverLying, OverLying);
	SYN_THE_SIZE_READONLY(string, m_strType, Type);
};

