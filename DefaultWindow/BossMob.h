#pragma once
#include "Monster.h"

enum STATE {
	Appear,
	STATE_01,
	STATE_02,
	STATE_03,
	STATE_04,
	STATE_05,
	STATE_IDLE
};

class CBossMob : public CMonster
{
public:
	CBossMob();
	~CBossMob();

public:
	void		Initialize() override;
	int			Update() override;
	void		Late_Update() override;
	void		Render(HDC hDC) override;
	void		Release() override;

public:
	void		CulRotate(HDC hDC, float angleInDegrees);

public:
	INFO		GettCircle() { return m_tCircle; }
	int			GetiDistance() { return m_iDistance; }
	int			GetiTime() { return m_iTime; }
	int			GetiVel() { return m_iVel; }
	int			GetiHp() { return m_iHp; }
	int			GetiSin() { return m_iStack; }

public:
	void		SettCirclePos(INFO _info) { m_tCircle.fX = _info.fX; m_tCircle.fY = _info.fY; }
	void		SettCircleScale(INFO _info) { m_tCircle.fCX = _info.fCX; m_tCircle.fCY = _info.fCY; }
	void		SetiDistance(int _dis) { m_iDistance = _dis; }
	void		SetiTime(int _time) { m_iTime = _time; }
	void		SetiVel(int _vel) { m_iVel = _vel; }
	void		SetiAddX(float _AddX) { m_iAddX = _AddX; }
	void		SetiAddY(float _AddY) { m_iAddY = _AddY; }
	void		AddiHp(int _hp) { m_iHp += _hp; }

public:
	void		Scale_pattern();
	void		Rotate_pattern();
	void		Moving_pattern();

private:
	INFO	m_tCircle;
	int		m_iDistance;
	int		m_iTime;
	int		m_iVel;
	int		m_iHp;
	int		m_iStack;
	int		m_iMoving;
	float	m_iAddX;
	float	m_iAddY;
	float	m_fRotate;
	bool	m_bScale;
	bool	m_bRotate;
	bool	m_bMoving;

private:
	STATE m_eState = Appear;
	ULONGLONG m_dwStateStartTime = GetTickCount64();
	float m_fXOne;
	float m_fYOne;
	int m_iAtkAction;
	int m_iRGB_value;
};



