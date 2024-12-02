#include "pch.h"
#include "MonsterDown.h"

CMonsterDown::CMonsterDown()
{
}

CMonsterDown::~CMonsterDown()
{
}

int CMonsterDown::Update()
{
	if (m_bDead == true)
		return OBJ_DEAD;
	
	if (Bullet_CoolDown(m_bulletCoolDown))
		Create_Bullet();

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


	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonsterDown::Late_Update()
{
}

void CMonsterDown::Release()
{
}
