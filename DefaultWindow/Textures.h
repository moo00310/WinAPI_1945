#pragma once
#include "Res.h"

class CTextures : public CRes
{
public:
	CTextures();
	~CTextures();

public:
	void Load(const wstring _filepath);

public:
	HDC					GetDC() { return m_hDc; }
	HBITMAP				GetBitmap() { return m_hBitmap; }

public:
	UINT				GetWidth() { return m_bitInfo.bmWidth; }
	UINT				GetHeight() { return m_bitInfo.bmHeight; }
	HDC					GetHDC() { return m_hDc; }

private:
	HDC		m_hDc;
	HBITMAP	m_hBitmap;
	BITMAP	m_bitInfo;

};

