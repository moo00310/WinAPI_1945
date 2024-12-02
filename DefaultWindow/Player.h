#pragma once
#include "Object.h"
#include "Bullet.h"
#include "AbstractFactory.h"

enum PlayerType
{
	PT_LIGHTNING = 1,
	PT_MUSTANG
};

class CTextures;

class CPlayer : public CObject
{
public:
	CPlayer(PlayerType _playerType);
	virtual ~CPlayer();

public:
	virtual void Initialize()override;
	virtual int Update() override;
	void Late_Update() override;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() override;

public:
	void Set_Bullet(list<CObject*>* pBullet) { m_pBullet = pBullet; }
	void Set_itemArray(int* _array) { m_itemArray = _array; }
	void Set_Monster_Set_MBullet_Set_Item_Set_BoomFX(list<CObject*>* pMonster, list<CObject*>* pMBullet, list<CObject*>* _pitem, list<CObject*>* _pBoomFX);
	void Set_Bullet_Type()
	{
		if (m_eBullet_Type < BUL_PL4)
		{
			m_eBullet_Type = (BULLET_ID)(m_eBullet_Type + 1);
		}
	}
	void Set_Pet(list<CObject*>* _pPet);
	list<CObject*>* Get_Monster();
	void Clear_Pet();
	void Clear_Bullet() { m_itemArray[ITEM_ATTACK] = 0;	}

	void Create_Rot_Pet(float fAngle);
	void Create_Cur_Pet();
	void Create_Tra_Pet();

public:
	void SetDeadthTime(ULONGLONG _ullDeathTime)
	{
		m_ullDeathTime = _ullDeathTime;
	}
	void SetDeathCount(int* ref) { m_pDeadthCount = ref; }
	void SetActionCount(ULONG64* _ullActionCount) { m_pullActionCount = _ullActionCount; }
	void SetisWin(bool* _isWin) { m_bIsWin = _isWin; }
	void InitStage();
	void Set_Score(int* _iScore) { m_pScore = _iScore; }
private:
	void Create_Bullet();
	
protected:
	void Key_Input();

private:
	PlayerType m_PlayerType;
	list<CObject*>* m_pBullet;
	list<CObject*>* m_pPet;
	bool m_bDropItem;
	int* m_pScore;

protected:
	int m_BoomCoolDown;
	int* m_itemArray;
	list<CObject*>* m_pMonster;
	list<CObject*>* m_pMBullet;
	list<CObject*>* m_pitem;
	list<CObject*>* m_pBoomFX;

protected:
	bool* m_bIsWin;
	ULONGLONG m_ullDeathTime;
	int* m_pDeadthCount;
	ULONG64* m_pullActionCount;

protected:
	CTextures* m_pTex;
	ULONGLONG Temp;
	
};

/*---------------
	PlayerType
----------------*/
class CLightning : public CPlayer
{
public:
	CLightning() : CPlayer(PT_LIGHTNING)
	{
		m_fSpeed = 13.f;
		m_bulletCoolDown = 150;
		m_eBullet_Type = BUL_PL1;
	}

	virtual void Render(HDC hDC) override;

	// TODO : 
	// 총알 방식 Ex) 집탄, 확산
	// 펫 타입 (원형,  따라가기)

};

class CMustang : public CPlayer
{
public:
	CMustang() : CPlayer(PT_MUSTANG)
	{
		m_fSpeed = 10.f;
		m_bulletCoolDown = 500;
		m_eBullet_Type = BUL_PL4;
	}

	virtual void Render(HDC hDC) override;

};