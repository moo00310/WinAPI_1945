#include "pch.h"
#include "Mouse.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
    Release();
}

void Mouse::Initialize()
{
    m_tInfo.fCX = 30.f;
    m_tInfo.fCY = 30.f;
}

int Mouse::Update()
{
    ShowCursor(FALSE);
    POINT       ptMouse{};
    GetCursorPos(&ptMouse);
    ScreenToClient(g_hWnd, &ptMouse);

    m_tInfo.fX = (float)ptMouse.x;
    m_tInfo.fY = (float)ptMouse.y;

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void Mouse::Late_Update()
{
}

void Mouse::Render(HDC hDC)
{
    Ellipse(hDC,
        m_tRect.left,
        m_tRect.top,
        m_tRect.right,
        m_tRect.bottom);
}

void Mouse::Release()
{
}
