#pragma once
#include "Object.h"
#define SQUARE(X) (X) * (X)

class CBullet : public CObject
{
public:
	CBullet();
	virtual ~CBullet() override;

public:
	void Initialize() PURE;
	int Update() PURE;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() PURE;

};

class BoomBullet : public CBullet
{
public:
	void Initialize() override;
	int Update() override;
	void Release() override;
};
