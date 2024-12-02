#include "pch.h"
#include "Textures.h"
#include "define.h"

CTextures::CTextures()
{
}

CTextures::~CTextures()
{
	DeleteDC(m_hDc);
	DeleteObject(m_hBitmap);
}

void CTextures::Load(const wstring _filepath)
{
	m_hBitmap = (HBITMAP)LoadImage(nullptr, _filepath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBitmap);

	m_hDc = CreateCompatibleDC(g_hDC);

	HBITMAP hPreBit = (HBITMAP)SelectObject(m_hDc, m_hBitmap);
	DeleteObject(hPreBit);

	GetObject(m_hBitmap, sizeof(BITMAP), &m_bitInfo);
}

