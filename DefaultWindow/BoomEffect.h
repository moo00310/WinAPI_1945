#pragma once
#include "Object.h"

enum BOOMTYPE
{
	BT_CRICLE = 1,
	BT_PLANE
};
class CBoomEffect : public CObject
{
public:
	CBoomEffect(BOOMTYPE _eBoomType);
	virtual ~CBoomEffect();
public:
	void SetBullet(list<CObject*>* _bulletList) { m_bulletList = _bulletList; }

public:
	void Initialize() PURE;
	int Update() PURE;
	void Late_Update() PURE;
	void Render(HDC hDC) PURE;
	void Release() override;

protected:
	list<CObject*>* m_bulletList;
	BOOMTYPE m_eBoomType;
	ULONG64 m_uTime;
};

/// <summary>
///  BoomType
/// </summary>
class CBoomCricle : public CBoomEffect
{
public:
	CBoomCricle() : CBoomEffect(BT_CRICLE)
	{

	}
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
};
/// <summary>
///  BoomType
/// </summary>

class CBoomPlane : public CBoomEffect
{
public:
	CBoomPlane() : CBoomEffect(BT_PLANE)
	{

	}
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
};