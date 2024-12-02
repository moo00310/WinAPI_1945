#include "pch.h"
#include "SelectScene.h"
#include "CollisionManager.h"

SelectScene::SelectScene() : m_hDC(nullptr), isStart(false)
{
	ZeroMemory(&m_tBox1, sizeof(RECT));
	ZeroMemory(&m_tBox1, sizeof(RECT));
	ZeroMemory(&m_AllBox, sizeof(RECT));
}

SelectScene::~SelectScene()
{
	Release();
}

void SelectScene::Initilaize()
{
	m_hDC = GetDC(g_hWnd);

	if (!m_Mouse)
	{
		m_Mouse = new Mouse();
		m_Mouse->Initialize();
	}

	m_AllBox = { 0, 0, 600, 800 };

	m_tBox1 = { 100, 100, 275, 400 };
	m_tBox2 = { 325, 100, 500, 400 };
}

void SelectScene::Update()
{
	m_Mouse->Update();



}

CObject* SelectScene::Late_Update()
{
	RECT rc;
	if (!isStart)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			isStart = true;
		}
	}
	else
	{
		// 마우스클릭으로 플레이어를 선택
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (IntersectRect(&rc, &m_tBox1, m_Mouse->Get_Rect()))
			{
				m_pPlayer = new CLightning();
				return m_pPlayer;
			}
			else if (IntersectRect(&rc, &m_tBox2, m_Mouse->Get_Rect()))
			{
				m_pPlayer = new CMustang();
				return m_pPlayer;
			}
		}
	}

	return nullptr;
}

void SelectScene::Render()
{

	if (!isStart)
	{
		Rectangle(m_hDC, 0, 0, WINCX, WINCY);

		swprintf_s(szBuf1, L"1945 게임");
		TextOut(m_hDC, 250, 350, szBuf1, lstrlen(szBuf1));

		swprintf_s(szBuf1, L"4조: 신승훈 임동하 최은성 임무결");
		TextOut(m_hDC, 170, 400, szBuf1, lstrlen(szBuf1));

		swprintf_s(szBuf1, L"시작하려면 스페이스바를 입력하세요");
		TextOut(m_hDC, 170, 450, szBuf1, lstrlen(szBuf1));

	}
	else  // 시작을 했다면
	{
		// 배경 가리는 창
		Rectangle(m_hDC, 0, 0, WINCX, WINCY);
		// 선택 상자
		Rectangle(m_hDC, m_tBox1.left, m_tBox1.top, m_tBox1.right, m_tBox1.bottom);
		Rectangle(m_hDC, m_tBox2.left, m_tBox2.top, m_tBox2.right, m_tBox2.bottom);

		// 텍스트
		swprintf_s(szBuf1, L"라이트닝 전투기");	// 모든 서식 문자 지원 함수
		TextOut(m_hDC, 150, 450, szBuf1, lstrlen(szBuf1));

		swprintf_s(szBuf1, L"머스탱 전투기");	// 모든 서식 문자 지원 함수
		TextOut(m_hDC, 350, 450, szBuf1, lstrlen(szBuf1));

		swprintf_s(szBuf1, L"마우스로 전투기를 선택하세요");	// 모든 서식 문자 지원 함수
		TextOut(m_hDC, 170, 550, szBuf1, lstrlen(szBuf1));
	}

	m_Mouse->Render(m_hDC);
}

void SelectScene::Release()
{
	Safe_Delete<CObject*>(m_Mouse);
}

void SelectScene::SelectPlayer()
{
}
