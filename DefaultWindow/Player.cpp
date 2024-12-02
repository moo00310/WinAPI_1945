#include "pch.h"
#include "Player.h"
#include "Player_Bullet.h"
#include "Pet.h"
#include "Rotation_Pet.h"
#include "Curve_Pet.h"
#include "Tracking_Pet.h"
#include "BoomEffect.h"
#include "Item.h"
#include "Textures.h"

CPlayer::CPlayer(PlayerType _playerType)
	: m_pBullet(nullptr), m_PlayerType(_playerType),
	m_BoomCoolDown(0), m_pPet(nullptr),
	m_ullDeathTime(0), m_pDeadthCount(nullptr),
	m_bDropItem(false), m_bIsWin(nullptr),
	m_itemArray(nullptr), m_pBoomFX(nullptr),
	m_pMBullet(nullptr), m_pMonster(nullptr),
	m_pitem(nullptr), m_pullActionCount(nullptr),
	m_pScore(nullptr)
{
	m_pTex = new CTextures;

	wstring strFilePath;
	strFilePath += L"..\\Textures\\SpaceShip64bit.bmp";
	m_pTex->Load(strFilePath);
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_BoomCoolDown = 3000;
	m_itemArray[ITEM_BOOM] = 3;
	m_tInfo = { WINCX * 0.5f, WINCY * 0.5f, 20.f, 40.f };
	Temp = GetTickCount64() - m_BoomCoolDown;
}

int CPlayer::Update()
{
	Key_Input();

	if (m_bDead == true && m_bDropItem == false)
	{
		m_bDropItem = true;
		(*m_pitem).push_back(CAbstractFactory<CBoom>::Create(m_tInfo.fX, m_tInfo.fY));
		(*m_pitem).push_back(CAbstractFactory<CAdd_Attack>::Create(m_tInfo.fX, m_tInfo.fY));
		(*m_pitem).push_back(CAbstractFactory<Add_Pet>::Create(m_tInfo.fX, m_tInfo.fY));

		//총알 초기화
		if(m_PlayerType == PT_LIGHTNING)
			m_eBullet_Type = BUL_PL1;

		if (--(*m_pDeadthCount) <= 0)
			return OBJ_NODRAW;
	}

	CObject::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
}


void CPlayer::Release()
{
	Safe_Delete<CTextures*>(m_pTex);
}

void CPlayer::Set_Monster_Set_MBullet_Set_Item_Set_BoomFX(list<CObject*>* pMonster, list<CObject*>* pMBullet, list<CObject*>* _pitem, list<CObject*>* _pBoomFX)
{
	m_pMonster = pMonster;
	m_pMBullet = pMBullet;
	m_pitem = _pitem;
	m_pBoomFX = _pBoomFX;
}

void CPlayer::Key_Input()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (m_bDead && *m_pDeadthCount != 0 && GetTickCount64() - m_ullDeathTime >= 3000) // 3초 후 실행
		{
			for (auto& bullet : *m_pMBullet)
			{
				bullet->Set_Dead();
			}

			m_bDead = false;
			m_bDropItem = false;
			m_ullDeathTime = 0;
		}
		else if (!m_bDead)
		{
			if (Bullet_CoolDown(m_bulletCoolDown))
			{
				Create_Bullet();
			}
		}
	}

	if (GetAsyncKeyState('R'))
	{
		if ((m_bDead && *m_pDeadthCount == 0) || m_bIsWin)
			InitStage(); // 화면, 아이템, 체력, 초기화 
	}

	// 죽었을 때 키 입력 방지
	if (m_bDead) return;

	if (GetAsyncKeyState('Q'))
	{
		if (Temp + m_BoomCoolDown <= GetTickCount64())
		{
			if (m_itemArray[ITEM_BOOM] > 0)
			{
				if (m_PlayerType == PT_LIGHTNING)
				{
					m_pBoomFX->push_back(CAbstractFactory<CBoomCricle>::Create(m_tInfo.fX, m_tInfo.fY));
				}
				else if (m_PlayerType == PT_MUSTANG)
				{
					m_pBoomFX->push_back(CAbstractFactory<CBoomPlane>::Create(m_tInfo.fX, 1000.f));
					dynamic_cast<CBoomPlane*>((m_pBoomFX)->back())->SetBullet(m_pBullet);
				}

				m_itemArray[ITEM_BOOM] -= 1;
				if (m_itemArray[ITEM_BOOM] < 0) m_itemArray[ITEM_BOOM] = 0;

				Temp = GetTickCount64();
			}
		}
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{

		if (GetAsyncKeyState(VK_UP))
		{
			if (WINCX - 50 >= m_tRect.right && 50 <= m_tRect.top)
			{
				m_tInfo.fX += m_fSpeed / sqrtf(2.f);
				m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (WINCX - 50 >= m_tRect.right && WINCY - 50 >= m_tRect.bottom)
			{
				m_tInfo.fX += m_fSpeed / sqrtf(2.f);
				m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			}
		}
		else
		{
			if (WINCX - 50 >= m_tRect.right)
				m_tInfo.fX += m_fSpeed;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			if (50 <= m_tRect.left && 50 <= m_tRect.top)
			{
				m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
				m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (50 <= m_tRect.left && WINCY - 50 >= m_tRect.bottom)
			{
				m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
				m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			}
		}
		else
			if (50 <= m_tRect.left)
				m_tInfo.fX -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		if (50 <= m_tRect.top)
			m_tInfo.fY -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (WINCY - 50 >= m_tRect.bottom)
			m_tInfo.fY += m_fSpeed;
	}
}

void CPlayer::Set_Pet(list<CObject*>* _pPet)
{
	m_pPet = _pPet;
}

list<CObject*>* CPlayer::Get_Monster()
{
	return m_pMonster;
}

void CPlayer::Clear_Pet()
{
	for (auto& pet : *m_pPet)
	{
		pet->Set_Dead();
	}
	m_itemArray[ITEM_PET1] = 0;
	m_itemArray[ITEM_PET2] = 0;
	m_itemArray[ITEM_PET3] = 0;
}

void CPlayer::InitStage()
{
	for (auto& bullet : *m_pMBullet)
	{
		bullet->Set_Dead();
	}
	for (auto& monster : *m_pMonster)
	{
		monster->Set_Dead();
	}
	for (auto& item : *m_pitem)
	{
		item->Set_Dead();
	}

	// 몹 처음 부터 다시 소환
	*m_pullActionCount = 0;

	// Init
	if (m_PlayerType == PT_LIGHTNING)
		m_eBullet_Type = BUL_PL1;

	*m_pScore = 0;
	*m_bIsWin = false;
	m_bDead = false;
	m_bDropItem = false;
	m_ullDeathTime = 0;
	*m_pDeadthCount = MAX_HP;
	for (int i = 0; i < ITEM_END; ++i)
	{
		m_itemArray[i] = 0;
	}
}

void CPlayer::Create_Bullet()
{
	switch (m_eBullet_Type)
	{
	case BUL_PL1:
		m_pBullet->push_back(CAbstractFactory<CPlayer_Bullet>::Create());
		m_pBullet->back()->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		break;

	case BUL_PL2:
		m_pBullet->push_back(CAbstractFactory<CPlayer_Bullet>::Create());
		m_pBullet->back()->Set_Pos(m_tInfo.fX - 5, m_tInfo.fY);
		m_pBullet->push_back(CAbstractFactory<CPlayer_Bullet>::Create());
		m_pBullet->back()->Set_Pos(m_tInfo.fX + 5, m_tInfo.fY);
		break;

	case BUL_PL3:
		for (int i = 0; i < 4; ++i)
		{
			m_pBullet->push_back(CAbstractFactory<CPlayer_Bullet>::Create());
			m_pBullet->back()->Set_Pos(m_tInfo.fX - 15 + (i * 10), m_tInfo.fY);
		}
		break;
	case BUL_PL4:
		for (int i = 0; i < 4; ++i)
		{
			m_pBullet->push_back(CAbstractFactory<CPlayer_Bullet>::Create());
			m_pBullet->back()->Set_Pos(m_tInfo.fX - 15 + (i * 10), m_tInfo.fY);
		}

		m_pBullet->push_back(CAbstractFactory<CPlayer_Bullet>::Create());
		m_pBullet->back()->Set_Pos(m_tInfo.fX - 25, m_tInfo.fY);
		dynamic_cast<CPlayer_Bullet*>(m_pBullet->back())->Set_Dir(LEFT);

		m_pBullet->push_back(CAbstractFactory<CPlayer_Bullet>::Create());
		m_pBullet->back()->Set_Pos(m_tInfo.fX + 25, m_tInfo.fY);
		dynamic_cast<CPlayer_Bullet*>(m_pBullet->back())->Set_Dir(RIGHT);
		break;

	default:
		break;
	}
}

void CPlayer::Create_Rot_Pet(float _fAngle)
{
	if (3 >= m_itemArray[ITEM_PET1])
	{
		m_pPet->push_back(CAbstractFactory<CRotation_Pet>::Create(this));

		if (CPet* Temp = dynamic_cast<CPet*>(m_pPet->back()))
		{
			Temp->Set_Bullet(m_pBullet);
			Temp->Set_Monster(m_pMonster);
		}

		float fAngle = m_pPet->front()->Get_Angle();

		for (auto iter = m_pPet->begin();
			iter != m_pPet->end();
			iter++)
		{
			
			if (dynamic_cast<CPet*>(*iter)->Get_Type() == ROT_PET)
			{
				fAngle += _fAngle;
				(*iter)->Set_Angle(fAngle);
			}
		}
	}
}

void CPlayer::Create_Cur_Pet()
{
	if (3 >= m_itemArray[ITEM_PET2])
	{
		m_pPet->push_back(CAbstractFactory<CCurve_Pet>::Create(m_tInfo.fX, m_tInfo.fY, 0.f));

		if (CPet* Temp = dynamic_cast<CPet*>(m_pPet->back()))
		{
			Temp->Set_Bullet(m_pBullet);
			Temp->Set_Monster(m_pMonster);
		}

	}
}

void CPlayer::Create_Tra_Pet()
{
	if (1 == m_itemArray[ITEM_PET3])
	{
		m_pPet->push_back(CAbstractFactory<CTracking_Pet>::Create(this));

		if (CPet* Temp = dynamic_cast<CPet*>(m_pPet->back()))
		{
			Temp->Set_Bullet(m_pBullet);
			Temp->Set_Monster(m_pMonster);
		}
	}
	else if (3 >= m_itemArray[ITEM_PET3])
	{
		m_pPet->push_back(CAbstractFactory<CTracking_Pet>::Create());

		if (CPet* Temp = dynamic_cast<CPet*>(m_pPet->back()))
		{
			Temp->Set_Bullet(m_pBullet);
			Temp->Set_Monster(m_pMonster);
			auto iter = m_pPet->end();
			iter--;
			iter--;
			for (;
				iter != m_pPet->begin();
				iter--)
			{
				if (dynamic_cast<CPet*>(*iter)->Get_Type() == TRACK_PET)
				{
					m_pPet->back()->Set_Target(*iter);
					break;
				}
			}

			if (dynamic_cast<CPet*>(*iter)->Get_Type() == TRACK_PET)
			{
				m_pPet->back()->Set_Target(*iter);
			}
		}
	
	}
}


/*---------------
	PlayerType
----------------*/
void CLightning::Render(HDC hDC)
{
	if (m_bDead == true) return;
	int iWidth = (int)(m_pTex->GetWidth());
	int iHeight = (int)(m_pTex->GetHeight());

	INFO vPos = Get_Info();
	TransparentBlt(hDC,
		int(vPos.fX - (float)(iWidth / 2)),
		int(vPos.fY - (float)(iHeight / 2)),
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0, iWidth, iHeight,
		RGB(1, 1, 1));
}

void CMustang::Render(HDC hDC)
{
	if (m_bDead == true) return;
	int iWidth = (int)(m_pTex->GetWidth());
	int iHeight = (int)(m_pTex->GetHeight());

	INFO vPos = Get_Info();
	TransparentBlt(hDC,
		int(vPos.fX - (float)(iWidth / 2)),
		int(vPos.fY - (float)(iHeight / 2)),
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0, iWidth, iHeight,
		RGB(1, 1, 1));
}
