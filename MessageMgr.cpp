#include "MessageMgr.h"

CMessageMgr::CMessageMgr()
{
	messageNum = 5;
}

void CMessageMgr::onUpdate()
{
	messageNum = 5;
}

void CMessageMgr::onRender()
{
	for (int i = m_vecMessages.size() - 1; i >= 0; i--)
	{
		cout << m_vecMessages[i] << endl;
		messageNum--;
	}
	while (messageNum--) {
		cout << endl;
	}
}

void CMessageMgr::addMessage(string message)
{
	m_vecMessages.push_back(message);
	if (m_vecMessages.size()>messageNum)
	{
		m_vecMessages.erase(m_vecMessages.begin());
	}
	g_bClear = true;
}
