#include "pch.h"
#include "Monster.h"
#include "Monster_Bullet.h"
#include "Monster_Bullet02.h"
#include "AbstractFactory.h"

CMonster::CMonster()
	: m_tCircle(INFO{}), m_iTime(1), m_iVel(1),
	m_pBullet(nullptr), m_pPlINFO(nullptr),
	m_fDegree(0), m_ullframe(0)
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	m_tInfo = { 100.f, 50.f, 30.f, 30.f };
	m_tCircle = { 100.f, 100.f , 20.f , 20.f };
	m_fSpeed = 3.f;
	m_fDistance = 100.f;
	m_bulletCoolDown = 1000;
	m_eBullet_Type = BUL_MON1;
}

int CMonster::Update()
{
	if (m_bDead == true)
		return OBJ_DEAD;


	switch (m_eDirect)
	{
	case UP:
		m_tInfo.fY -= m_fSpeed;
		break;

	case DOWN:
		m_tInfo.fY += m_fSpeed;
		break;

	case LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;

	case RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;

	case LEFTUP:
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY -= m_fSpeed;
		break;

	case LEFTDOWN:
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY += m_fSpeed;
		break;

	case RIGHTUP:
		m_tInfo.fX += m_fSpeed;
		m_tInfo.fY -= m_fSpeed;
		break;

	case RIGHTDOWN:
		m_tInfo.fX += m_fSpeed;
		m_tInfo.fY += m_fSpeed;
		break;
	}

	CulCircle(10);

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
}

void CMonster::Render(HDC hDC)
{
	HPEN newPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HBRUSH newBrush = CreateSolidBrush(RGB(255, 0, 0));
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

void CMonster::Release()
{
}

void CMonster::CulCircle(int _vel)
{
	m_iTime += _vel;

	m_tCircle.fX = Get_Info().fX + (m_fDistance * cosf(m_iTime * (PI / 180.f)));
	m_tCircle.fY = Get_Info().fY + (m_fDistance * sinf(m_iTime * (PI / 180.f)));
}


void CMonster::Create_Bullet()
{
	switch (m_eBullet_Type)
	{
	case BUL_MON1:// 플레이어를 따라가는 총알
		m_pBullet->push_back(CAbstractFactory<CMonster_Bullet>::Create());
		m_pBullet->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		dynamic_cast<CMonster_Bullet*>(m_pBullet->back())->Set_Degree(m_pPlINFO);
		break;
	case BUL_MON2:// 플레이어 주위로 4발
		for (int i = 0; i < 4; ++i)
		{
			m_pBullet->push_back(CAbstractFactory<CMonster_Bullet>::Create());
			m_pBullet->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			dynamic_cast<CMonster_Bullet*>(m_pBullet->back())->Set_Degree(m_pPlINFO);
			dynamic_cast<CMonster_Bullet*>(m_pBullet->back())->ADD_Degree((float)(i * 14 - 21));
		}
		break;
	case BUL_MON3:
		for (int i = 0; i < 360; i += 15)
		{
			m_pBullet->push_back(CAbstractFactory<CMonster_Bullet>::Create());
			m_pBullet->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			dynamic_cast<CMonster_Bullet*>(m_pBullet->back())->Set_Degree((float)(i));
		}
		break;
	case BUL_MON4: 
		m_pBullet->push_back(CAbstractFactory<CMonster_Bullet02>::Create());
		m_pBullet->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		dynamic_cast<CMonster_Bullet02*>(m_pBullet->back())->Set_Degree(m_pPlINFO);

		break;
	default:
		break;
	}
}

void CMonster::Create_Bullet(const float& _Degree)
{
	switch (m_eBullet_Type)
	{
	case BUL_MON1:// 플레이어를 따라가는 총알
		m_pBullet->push_back(CAbstractFactory<CMonster_Bullet>::Create());
		m_pBullet->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		dynamic_cast<CMonster_Bullet*>(m_pBullet->back())->Set_Degree(_Degree);
		break;
	case BUL_MON2:// 플레이어 주위로 4발
		for (int i = 0; i < 4; ++i)
		{
			m_pBullet->push_back(CAbstractFactory<CMonster_Bullet>::Create());
			m_pBullet->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			dynamic_cast<CMonster_Bullet*>(m_pBullet->back())->Set_Degree(_Degree);
			dynamic_cast<CMonster_Bullet*>(m_pBullet->back())->ADD_Degree((float)(i * 14 - 21));
		}
		break;
	case BUL_MON3:
		for (int i = 0; i < 360; i += 15)
		{
			m_pBullet->push_back(CAbstractFactory<CMonster_Bullet>::Create());
			m_pBullet->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			dynamic_cast<CMonster_Bullet*>(m_pBullet->back())->Set_Degree((float)(i));
		}
		break;
	default:
		break;
	}
}

void CMonster::Atk_Pattern1()
{
	for (int i = 0; i < 4; ++i)
	{
		m_pBullet->push_back(CAbstractFactory<CMonster_Bullet>::Create());
		m_pBullet->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		dynamic_cast<CMonster_Bullet*>(m_pBullet->back())->Set_Degree(m_fDegree + i * 91);
	}
	m_fDegree += 10;
}

void CMonster::Atk_Pattern2()
{
	if (m_ullframe + 150 < GetTickCount64())
	{
		for (int i = 0 + rand() % 15; i < 360; i += 15)
		{
			m_pBullet->push_back(CAbstractFactory<CMonster_Bullet>::Create());
			m_pBullet->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
			dynamic_cast<CMonster_Bullet*>(m_pBullet->back())->Set_Degree((float)(i));
		}
		m_ullframe = GetTickCount64();
	}

}
