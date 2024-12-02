#pragma once
#include "Object.h"
#include "Textures.h"

class CMonster : public CObject
{
public:
	CMonster();
	~CMonster();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
public:
	void CulCircle(int _vel);

public:
	void Set_PlInfo(INFO* _pInfo) { m_pPlINFO = _pInfo; }
	void Set_Bullet(list<CObject*>* pBullet) { m_pBullet = pBullet; }
	void Set_Bullet_Type(const BULLET_ID& _Bullet_Id) { m_eBullet_Type = _Bullet_Id; }

	void Create_Bullet();
	void Create_Bullet(const float& _Degree);
private:
	INFO m_tCircle;
	int  m_iTime;
	int  m_iVel;

	list<CObject*>* m_pBullet;

	INFO* m_pPlINFO;

	ULONGLONG m_ulltime, m_ullframe;
	float m_fDegree;
protected:
	void Atk_Pattern1(); // 돌면서 흩뿌리기 
	void Atk_Pattern2(); // 교차되는 전방향 탄환
};

