#pragma once
#include "define.h"
#include "Object.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize(CObject* pPlayer);
	void Update();
	void Late_Update();
	void Render();
	void Release();
public:
	void UITextPrint(HDC _hdc, const WCHAR* _string, POINT pos)
	{
		TCHAR szBuf[32] = L"";
		wsprintf(szBuf, _string);
		TextOut(_hdc, pos.x, pos.y, szBuf, lstrlen(szBuf));
	}
private:
	HDC m_hDC;

	list<CObject*> m_ObjList[OBJ_END];

	int m_iItemCount[ITEM_END];
	
	ULONG64 m_dwTime;
	int   m_iFPS;
	int   m_iScore;
	TCHAR m_szFPS[16];
	
	ULONG64 m_ullItemTime;
	ULONG64 m_ullTime;
	ULONG64	m_ullTimeCount;
	ULONG64	m_ullActionCount;

	HBITMAP m_hBit;
	HDC		m_memDC;
	
	int m_iDeadthCount;
	bool m_bisWin;

	inline void Mop_Down(const int& _ActionCountStart, const int& _ActionCountEnd, const BULLET_ID& _BulletType = BUL_MON1, const int& _BulletCooltime = 1000 + rand() % 1500);
	inline void Mop_Lumped(const int& _ActionCountStart, const int& _ActionCountEnd, const BULLET_ID& _BulletType = BUL_MON1, const int& _BulletCooltime = 300, const bool& _isBulleteToPl = false);
	inline void Mop_Up(const int& _ActionCountStart, const int& _ActionCountEnd, const BULLET_ID& _BulletType = BUL_MON3, const int& _BulletCooltime = 1000 + rand() % 1000);
	inline void Mop_Horizon(const int& _ActionCountStart, const int& _ActionCountEnd, const BULLET_ID& _BulletType = BUL_MON2, const int& _BulletCooltime = 900);
	inline void Mop_CIrcle(const int& _ActionCountStart, const int& _ActionCountEnd);
	inline void Mop_Boss(const int& _ActionCountStart, const int& _ActionCountEnd);
};

