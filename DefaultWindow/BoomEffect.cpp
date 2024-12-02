#include "pch.h"
#include "BoomEffect.h"
#include "AbstractFactory.h"
#include "Player_Bullet.h"

CBoomEffect::CBoomEffect(BOOMTYPE _eBoomType) : m_eBoomType(_eBoomType), m_uTime(0)
{
}

CBoomEffect::~CBoomEffect()
{
}

void CBoomEffect::Release()
{
}

/*-------------------
	CircleBoom
--------------------------*/
void CBoomCricle::Initialize()
{
	m_tInfo = { 100, 100.f, 100.f, 100.f };
	m_fSpeed = 4.f;
}

int CBoomCricle::Update()
{
	if (m_bDead == true) return OBJ_DEAD;

	m_tInfo.fCX += (float)m_fSpeed;
	m_tInfo.fCY += (float)m_fSpeed;

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBoomCricle::Late_Update()
{
	if (m_tInfo.fCX >= 500)
		m_bDead = true;
}

void CBoomCricle::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

/*-------------------
	PlaneBoom
--------------------------*/

void CBoomPlane::Initialize()
{
	m_tInfo.fY = 200.f;
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 400.f;
	m_fSpeed = 5.f;
}

int CBoomPlane::Update()
{
	if (m_bDead == true) return OBJ_DEAD;

	m_tInfo.fY += -m_fSpeed;

	if (m_uTime + 100 <= GetTickCount64())
	{
		m_bulletList->push_back(CAbstractFactory<BoomBullet>::Create(m_tInfo.fX, m_tInfo.fY, 0.f));
		m_bulletList->push_back(CAbstractFactory<BoomBullet>::Create(m_tInfo.fX, m_tInfo.fY, 180.f));

		m_bulletList->push_back(CAbstractFactory<BoomBullet>::Create(m_tInfo.fX, m_tInfo.fY - 100.f, 0.f));
		m_bulletList->push_back(CAbstractFactory<BoomBullet>::Create(m_tInfo.fX, m_tInfo.fY - 100.f, 180.f));

		m_bulletList->push_back(CAbstractFactory<BoomBullet>::Create(m_tInfo.fX, m_tInfo.fY + 100.f, 0.f));
		m_bulletList->push_back(CAbstractFactory<BoomBullet>::Create(m_tInfo.fX, m_tInfo.fY + 100.f, 180.f));

		m_uTime = GetTickCount64();
	}

	CObject::Update_Rect();
	return OBJ_NOEVENT;
}

void CBoomPlane::Late_Update()
{
	if (m_tInfo.fY <= -200)
		m_bDead = true;
}

void CBoomPlane::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}
