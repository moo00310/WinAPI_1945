#include "pch.h"
#include "Tracking_Pet.h"

CTracking_Pet::CTracking_Pet() : m_bMove(true), m_fPetAngle(0)
{
}

CTracking_Pet::~CTracking_Pet()
{
}

void CTracking_Pet::Initialize()
{
    m_tInfo = { WINCX * 0.5f, WINCY - 50.f, 15.f, 15.f };
    m_fSpeed = 6.f;
    m_bulletCoolDown = 1500;
    m_fPetAngle = 0.f;

    m_ePetType = TRACK_PET;
}

int CTracking_Pet::Update()
{
    if (m_bDead == true)
        return OBJ_DEAD;

    if (m_bMove == true)
    {
        float fWdith(0), fHeight(0), fDiagonal(0), fRadian(0);
        
        fWdith = (m_pTarget->Get_Info().fX) - m_tInfo.fX;
        fHeight = (m_pTarget->Get_Info().fY) - m_tInfo.fY;
        fDiagonal = sqrtf(fWdith * fWdith + fHeight * fHeight);

        fRadian = acosf(fWdith / fDiagonal);

        m_fPetAngle = fRadian * (180.f / PI);

        if (m_pTarget->Get_Info().fY > m_tInfo.fY)
            m_fPetAngle *= -1.f;

        m_tInfo.fX += ( m_fSpeed * cosf(m_fPetAngle * PI / 180.f));
        m_tInfo.fY -= ( m_fSpeed * sinf(m_fPetAngle * PI / 180.f));
    }


    CObject::Update_Rect();

	return OBJ_NOEVENT;
}

void CTracking_Pet::Late_Update()
{
    if (m_pTarget->Get_Rect()->right + 35 <= m_tRect.right ||
        m_pTarget->Get_Rect()->left - 35 >= m_tRect.left ||
        m_pTarget->Get_Rect()->bottom + 35 <= m_tRect.bottom||
        m_pTarget->Get_Rect()->top - 35 >= m_tRect.top)
    {
        m_bMove = true;
    }
    else
        m_bMove = false;

    if (Bullet_CoolDown(m_bulletCoolDown))
    {
        Create_Bullet();
    }
}

void CTracking_Pet::Render(HDC hDC)
{
    HPEN newPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HBRUSH newBrush = CreateSolidBrush(RGB(0, 210, 200));
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

void CTracking_Pet::Release()
{
}
