#include "pch.h"
#include "Object.h"


CObject::CObject() 
	: m_fSpeed(0.f), m_eDirect(DIR_END),
	m_bDead(false), m_eBullet_Type(BUL_END),
	m_fDistance(0), m_ullLast_Bullet(0), m_bulletCoolDown(0),
	m_fAngle(0), m_pTarget(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CObject::~CObject()
{
}

void CObject::Update_Rect()
{
	m_tRect.left   = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top    = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right  = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

DIRECTION CObject::Get_Direct()
{
	return m_eDirect;
}

void CObject::Set_Direct(DIRECTION eDirect)
{
	m_eDirect = eDirect;
}

bool CObject::Get_Dead()
{
	return m_bDead;
}

void CObject::Set_Dead()
{
	m_bDead = true;
}

bool CObject::Bullet_CoolDown(int CoolDown) // Äð´Ù¿î , ½Ã°£?
{
	if (m_ullLast_Bullet + CoolDown < GetTickCount64())
	{
		m_ullLast_Bullet = GetTickCount64();
		return true;
	}
	else
		return false;
}
