#include "Item.h"

CItem::CItem()
{
	m_nID = 0;
	m_strName = "";
	m_nHp = 0;
	m_nMp = 0;
	m_nAck = 0;
	m_nDef = 0;
	m_nPrice = 0;
	m_strDescription = "";
	m_strType = "";
	m_nCount = 0;
}

CItem::CItem(CItemDt* pItemDt)
{
	m_nID = pItemDt->nID;
	m_nHp = pItemDt->nHp;
	m_nMp = pItemDt->nMp;
	m_nAck = pItemDt->nAck;
	m_nDef = pItemDt->nDef;
	m_strName = pItemDt->strName;
	m_strDescription = pItemDt->strDescription;
	m_nPrice = pItemDt->nPrice;
	m_nOverLying = pItemDt->nOverLying;
	m_strType = pItemDt->strType;
	m_nCount = 1;
}
