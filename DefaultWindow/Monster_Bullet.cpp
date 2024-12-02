#include "pch.h"
#include "Monster_Bullet.h"

CMonster_Bullet::CMonster_Bullet() : m_fDegree(0)//, m_pTarget(nullptr)
{
}

CMonster_Bullet::~CMonster_Bullet()
{
	Release();
}

void CMonster_Bullet::Initialize()
{
	m_tInfo.fCX = 8.f;
	m_tInfo.fCY = 8.f;

	m_fSpeed = 5.f;
}

int CMonster_Bullet::Update()
{
	if (m_bDead == true)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed * cosf(m_fDegree);
	m_tInfo.fY -= m_fSpeed * sinf(m_fDegree);

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster_Bullet::Render(HDC hDC)
{
	HPEN newPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HBRUSH newBrush = CreateSolidBrush(RGB(255, 250, 205));
	//HBRUSH newBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HPEN oldPen = (HPEN)SelectObject(hDC, newPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, newBrush);

	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(newBrush);
	DeleteObject(newPen);
}

void CMonster_Bullet::Release()
{
}

void CMonster_Bullet::Set_Degree(const INFO* _Target)
{
	float fDistance = (float)sqrt(SQUARE(m_tInfo.fX - _Target->fX) + SQUARE(m_tInfo.fY - _Target->fY));

	m_fDegree = acosf((_Target->fX - m_tInfo.fX) / fDistance);

	if (_Target->fY > m_tInfo.fY)
	{
		m_fDegree = (2.f * PI) - m_fDegree;
	}
}