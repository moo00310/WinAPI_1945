#pragma once
#include "Bullet.h"
class CMonster_Bullet02 : public CBullet
{
public:
	CMonster_Bullet02();
	virtual ~CMonster_Bullet02()override;

	// CBullet을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void Update_Polygon();
	void Set_Degree(const INFO* _Target);

private:
	const INFO* m_pTarget;

	ULONGLONG m_ullTime;
	float m_fDegree;
	POINT m_pPoints[4];

};

