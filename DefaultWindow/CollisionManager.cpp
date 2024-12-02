#include "pch.h"
#include "CollisionManager.h"
#include "AbstractFactory.h"
#include "BossMob.h"
#include "MonsterCircle.h"
#include "Item.h"
#include "Player.h"

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Collision_Rect(list<CObject*> pDst, list<CObject*> pSrc)
{
	RECT rc;

	for (auto& Dst : pDst)
	{
		CBossMob* monsterBoss = dynamic_cast<CBossMob*>(Dst);
		if (monsterBoss)
		{
			for (auto& Src : pSrc)
			{
				if (IntersectRect(&rc, Dst->Get_Rect(), Src->Get_Rect()))
				{
					if (monsterBoss)
					{
						if (0 >= dynamic_cast<CBossMob*>(Dst)->GetiHp())
						{
							Dst->Set_Dead();
							Src->Set_Dead();
						}
						else
						{
							dynamic_cast<CBossMob*>(Dst)->AddiHp(-1);
							Src->Set_Dead();
						}
					}
					else
					{
						Dst->Set_Dead();
						Src->Set_Dead();
					}
				}
			}
		}
	}
}

void CCollisionManager::Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src, bool* _isWin)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			float iX = ((Dst->Get_Info().fX - Src->Get_Info().fX));
			iX *= iX;
			float iY = (Dst->Get_Info().fY - Src->Get_Info().fY);
			iY *= iY;

			float iRange = (Dst->Get_Info().fCX * 0.5f) + (Src->Get_Info().fCY * 0.5f);
			iRange *= iRange;

			if ((iX + iY) <= iRange)
			{
				CBossMob* monsterBoss = dynamic_cast<CBossMob*>(Dst);
				CMonsterCircle* monsterCircle = dynamic_cast<CMonsterCircle*>(Dst);
				if (monsterCircle)
				{
					Dst->Set_Dead();
					Src->Set_Dead();
				}
				else if (monsterBoss)
				{
					if (0 >= dynamic_cast<CBossMob*>(Dst)->GetiHp())
					{
						int BossHp = dynamic_cast<CBossMob*>(Dst)->GetiHp();
						*_isWin = true;
						Dst->Set_Dead();
						Src->Set_Dead();
					}
					else
					{
						dynamic_cast<CBossMob*>(Dst)->AddiHp(-1);
						//Src->Set_Pos(-100, -100);
						Src->Set_Dead();
					}
				}
				else
				{
					Dst->Set_Dead();
					Src->Set_Dead();
				}
			}
		}
	}
}

void CCollisionManager::Collision_Circle2(list<CObject*> _Dst, list<CObject*> _Src)
{
	for (auto& Dst : _Dst)
	{
		CMonsterCircle* monsterCircle = dynamic_cast<CMonsterCircle*>(Dst);

		if (monsterCircle)

		{
			for (auto& Src : _Src)
			{
				float iX = ((monsterCircle->GettCircle().fX - Src->Get_Info().fX));
				iX *= iX;
				float iY = (monsterCircle->GettCircle().fY - Src->Get_Info().fY);
				iY *= iY;

				float iRange = (monsterCircle->GettCircle().fCX * 0.5f) + (Src->Get_Info().fCY * 0.5f);
				iRange *= iRange;


				if ((iX + iY) <= iRange)
				{
					Dst->Set_Dead();
					Src->Set_Dead();
				}
			}
		}
	}
}

void CCollisionManager::Collision_Player(CObject* _pPlayer, list<CObject*> _Src)
{
	if (_pPlayer->Get_Dead()) return;
	for (auto& Src : _Src)
	{
		float iX = ((_pPlayer->Get_Info().fX - Src->Get_Info().fX));
		iX *= iX;
		float iY = (_pPlayer->Get_Info().fY - Src->Get_Info().fY);
		iY *= iY;

		float iRange = ((_pPlayer->Get_Info().fCX + Src->Get_Info().fCY) * 0.5f);
		iRange *= iRange;

		if ((iX + iY) <= iRange)
		{
			Src->Set_Dead();
			if (CPlayer* Temp = dynamic_cast<CPlayer*>(_pPlayer))
			{
				Temp->SetDeadthTime(GetTickCount64());
				Temp->Clear_Pet();
				Temp->Clear_Bullet();
			}
			_pPlayer->Set_Dead();
		}
	}
}

void CCollisionManager::Collision_Boom(CObject* _Boom, list<CObject*> _Src)
{
	for (auto& Src : _Src)
	{
		float iX = ((_Boom->Get_Info().fX - Src->Get_Info().fX));
		iX *= iX;
		float iY = (_Boom->Get_Info().fY - Src->Get_Info().fY);
		iY *= iY;

		float iRange = ((_Boom->Get_Info().fCX + Src->Get_Info().fCY) * 0.5f);
		iRange *= iRange;

		if ((iX + iY) <= iRange)
		{
			Src->Set_Dead();
		}
	}
}

void CCollisionManager::Collision_Item(CObject* _pPlayer, list<CObject*> _Src, int ItemArray[ITEM_END])
{
	if (_pPlayer->Get_Dead()) return;
	for (auto& Src : _Src)
	{
		float iX = ((_pPlayer->Get_Info().fX - Src->Get_Info().fX));
		iX *= iX;
		float iY = (_pPlayer->Get_Info().fY - Src->Get_Info().fY);
		iY *= iY;

		float iRange = (_pPlayer->Get_Info().fCX + Src->Get_Info().fCY * 0.5f);
		iRange *= iRange;

		if ((iX + iY) <= iRange)
		{
			ITEM_ID ID = dynamic_cast<CItem*>(Src)->GetItemID();
			switch (ID)
			{
			case ITEM_ATTACK:
				if (ItemArray[ITEM_ATTACK] < 3)
				{
					ItemArray[ITEM_ATTACK] += 1;
					dynamic_cast<CPlayer*>(_pPlayer)->Set_Bullet_Type();
				}
				break;
			case ITEM_PET1:
			{
				if (ItemArray[ITEM_PET1] < 3)
				{
					ItemArray[ITEM_PET1] += 1;
					int iPetCount = ItemArray[ITEM_PET1]; // 문제점 각도를 제대로 못구함
					dynamic_cast<CPlayer*>(_pPlayer)->Create_Rot_Pet((float)360 / iPetCount);
				}
				break;
			}
			case ITEM_PET2:
				if (ItemArray[ITEM_PET2] < 3)
				{
					ItemArray[ITEM_PET2] += 1;
					dynamic_cast<CPlayer*>(_pPlayer)->Create_Cur_Pet();
				}
				break;
			case ITEM_PET3:
				if (ItemArray[ITEM_PET3] < 3)
				{
					ItemArray[ITEM_PET3] += 1;
					dynamic_cast<CPlayer*>(_pPlayer)->Create_Tra_Pet();
				}
				break;
			case ITEM_BOOM:
			{
				if (ItemArray[ITEM_BOOM] < 3)
					ItemArray[ITEM_BOOM] += 1;
				break;
			}
			case ITEM_END:
				break;
			}
				
			Src->Set_Dead();
		}
	}
}
