#pragma once
#include "Bullet.h"
class CPet_Bullet : public CBullet
{
public:
	CPet_Bullet();
	virtual ~CPet_Bullet() override;

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	//void Rotate();
	void Update_Polygon();

	void Set_Degree(const INFO* _Target);

private:
	const INFO* m_pTarget;
	POINT m_pPoints[4];
};

