#pragma once
#include "Object.h"
#include "BossMob.h"
#include "MonsterCircle.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static CObject* Create()
	{
		CObject* pObj = new T;
		pObj->Initialize();
		return pObj;
	}

	static CObject* Create(float _iX, float _iY, DIRECTION eDirect)
	{
		CObject* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_iX, _iY);
		pObj->Set_Direct(eDirect);

		return pObj;
	}

	static CObject* Create(float _iX, float _iY, float fAngle)
	{
		CObject* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_iX, _iY);
		pObj->Set_Angle(fAngle);

		return pObj;
	}

	static CObject* Create(float fAngle, CObject* pTaget)
	{

		CObject* pObj = new T;
		pObj->Initialize();
		pObj->Add_Angle(fAngle);
		pObj->Set_Target(pTaget);

		return pObj;
	}

	static CObject* Create(CObject* pTaget)
	{

		CObject* pObj = new T;
		pObj->Initialize();
		pObj->Set_Target(pTaget);

		return pObj;
	}


	static CObject* Create(float _iX, float _iY, DIRECTION eDirect, INFO* pInfo, list<CObject*>* pBulletList)
	{
		CObject* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_iX, _iY);
		pObj->Set_Direct(eDirect);
		dynamic_cast<CMonster*>(pObj)->Set_PlInfo(pInfo);
		dynamic_cast<CMonster*>(pObj)->Set_Bullet(pBulletList);

		return pObj;
	}

	static CObject* Create(float _iX, float _iY, float fAngle, INFO* pInfo, list<CObject*>* pBulletList)
	{
		CObject* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_iX, _iY);
		pObj->Set_Angle(fAngle);
		dynamic_cast<CMonster*>(pObj)->Set_PlInfo(pInfo);
		dynamic_cast<CMonster*>(pObj)->Set_Bullet(pBulletList);

		return pObj;
	}

	static CObject* Create(float _iX, float _iY, DIRECTION eDirect, float _iTime, float _iVel, int _iDis, int _iAddXPos, int _iAddYPos, INFO* pInfo, list<CObject*>* pBulletList)
	{
		CObject* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_iX, _iY);
		pObj->Set_Direct(eDirect);

		//이동지연
		dynamic_cast<CMonsterCircle*>(pObj)->SetiTime((int)_iTime);
		//회전속도
		dynamic_cast<CMonsterCircle*>(pObj)->SetiVel((int)_iVel);
		//중심으로부터 거리
		dynamic_cast<CMonsterCircle*>(pObj)->SetiDistance(_iDis);
		//중심이동속도
		dynamic_cast<CMonsterCircle*>(pObj)->SetiAddX((float)_iAddXPos);
		dynamic_cast<CMonsterCircle*>(pObj)->SetiAddY((float)_iAddYPos);
		dynamic_cast<CMonster*>(pObj)->Set_PlInfo(pInfo);
		dynamic_cast<CMonster*>(pObj)->Set_Bullet(pBulletList);

		return pObj;
	}

	static CObject* Create(float _iX, float _iY, DIRECTION eDirect, float _iVel, int _iDis, int _iAddXPos, int _iAddYPos, INFO* pInfo, list<CObject*>* pBulletList )
	{
		CObject* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_iX, _iY);
		pObj->Set_Direct(eDirect);
		dynamic_cast<CMonster*>(pObj)->Set_PlInfo(pInfo);
		dynamic_cast<CMonster*>(pObj)->Set_Bullet(pBulletList);
		//회전속도
		dynamic_cast<CBossMob*>(pObj)->SetiVel((int)_iVel);
		//중심으로부터 거리
		dynamic_cast<CBossMob*>(pObj)->SetiDistance(_iDis);
		//중심이동속도
		dynamic_cast<CBossMob*>(pObj)->SetiAddX((float)_iAddXPos);
		dynamic_cast<CBossMob*>(pObj)->SetiAddY((float)_iAddYPos);

		return pObj;
	}

	static CObject* Create(float _iX, float _iY)
	{
		CObject* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_iX, _iY);

		return pObj;
	}

	static CObject* Create(float _iX, float _iY, CObject* pTarget)
	{
		CObject* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_iX, _iY);
		pObj->Set_Target(pTarget);

		return pObj;
	}
};

