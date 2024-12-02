#pragma once
#include "define.h"

enum DIRECTION { UP, DOWN, LEFT, RIGHT, LEFTUP, RIGHTUP, LEFTDOWN, RIGHTDOWN, DIR_END };
enum BULLET_ID { BUL_PL1, BUL_PL2, BUL_PL3, BUL_PL4, BUL_MON1, BUL_MON2, BUL_MON3, BUL_MON4, BUL_END };

class CObject
{
public:
	CObject();
	virtual ~CObject();

public:
	INFO Get_Info() { return m_tInfo; }
	INFO* Get_pInfo() { return &m_tInfo; }
	RECT* Get_Rect() { return &m_tRect; }

	void Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

public:
	virtual void Initialize()PURE;
	virtual int Update()PURE;
	virtual void Late_Update()PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()PURE;

public:
	void Update_Rect();

public:
	DIRECTION Get_Direct();
	void Set_Direct(DIRECTION eDirect);
	bool Get_Dead();
	void Set_Dead();
	void Set_Target(CObject* pTarget) { m_pTarget = pTarget; }
	float Get_Angle() { return m_fAngle; }
	void Set_Angle(float fAngle) { m_fAngle = fAngle; }
	void Add_Angle(float fAngle) 
	{
		m_fAngle += fAngle;
		if (m_fAngle > 360)
			m_fAngle -= 360;
	}
	void Set_CoolTime(const int& _time) { m_bulletCoolDown = _time; }

public:
	void AddPos(float fX, float fY) { m_tInfo.fX += fX; m_tInfo.fY += fY; }
	void AddScale(float fCX, float fCY) { m_tInfo.fCX += fCX; m_tInfo.fCY += fCY; }

public:
	bool Bullet_CoolDown(int CoolDown);

protected:
	INFO m_tInfo;   // 위치 정보를 저장할 구조체?
	RECT m_tRect;   // 그리기용 렉트
	CObject* m_pTarget;

	bool m_bDead;
	float m_fSpeed;    // 속도
	float m_fDistance; // 오브젝트 간 거리
	float m_fAngle;

	DIRECTION m_eDirect; // 방향 설정
	BULLET_ID m_eBullet_Type; // 총알타입

	ULONG64 m_ullLast_Bullet;
	int m_bulletCoolDown;
};

