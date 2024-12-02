#include "pch.h"
#include "Bullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Late_Update()
{
	if (WINCX - 50 < m_tRect.right || 50 > m_tRect.left ||
		50 > m_tRect.top || WINCY - 50 < m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CBullet::Release()
{
}

/*--------------
	BOOM_Bullet
-----------------*/

void BoomBullet::Initialize()
{
	m_tInfo = { 0, 0, 20,20 };
	m_fSpeed = 5.f;
}

int BoomBullet::Update()
{
	if (m_bDead == true) return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180));
	m_tInfo.fY += m_fSpeed * sinf(m_fAngle * (PI / 180));

	__super::Update_Rect();
	return OBJ_NOEVENT;
}


void BoomBullet::Release()
{
}