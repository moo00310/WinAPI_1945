#include "pch.h"
#include "MainGame.h"
#include "Player.h"
#include "Monster.h"
#include "MonsterCircle.h"
#include "MonsterDown.h"
#include "BossMob.h"
#include "Item.h"
#include "AbstractFactory.h"
#include "CollisionManager.h"
#include "Rotation_Pet.h"

HDC g_hDC = GetDC(g_hWnd);

CMainGame::CMainGame()
	: m_hDC(nullptr), m_ullTime(0),
	m_dwTime(0), m_iFPS(0),
	m_iScore(0), m_ullTimeCount(0),
	m_ullActionCount(0), m_hBit(0),
	m_memDC(0), m_iItemCount{0},
	m_ullItemTime(0)
{
	ZeroMemory(&m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

void CMainGame::Initialize(CObject* pPlayer)
{
	srand(unsigned(time(NULL)));

	m_hDC = GetDC(g_hWnd);
	m_iDeadthCount = MAX_HP;

	m_hBit = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	m_ObjList[OBJ_PLAYER].push_back(pPlayer);
	if (CPlayer* Temp = dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front()))
	{
		Temp->Set_Bullet(&m_ObjList[OBJ_P_BULLET]);
		Temp->Set_itemArray(m_iItemCount);
		Temp->Set_Monster_Set_MBullet_Set_Item_Set_BoomFX
		(&m_ObjList[OBJ_MONSTER], &m_ObjList[OBJ_M_BULLET], &m_ObjList[OBJ_ITEM], &m_ObjList[OBJ_BOOMEFFECT]);
		Temp->Set_Pet(&m_ObjList[OBJ_PET]);
		Temp->SetDeathCount(&m_iDeadthCount);
		Temp->SetActionCount(&m_ullActionCount);
		Temp->SetisWin(&m_bisWin);
		Temp->Set_Score(&m_iScore);
		pPlayer->Initialize();
	}

}

void CMainGame::Update()
{
	// 현재 시간 가져오기
	ULONGLONG currentTime = GetTickCount64();

	//Item Test

	if (m_ullItemTime + 3000 < GetTickCount64())
	{
		m_ullItemTime = GetTickCount64();
		float fRandomX = (float)(rand() % (400 - 100 + 1) + 100);
		switch (rand() % 3)
		{
		case 0:
			m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<CBoom>::Create(fRandomX, 200));
			break;
		case 1:
			m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<CAdd_Attack>::Create(fRandomX, 200));
			break;
		case 2:
			m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<Add_Pet>::Create(fRandomX, 200));
			break;
		default:
			break;
		}
	}

	//////
	if (currentTime - m_ullTime >= 1000)
	{
		++m_ullTimeCount;

		m_ullTime = currentTime;

		Mop_Down(0, 4);
		Mop_Lumped(4, 5);
		Mop_Lumped(6, 7);
		Mop_Horizon(8, 10);
		Mop_Down(10, 12);
		Mop_Lumped(12, 13, BUL_MON2, 2000);
		Mop_CIrcle(14, 15);
		//Pause(15,18);
		Mop_Up(18, 23);
		//Pause(25,30);
		Mop_Lumped(23, 24);

		Mop_Up(27, 30, BUL_MON1, 1000 + rand() % 1500);
		Mop_Lumped(27, 30, BUL_MON1, 1000 + rand() % 1500, true);
		Mop_Down(27, 30);

		//Pause(30,31);

		Mop_Boss(35, 36);
		++m_ullActionCount;
	}


	for (int i = 0; i < OBJ_END; i++)        // 포문 돌면서 업데이트 호출, iResult의 반환값이 DEAD라면 ( 이벤트가 발생했다면 ) 삭제 
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end();)
		{
			if ((*iter) == nullptr) continue;
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				if (m_ObjList[i] == m_ObjList[OBJ_MONSTER])
				{
					m_iScore += 100;
				}

				Safe_Delete<CObject*>(*iter);
				iter = m_ObjList[i].erase(iter);


			}
			else
				iter++;
		}
	}
}

void CMainGame::Late_Update()
{
	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); iter++)
		{
			(*iter)->Late_Update();
		}
	}

	CCollisionManager::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_P_BULLET]);
	CCollisionManager::Collision_Circle(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_P_BULLET], &m_bisWin);
	CCollisionManager::Collision_Circle2(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_P_BULLET]);
	CCollisionManager::Collision_Player(m_ObjList[OBJ_PLAYER].front(), m_ObjList[OBJ_M_BULLET]);
	CCollisionManager::Collision_Item(m_ObjList[OBJ_PLAYER].front(), m_ObjList[OBJ_ITEM], m_iItemCount);
	if(!m_ObjList[OBJ_BOOMEFFECT].empty())
		CCollisionManager::Collision_Boom(m_ObjList[OBJ_BOOMEFFECT].front(), m_ObjList[OBJ_M_BULLET]);
}

void CMainGame::Render()
{
	++m_iFPS;

	Rectangle(m_memDC, 0, 0, WINCX, WINCY);
	HPEN newBackGroundPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HBRUSH newBackGroundBrush = CreateSolidBrush(RGB(0, 0, 0));
	//HBRUSH newBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HPEN oldBackGroundPen = (HPEN)SelectObject(m_memDC, newBackGroundPen);
	HBRUSH oldBackGroundBrush = (HBRUSH)SelectObject(m_memDC, newBackGroundBrush);

	Rectangle(m_memDC, 50, 50, WINCX - 50, WINCY - 50);

	SelectObject(m_memDC, oldBackGroundPen);
	SelectObject(m_memDC, oldBackGroundBrush);
	DeleteObject(newBackGroundBrush);
	DeleteObject(newBackGroundPen);

	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		
		m_iFPS = 0;
		m_dwTime = GetTickCount64();
	}

	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); iter++)
		{
			(*iter)->Render(m_memDC);
		}
	}
	HPEN newPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(m_memDC, newPen);

	Rectangle(m_memDC, 0, WINCY - 50, WINCX + 50, WINCY);
#pragma region 좌우, 위가림막

	HBRUSH newBrush = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_memDC, newBrush);

	Rectangle(m_memDC, 0, 0, 600, 50);
	Rectangle(m_memDC, 0, 0, 50, 750);
	Rectangle(m_memDC, 550, 0, 600, 750);

	SelectObject(m_memDC, oldPen);
	SelectObject(m_memDC, oldBrush);
	DeleteObject(newBrush);
	DeleteObject(newPen);

#pragma endregion
	TextOut(m_memDC, 100, WINCY - 40, m_szFPS, lstrlen(m_szFPS));

	TCHAR szBuf[32] = L"";
	wsprintf(szBuf, L"플레이어 총알 수 : %d", static_cast<int>(m_ObjList[OBJ_P_BULLET].size()));
	TextOut(m_memDC, 100, WINCY - 20, szBuf, lstrlen(szBuf));

	TCHAR szMobBuf[32] = L"";
	wsprintf(szMobBuf, L"몬스터 총알 수 : %d", static_cast<int>(m_ObjList[OBJ_M_BULLET].size()));
	TextOut(m_memDC, 100, WINCY - 40, szMobBuf, lstrlen(szMobBuf));

	TCHAR szSroce[32] = L"";
	wsprintf(szSroce, L"Score : %d", m_iScore);
	TextOut(m_memDC, 275, WINCY - 40, szSroce, lstrlen(szSroce));

	TCHAR szBoomCount[32] = L"";
	wsprintf(szBoomCount, L"폭탄 개수 : %d", m_iItemCount[ITEM_BOOM]);
	TextOut(m_memDC, 275, WINCY - 20, szBoomCount, lstrlen(szBoomCount));

	TCHAR szHp[32] = L"";
	wsprintf(szHp, L"Player의 남은 목숨 : %d", m_iDeadthCount);
	TextOut(m_memDC, 400, WINCY - 20, szHp, lstrlen(szHp));

	// 부활 텍스트
	if (m_ObjList[OBJ_PLAYER].front()->Get_Dead() && m_iDeadthCount > 0)
	{
		(m_memDC, 50, 50, WINCX - 50, WINCY - 50);
		POINT pos = { 250, 450 };
		UITextPrint(m_memDC, L"죽었습니다!", pos);

		pos = { 170, 500 };
		UITextPrint(m_memDC, L"3초 뒤 space 키를 누르면 부활합니다!", pos);
	}

	// 패배 텍스트
	if (m_iDeadthCount == 0)
	{
		(m_memDC, 50, 50, WINCX - 50, WINCY - 50);
		POINT pos = { 270, 450 };
		UITextPrint(m_memDC, L"패     배!", pos);

		pos = { 200, 500 };
		UITextPrint(m_memDC, L"다시 하려면 R키를 누르세요 !", pos);
	}

	// 승리 텍스트
	if (m_bisWin)
	{
		(m_memDC, 50, 50, WINCX - 50, WINCY - 50);
		POINT pos = { 270, 350 };
		UITextPrint(m_memDC, L"승     리!", pos);

		pos = { 200, 500 };
		UITextPrint(m_memDC, L"다시 하려면 R키를 누르세요 !", pos);
	}

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_memDC, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	for (int i = 0; i < OBJ_END; i++)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObject*>);
		m_ObjList[i].clear();
	}

	ReleaseDC(g_hWnd, m_hDC);
}

inline void CMainGame::Mop_Down(const int& _ActionCountStart, const int& _ActionCountEnd, const BULLET_ID& _BulletType, const int& _BulletCooltime)
{
	// 세로몹 몹 3세트
	if (_ActionCountStart <= m_ullActionCount && m_ullActionCount < _ActionCountEnd)
	{
		//for (int i = 0; i < 5; ++i)
		//{
			//float fX = 100;
			//float fY = 0;
			//DIRECTION eRandom = static_cast<DIRECTION>(DIRECTION::DOWN);
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonsterDown>::Create(100, 0, DOWN, m_ObjList[OBJ_PLAYER].front()->Get_pInfo(), &m_ObjList[OBJ_M_BULLET]));
		m_ObjList[OBJ_MONSTER].back()->Set_CoolTime(1000 + rand() % 1500);
		static_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet_Type(_BulletType);
		m_ObjList[OBJ_MONSTER].back()->Set_CoolTime(_BulletCooltime);
		//fX = 490;
		//fY = 0;
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonsterDown>::Create(490, 0, DOWN, m_ObjList[OBJ_PLAYER].front()->Get_pInfo(), &m_ObjList[OBJ_M_BULLET]));
		m_ObjList[OBJ_MONSTER].back()->Set_CoolTime(1000 + rand() % 1500);
		static_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet_Type(_BulletType);
		m_ObjList[OBJ_MONSTER].back()->Set_CoolTime(_BulletCooltime);

		//}
	}
}

inline void CMainGame::Mop_Lumped(const int& _ActionCountStart, const int& _ActionCountEnd, const BULLET_ID& _BulletType, const int& _BulletCooltime, const bool& _isBulleteToPl)
{
	// 뭉친 몹 2세트
	if (m_ullActionCount >= _ActionCountStart && m_ullActionCount < _ActionCountEnd)
	{
		for (int i = 0; i < 5; ++i)
		{
			//float fX = 10;
			//float fY = 0;
			//DIRECTION eRandom = static_cast<DIRECTION>(DIRECTION::DOWN);
			m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonsterCircle>::Create
			(10, 0, DOWN, 1.f + (i * 50), (i * 5.f), 10, 3, 3, m_ObjList[OBJ_PLAYER].front()->Get_pInfo(), &m_ObjList[OBJ_M_BULLET]));
			static_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet_Type(_BulletType);
			m_ObjList[OBJ_MONSTER].back()->Set_CoolTime(_BulletCooltime);
			static_cast<CMonsterCircle*>(m_ObjList[OBJ_MONSTER].back())->Set_Dir(_isBulleteToPl);
			//fX = 590;
			//fY = 0;
			m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonsterCircle>::Create
			(590, 0, DOWN, 1.f + (i * 50), (i * 5.f), 10, -3, 3, m_ObjList[OBJ_PLAYER].front()->Get_pInfo(), &m_ObjList[OBJ_M_BULLET]));
			static_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet_Type(_BulletType);
			m_ObjList[OBJ_MONSTER].back()->Set_CoolTime(_BulletCooltime);
			static_cast<CMonsterCircle*>(m_ObjList[OBJ_MONSTER].back())->Set_Dir(_isBulleteToPl);
		}
	}

}

inline void CMainGame::Mop_Up(const int& _ActionCountStart, const int& _ActionCountEnd, const BULLET_ID& _BulletType, const int& _BulletCooltime)
{
	// 위로 올라가는 애들
	if (m_ullActionCount >= _ActionCountStart && m_ullActionCount < _ActionCountEnd)
	{
		//for (int i = 0; i < 5; ++i)
		//{
			//float fX = 0;
			//float fY = 600;
			//DIRECTION eRandom = static_cast<DIRECTION>(DIRECTION::RIGHTUP);
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonsterDown>::Create(0, 600, RIGHTUP, m_ObjList[OBJ_PLAYER].front()->Get_pInfo(), &m_ObjList[OBJ_M_BULLET]));
		static_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet_Type(_BulletType);
		m_ObjList[OBJ_MONSTER].back()->Set_CoolTime(_BulletCooltime);

		//fX = 600;
		//fY = 600;
		//eRandom = static_cast<DIRECTION>(DIRECTION::LEFTUP);
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonsterDown>::Create(600, 600, LEFTUP, m_ObjList[OBJ_PLAYER].front()->Get_pInfo(), &m_ObjList[OBJ_M_BULLET]));
		static_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet_Type(_BulletType);
		m_ObjList[OBJ_MONSTER].back()->Set_CoolTime(_BulletCooltime);
		//}

	}
}

inline void CMainGame::Mop_Horizon(const int& _ActionCountStart, const int& _ActionCountEnd, const BULLET_ID& _BulletType, const int& _BulletCooltime)
{
	if (m_ullActionCount >= _ActionCountStart && m_ullActionCount < _ActionCountEnd)
	{
		//float fX = 0;
		//float fY = 200;
		//DIRECTION eRandom = static_cast<DIRECTION>(DIRECTION::LEFT);
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonsterCircle>::Create
		(0, 200, LEFT, 1.f, 5.f, 30, 5, 0, m_ObjList[OBJ_PLAYER].front()->Get_pInfo(), &m_ObjList[OBJ_M_BULLET]));
		static_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet_Type(_BulletType);
		m_ObjList[OBJ_MONSTER].back()->Set_CoolTime(_BulletCooltime);
		static_cast<CMonsterCircle*>(m_ObjList[OBJ_MONSTER].back())->Set_Dir(true);

		//fX = 600;
		//fY = 400;
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonsterCircle>::Create
		(600, 400, LEFT, 1.f, 5.f, 30, -5, 0, m_ObjList[OBJ_PLAYER].front()->Get_pInfo(), &m_ObjList[OBJ_M_BULLET]));
		static_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet_Type(_BulletType);
		m_ObjList[OBJ_MONSTER].back()->Set_CoolTime(_BulletCooltime);
		static_cast<CMonsterCircle*>(m_ObjList[OBJ_MONSTER].back())->Set_Dir(true);
	}
}

inline void CMainGame::Mop_CIrcle(const int& _ActionCountStart, const int& _ActionCountEnd)
{
	if (m_ullActionCount >= _ActionCountStart && m_ullActionCount < _ActionCountEnd)
	{
		for (int i = 0; i < 20; ++i)
		{
			//float fX = 300;
			//float fY = -100;
			//DIRECTION eRandom = static_cast<DIRECTION>(DIRECTION::LEFT);
			m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonsterCircle>::Create
			(300, -100, LEFT, 1.f + float(i * 20), 5.f, 100, 0, 3, m_ObjList[OBJ_PLAYER].front()->Get_pInfo(), &m_ObjList[OBJ_M_BULLET]));
			static_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet_Type(BUL_MON1);
			m_ObjList[OBJ_MONSTER].back()->Set_CoolTime(1500 + i * 40);
		}

	}
}

inline void CMainGame::Mop_Boss(const int& _ActionCountStart, const int& _ActionCountEnd)
{
	if (m_ullActionCount >= _ActionCountStart && m_ullActionCount < _ActionCountEnd)
	{
		//for (int i = 0; i < 20; ++i)
		//{
		float fX = 300;
		float fY = 0;
		DIRECTION eRandom = static_cast<DIRECTION>(DIRECTION::LEFT);
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CBossMob>::Create
		(fX, fY, eRandom, 30.f, 100, 0, 0, m_ObjList[OBJ_PLAYER].front()->Get_pInfo(), &m_ObjList[OBJ_M_BULLET]));
		//}
	}
}
