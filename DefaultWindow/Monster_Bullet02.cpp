#include "pch.h"
#include "Monster_Bullet02.h"

CMonster_Bullet02::CMonster_Bullet02()
{
}

CMonster_Bullet02::~CMonster_Bullet02()
{
	Release();
}

void CMonster_Bullet02::Initialize()
{
	m_tInfo.fCX = 3.f;
	m_tInfo.fCY = 35.f;

	m_fSpeed = 2.f;
	m_ullTime = GetTickCount64();
	m_fAngle = (rand() % 360) * (PI / 180.f);
	m_fDegree = 90.f * (PI / 180.f);
}

int CMonster_Bullet02::Update()
{
	m_ullTime;
	if (m_bDead == true)
		return OBJ_DEAD;

	if (m_ullTime + 600 > GetTickCount64())
	{
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle);
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle);
	}
	else if (m_ullTime + 650 > GetTickCount64())
	{
		m_fSpeed = 13.f;
		Set_Degree(m_pTarget);
	}
	else
	{
		m_fSpeed += 1.f;
		m_tInfo.fX += m_fSpeed * cosf(m_fDegree);
		m_tInfo.fY -= m_fSpeed * sinf(m_fDegree);
	}

	Update_Polygon();
	__super::Update_Rect();
	return OBJ_NOEVENT;

}

void CMonster_Bullet02::Render(HDC hDC)
{
	HPEN newPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HBRUSH newBrush = CreateSolidBrush(RGB(255, 0, 0));
	//HBRUSH newBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HPEN oldPen = (HPEN)SelectObject(hDC, newPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, newBrush);

	Polygon(hDC, m_pPoints, 4);

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(newBrush);
	DeleteObject(newPen);
}

void CMonster_Bullet02::Release()
{
}

void CMonster_Bullet02::Update_Polygon()
{
	float halfWidth = Get_Info().fCX / 2;
	float halfHeight = Get_Info().fCY / 2;

	// 각 꼭짓점 계산 (사각형의 중심 기준 상대 위치)
	POINT vertices[4] = {
		{int(-halfWidth), int(-halfHeight)},
		{int(halfWidth), int(-halfHeight)},
		{int(halfWidth), int(halfHeight)},
		{int(-halfWidth), int(halfHeight)}
	};

	// 회전 변환 계산
	for (int i = 0; i < 4; i++)
	{
		m_pPoints[i].x = int(cosf(0.5f * PI - m_fDegree) * vertices[i].x - sinf(0.5f * PI - m_fDegree) * vertices[i].y + m_tInfo.fX);
		m_pPoints[i].y = int(sinf(0.5f * PI - m_fDegree) * vertices[i].x + cosf(0.5f * PI - m_fDegree) * vertices[i].y + m_tInfo.fY);
	}
}

void CMonster_Bullet02::Set_Degree(const INFO* _Target)
{
	m_pTarget = _Target;
	float fDistance = (float)sqrt(SQUARE(m_tInfo.fX - m_pTarget->fX) + SQUARE(m_tInfo.fY - m_pTarget->fY));

	m_fDegree = acosf((m_pTarget->fX - m_tInfo.fX) / fDistance);

	if (m_pTarget->fY > m_tInfo.fY)
	{
		m_fDegree = (2.f * PI) - m_fDegree;
	}
}
