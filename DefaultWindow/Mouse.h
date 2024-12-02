#pragma once
#include "Object.h"
class Mouse : public CObject
{
public:
	Mouse();
	virtual ~Mouse();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;


};

