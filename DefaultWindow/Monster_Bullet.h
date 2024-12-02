#pragma once
#include "Bullet.h"
class CMonster_Bullet : public CBullet
{
public:
	CMonster_Bullet();
	virtual ~CMonster_Bullet() override;

	void Initialize() override;
	int Update() override;
	void Render(HDC hDC) override;
	void Release() override;
public:

	void Set_Degree(const float& _Degree) { m_fDegree = _Degree * PI / 180; }
	void Set_Degree(const INFO* _Target);
	void ADD_Degree(const float& _Degree) { m_fDegree += _Degree * PI / 180; }
private:
	float m_fDegree;
};





