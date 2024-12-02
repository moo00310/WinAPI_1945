#pragma once
class CResourceMgr
{
private:
	CResourceMgr();
	~CResourceMgr();

public:
	static CResourceMgr* GetInst()
	{
		static CResourceMgr res;

		return &res;
	}

public:
	void		Initialize();

public:
	const wchar_t* GetContentPath() { return m_szContenPath; }

private:
	wchar_t m_szContenPath[255];
};

