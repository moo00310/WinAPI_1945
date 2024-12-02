#pragma once
#include "Bullet.h"
class CPlayer_Bullet : public CBullet
{
public:
	CPlayer_Bullet();
	virtual ~CPlayer_Bullet() override;

	void Initialize() override;
	int Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void Set_Dir(const DIRECTION& _Dir);

private:
	DIRECTION m_eDir;
};





