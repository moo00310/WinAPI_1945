#pragma once
#include "Object.h"

class CItem : public CObject
{
public:
	CItem(ITEM_ID _eItemType) : m_eItemType(_eItemType), m_fDegree(0), m_uLifeTime(0)
	{
		ZeroMemory(&m_szBuf, sizeof(m_szBuf));
	}
	virtual~CItem() {}

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) PURE;
	void Release() override;

	ITEM_ID GetItemID() { return m_eItemType; }

private:
	float m_fDegree;
	ULONG64 m_uLifeTime;

protected:
	ITEM_ID m_eItemType;
	TCHAR m_szBuf[32];
};


/*------------------
	ItemTypes
-------------------*/
class CBoom :public CItem
{
public:
	CBoom() :CItem(ITEM_BOOM)
	{
	}

	void Render(HDC hDC) override;
};

class CAdd_Attack : public CItem
{
public:
	CAdd_Attack() : CItem(ITEM_ATTACK)
	{
	}
	void Render(HDC hDC) override;
};

class Add_Pet : public CItem
{
public:
	Add_Pet() :CItem(static_cast<ITEM_ID>(rand()%(4 - 2 + 1) + 2))
	{
	}

	void Render(HDC hDC) override;

};


