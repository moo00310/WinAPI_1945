#pragma once
#include "Pet.h"
class CTracking_Pet : public CPet
{
public:
	CTracking_Pet();
	virtual ~CTracking_Pet();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	
private:
	bool m_bMove;
	float m_fPetAngle;
};

