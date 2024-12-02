#include "pch.h"
#include "Rotation_Pet.h"

CRotation_Pet::CRotation_Pet() : m_fPetAngle(0)
{
}

CRotation_Pet::~CRotation_Pet()
{
}

void CRotation_Pet::Initialize()
{
    m_tInfo.fCX = 15;
    m_tInfo.fCY = 15;
    m_fSpeed = 3.f;
    m_fDistance = 100.f;
    m_bulletCoolDown = 1500;
    m_ePetType = ROT_PET;
}

int CRotation_Pet::Update()
{
    if (m_bDead == true)
        return OBJ_DEAD;
    
    if (m_pTarget != nullptr)
    {
        m_tInfo.fX = (m_pTarget->Get_Info().fX + (m_fDistance * cosf(m_fAngle * PI / 180.f)));
        m_tInfo.fY = (m_pTarget->Get_Info().fY - (m_fDistance * sinf(m_fAngle * PI / 180.f)));
    }
    m_fAngle += m_fSpeed;

    CObject::Update_Rect();

    return OBJ_NOEVENT;
}

void CRotation_Pet::Late_Update()
{
    if(Bullet_CoolDown(m_bulletCoolDown))
        Create_Missile();
}

void CRotation_Pet::Render(HDC hDC)
{
    HPEN newPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HBRUSH newBrush = CreateSolidBrush(RGB(0, 100, 150));
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

void CRotation_Pet::Release()
{
}
