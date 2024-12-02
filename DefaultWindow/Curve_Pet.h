#pragma once
#include "Pet.h"
class CCurve_Pet : public CPet
{
public:
	CCurve_Pet();
	virtual ~CCurve_Pet();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	POINT m_tCenter;
	float m_RotAngle;
	float m_RotSpeed;

	bool m_bMove;
};

