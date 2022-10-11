#include "RoleBase.h"
CRoleBase::CRoleBase()
{
	m_vPos = CVec2();
	m_nID = 0;
	m_nHp = 0;
	m_nMp = 0;
	m_nAck = 0;
	m_nDef = 0;
	m_strName = "";
	m_strPic = "";
	m_nExp = 0;
	m_nMoney = 0;
	m_nMaxHp = 0;
	m_nMaxMp = 0;
}
void CRoleBase::setPosition(int nX, int nY)
{
	m_vPos.x = nX;
	m_vPos.y = nY;
}

void CRoleBase::onBackUp()
{
	m_vPos.xBk = m_vPos.x;
	m_vPos.yBk = m_vPos.y;
}

void CRoleBase::onRestore()
{
	m_vPos.x = m_vPos.xBk;
	m_vPos.y = m_vPos.yBk;
}

void CRoleBase::onRender()
{
	cout << m_strPic;
}

bool CRoleBase::isEquals(int nX, int nY)
{
	return m_vPos.x == nX && m_vPos.y == nY;
}

bool CRoleBase::onDamage(int Damage)
{
	m_nHp -= Damage;
	return m_nHp > 0;
}
