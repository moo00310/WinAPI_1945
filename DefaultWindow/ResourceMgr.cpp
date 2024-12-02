#include "pch.h"
#include "ResourceMgr.h"
#include "define.h"

CResourceMgr::CResourceMgr() : m_szContenPath{}
{
}

CResourceMgr::~CResourceMgr()
{
}
void CResourceMgr::Initialize()
{
	GetCurrentDirectory(255, m_szContenPath);
	int iLen = (int)wcslen(m_szContenPath);

	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContenPath[i])
		{
			m_szContenPath[i] = '\0';
			break;
		}
	}

	SetWindowText(g_hWnd, m_szContenPath);
}