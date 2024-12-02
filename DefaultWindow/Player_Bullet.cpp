#include "pch.h"
#include "Player_Bullet.h"

CPlayer_Bullet::CPlayer_Bullet() : m_eDir(UP)
{
}

CPlayer_Bullet::~CPlayer_Bullet()
{
	Release();
}

void CPlayer_Bullet::Initialize()
{
	m_fAngle = 0.5f * PI;
	m_tInfo.fCX = 4.f;
	m_tInfo.fCY = 25.f;

	m_fSpeed = 13.f;
}

int CPlayer_Bullet::Update()
{
	if (m_bDead == true)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle);

	__super::Update_Rect();

	return OBJ_NOEVENT;

}

void CPlayer_Bullet::Render(HDC hDC)
{
	HPEN newPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HBRUSH newBrush = CreateSolidBrush(RGB(0, 209, 206));
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

void CPlayer_Bullet::Release()
{
}

void CPlayer_Bullet::Set_Dir(const DIRECTION& _Dir)
{
	switch (_Dir)
	{
	case RIGHT:
		m_fAngle = 80.f * PI / 180.f;
		break;
	case LEFT:
		m_fAngle = 100.f * PI / 180.f;
		break;
	default:
		m_fAngle = 90.f * PI / 180.f;
	}
}
