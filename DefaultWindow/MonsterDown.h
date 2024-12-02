#pragma once
#include "Monster.h"
class CMonsterDown : public CMonster
{
public:
	CMonsterDown();
	~CMonsterDown();

public:
	int Update() override;
	void Late_Update() override;
	void Release() override;

};