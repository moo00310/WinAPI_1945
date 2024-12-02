#include "pch.h"
#include "Item.h"

void CItem::Initialize()
{
	m_tInfo.fCX = 20;
	m_tInfo.fCY = 20;
	m_fSpeed = 5.f;
	m_fDegree = (float)(rand() % 360 + 1);
	m_uLifeTime = GetTickCount64();
}

int CItem::Update()
{
	if (m_bDead == true)
		return OBJ_DEAD;

	if (m_uLifeTime + 7000 <= GetTickCount64())
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed * cosf(m_fDegree * (PI / 180));
	m_tInfo.fY += -m_fSpeed * sinf(m_fDegree * (PI / 180));

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CItem::Late_Update()
{
	if (WINCX - 50 <= m_tRect.right || 50 >= m_tRect.left)
	{
		m_fDegree -= 90;
	}
	else if (50 >= m_tRect.top || WINCY - 50 <= m_tRect.bottom)
	{
		m_fDegree *= -1.f;
	}
}

void CItem::Release()
{
}



/*------------------
	ItemTypes
-------------------*/

void CBoom::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	swprintf_s(m_szBuf, L"BOOM");
	TextOut(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, m_szBuf, lstrlen(m_szBuf));
}


void CAdd_Attack::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	swprintf_s(m_szBuf, L"ATTACK");
	TextOut(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, m_szBuf, lstrlen(m_szBuf));
}

void Add_Pet::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	swprintf_s(m_szBuf, L"PET");
	TextOut(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, m_szBuf, lstrlen(m_szBuf));
}
