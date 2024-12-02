#include "pch.h"
#include "Pet.h"
#include "AbstractFactory.h"
#include "Player_Bullet.h"

CPet::CPet() : m_ePetType(PET_END), m_pPetBullet(nullptr)
{
}

CPet::~CPet()
{
}

void CPet::Create_Bullet()
{
	m_pPetBullet->push_back(CAbstractFactory<CPlayer_Bullet>::Create(m_tInfo.fX, m_tInfo.fY));
}

void CPet::Create_Missile()
{
	m_pPetBullet->push_back(CAbstractFactory<CPet_Bullet>::Create(m_tInfo.fX, m_tInfo.fY));
	dynamic_cast<CPet_Bullet*>(m_pPetBullet->back())->Set_Degree(Search_Immediate_Enemy_INFO());
}

PET_TYPE CPet::Get_Type()
{
	return m_ePetType;
}

INFO* CPet::Search_Immediate_Enemy_INFO()
{
	INFO* pReturn(nullptr);
	float MinDis(0.f);
	float CerrentDis(0.f);

	for (auto Iter = m_pMob->begin();
		Iter != m_pMob->end();
		++Iter)
	{
		CerrentDis = (m_tInfo.fX - (*Iter)->Get_Info().fX) * (m_tInfo.fX - (*Iter)->Get_Info().fX)
			+ (m_tInfo.fY - (*Iter)->Get_Info().fY) * (m_tInfo.fY - (*Iter)->Get_Info().fY); // 비교에는 sqrt 필요없으니까 생략

		if (MinDis == 0.f || CerrentDis < MinDis) // 최소거리 갱신
		{
			MinDis = CerrentDis;
			pReturn = (*Iter)->Get_pInfo();
		}
	}

	return pReturn; // 몬스터가 없으면 nullptr 반환
}
