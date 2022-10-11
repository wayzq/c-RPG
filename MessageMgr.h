#pragma once
#include"Define.h"
class CMessageMgr
{
public:
	CMessageMgr();
	void onUpdate();
	void onRender();
	void addMessage(string message);
	SYN_THE_SIZE(vector<string>, m_vecMessages, Messages);
private:
	int messageNum;
};

