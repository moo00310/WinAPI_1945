#pragma once
#include "Monster.h"
class CMonsterCircle : public CMonster
{
public:
	CMonsterCircle();
	~CMonsterCircle();

public:
	void		Initialize() override;
	int			Update() override;
	void		Late_Update() override;
	void		Render(HDC hDC) override;
	void		Release() override;

public:
	void		CulCircle(int _vel);

public:
	INFO		GettCircle() { return m_tCircle; }
	int			GetiDistance() { return m_iDistance; }
	int			GetiTime() { return m_iTime; }
	int			GetiVel() { return m_iVel; }

public:
	void		SettCirclePos(INFO _info) { m_tCircle.fX = _info.fX; m_tCircle.fY = _info.fY; }
	void		SettCircleScale(INFO _info) { m_tCircle.fCX = _info.fCX; m_tCircle.fCY = _info.fCY; }
	void		SetiDistance(int _dis) { m_iDistance = _dis; }
	void		SetiTime(int _time) { m_iTime = _time; }
	void		SetiVel(int _vel) { m_iVel = _vel; }
	void		SetiAddX(float _AddX) { m_iAddX = _AddX; }
	void		SetiAddY(float _AddY) { m_iAddY = _AddY; }
	void		Set_Dir(const bool& _isBulletToPl) { m_bisBulletToPl = _isBulletToPl; }

private:
	INFO	m_tCircle;
	int		m_iDistance;
	int		m_iTime;
	int		m_iVel;
	float	m_iAddX;
	float	m_iAddY;

	int m_iBulCount;
	bool m_bisBulletToPl;

};

