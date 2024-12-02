#include "pch.h"
#include "MonsterCircle.h"

CMonsterCircle::CMonsterCircle() 
	: m_iDistance(50), m_tCircle(INFO{}),
	m_iTime(1), m_iVel(5),
	m_iAddX(1), m_iAddY(1),
	m_iBulCount(0), m_bisBulletToPl(false)
{
}

CMonsterCircle::~CMonsterCircle()
{
	Release();
}

void CMonsterCircle::Initialize()
{
	m_tCircle = { 100.f, 100.f , 20.f , 20.f };
}

int CMonsterCircle::Update()
{
	if (m_bDead == true)
		return OBJ_DEAD;

	//회전구현함수(속도)
	CulCircle(m_iVel);
	if (m_iBulCount < 10 && Bullet_CoolDown(m_bulletCoolDown))
	{
		if (m_bisBulletToPl)
			Create_Bullet();
		else
			Create_Bullet(float(rand() % 360));
		m_iBulCount++;
	}

	return OBJ_NOEVENT;
}

void CMonsterCircle::Late_Update()
{
}

void CMonsterCircle::Render(HDC hDC)
{
	//중심점 이동함수
	AddPos(m_iAddX, m_iAddY);

	HPEN newPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HBRUSH newBrush = CreateSolidBrush(RGB(200, 0, 0));
	//HBRUSH newBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HPEN oldPen = (HPEN)SelectObject(hDC, newPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, newBrush);

	//서클렌더
	Ellipse(hDC,
		int(m_tCircle.fX - m_tCircle.fCX),
		int(m_tCircle.fY - m_tCircle.fCY),
		int(m_tCircle.fX + m_tCircle.fCY),
		int(m_tCircle.fY + m_tCircle.fCY));

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(newBrush);
	DeleteObject(newPen);
}

void CMonsterCircle::Release()
{
}

void CMonsterCircle::CulCircle(int _vel)
{
	//회전속도
	m_iTime += _vel;

	//디그리 계산
	m_tCircle.fX = Get_Info().fX + (m_iDistance * cosf(m_iTime * (PI / 180.f)));
	m_tCircle.fY = Get_Info().fY + (m_iDistance * sinf(m_iTime * (PI / 180.f)));
}