#pragma once
#include "Object.h"
#include "Player.h"
#include "Mouse.h"

class SelectScene
{
public:
	SelectScene();
	~SelectScene();

public:
	void Initilaize();
	void Update();
	CObject* Late_Update();
	void Render();
	void Release();

	void SelectPlayer();

private:
	HDC m_hDC;
	CObject* m_pPlayer;
	CObject* m_Mouse;

	RECT m_tBox1;
	RECT m_tBox2;
	RECT m_AllBox;

	TCHAR szBuf1[32];

	bool isStart;
};

