#pragma once
#include"Item.h"
#include <map>
class CEquip
{
public:
	CEquip();
	void init();
	void showEquip();
	CItem* addEquip(string Type, CItem* equip);
private:
	map<string, CItem*> m_mapEquip;
	map<string, string> m_mapInfo;
};

