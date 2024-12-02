#include "pch.h"
#include "Pet_Bullet.h"

CPet_Bullet::CPet_Bullet() : m_pTarget(nullptr)
{
}

CPet_Bullet::~CPet_Bullet()
{
	Release();
}

void CPet_Bullet::Initialize()
{

	m_fAngle = 0.5f * PI;
	m_tInfo.fCX = 3.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 50.f;
}

int CPet_Bullet::Update()
{
	if (m_bDead == true)
		return OBJ_DEAD;

	//Set_Degree(m_pTarget);
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle);

	__super::Update_Rect();

	Update_Polygon();

	return OBJ_NOEVENT;
}
void CPet_Bullet::Render(HDC hDC)
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

void CPet_Bullet::Release()
{
}

void CPet_Bullet::Update_Polygon()
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
		m_pPoints[i].x = int(cosf(0.5f * PI - m_fAngle) * vertices[i].x - sinf(0.5f * PI - m_fAngle) * vertices[i].y + m_tInfo.fX);
		m_pPoints[i].y = int(sinf(0.5f * PI - m_fAngle) * vertices[i].x + cosf(0.5f * PI - m_fAngle) * vertices[i].y + m_tInfo.fY);
	}
}

void CPet_Bullet::Set_Degree(const INFO* _Target)
{
	if (_Target == nullptr)
	{
		m_fAngle = 0.5f * PI;
		m_pTarget = _Target;
		return;
	}
	float fDistance = (float)sqrt(SQUARE(m_tInfo.fX - _Target->fX) + SQUARE(m_tInfo.fY - _Target->fY));

	m_fAngle = acosf((_Target->fX - m_tInfo.fX) / fDistance);

	if (_Target->fY > m_tInfo.fY)
	{
		m_fAngle = (2.f * PI) - m_fAngle;
	}
	m_pTarget = _Target;
}

