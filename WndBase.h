#pragma once
#include "Define.h"
#include <string>
using namespace std;
class CWndBase
{
public:
	CWndBase();
	~CWndBase();
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;
	SYN_THE_SIZE(string, m_strName, Name);
	SYN_THE_SIZE(bool, m_bDelete, Delete);
};
