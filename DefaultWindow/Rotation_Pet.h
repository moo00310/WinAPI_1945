#pragma once
#include "Pet.h"

class CRotation_Pet : public CPet
{
public:
	CRotation_Pet();
	virtual ~CRotation_Pet();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	float m_fPetAngle;
};

