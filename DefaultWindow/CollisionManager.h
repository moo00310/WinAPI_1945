#pragma once
#include "Object.h"

class CCollisionManager
{
public:
	CCollisionManager();
	~CCollisionManager();

public:
	static void Collision_Rect(list<CObject*> pDst, list<CObject*> pSrc);
	static void Collision_Circle(list<CObject*> _Dst, list<CObject*> _Src, bool* _isWin);
	static void Collision_Circle2(list<CObject*> _Dst, list<CObject*> _Src);
	static void Collision_Item(CObject* _pPlayer, list<CObject*> _Src, int ItemArray[ITEM_END]);
	static void Collision_Player(CObject* _pPlayer, list<CObject*> _Src);
	static void Collision_Boom(CObject* _Boom, list<CObject*> _Src);
};

