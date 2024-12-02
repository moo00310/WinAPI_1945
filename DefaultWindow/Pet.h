#pragma once
#include "Object.h"
#include "Pet_Bullet.h"

class CPet : public CObject
{
public:
	CPet();
	virtual ~CPet();

public:
	virtual void Initialize()PURE;
	virtual int Update()PURE;
	virtual void Late_Update()PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release()PURE;

public:
	void Set_Bullet(list<CObject*>* pBullet) { m_pPetBullet = pBullet; }
	PET_TYPE Get_Type();
	void Set_Monster(list<CObject*>* pMob) { m_pMob = pMob; }
public:
	virtual void Create_Bullet();
	virtual void Create_Missile();

private:
	INFO* Search_Immediate_Enemy_INFO();

private:
	list<CObject*>* m_pPetBullet;
	list<CObject*>* m_pMob;
protected:
	PET_TYPE m_ePetType;
};

