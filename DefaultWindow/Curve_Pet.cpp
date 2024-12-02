#include "pch.h"
#include "Curve_Pet.h"

CCurve_Pet::CCurve_Pet() : m_RotAngle(0), m_RotSpeed(0), m_bMove(false)
{
	ZeroMemory(&m_tCenter, sizeof(POINT));
}

CCurve_Pet::~CCurve_Pet()
{
}

void CCurve_Pet::Initialize()
{
	m_tInfo.fCX = 15;
	m_tInfo.fCY = 15;
	m_fSpeed = 2.f;

	m_RotAngle = 0.f;
	m_RotSpeed = 5.f;
	m_fDistance = 40.f;
	m_bulletCoolDown = 1500;

	m_ePetType = CURVE_PET;
}

int CCurve_Pet::Update()
{
	if (m_bDead == true)
		return OBJ_DEAD;

	if (m_bMove == false)
	{
		m_tCenter.x = long(m_tInfo.fX);
		m_tCenter.y = long(m_tInfo.fY);
		m_bMove = true;
	}

	m_tCenter.x += long(m_fSpeed);

	m_RotAngle += m_RotSpeed;

	m_tInfo.fX = float(m_tCenter.x + (m_fDistance * cosf(m_RotAngle * PI / 180.f)));
	m_tInfo.fY = float(m_tCenter.y + (m_fDistance * sinf(m_RotAngle * PI / 180.f)));


	CObject::Update_Rect();

	return 0;
}

void CCurve_Pet::Late_Update()
{
	if (WINCX - 50 < m_tRect.right + 30 || 50 > m_tRect.left - 30)
		m_fSpeed *= -1.f;

	if(Bullet_CoolDown(m_bulletCoolDown))
		Create_Bullet();
}

void CCurve_Pet::Render(HDC hDC)
{
	HPEN newPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HBRUSH newBrush = CreateSolidBrush(RGB(0, 200, 150));
	//HBRUSH newBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HPEN oldPen = (HPEN)SelectObject(hDC, newPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, newBrush);

	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(newBrush);
	DeleteObject(newPen);
}

void CCurve_Pet::Release()
{
}
