#pragma once

class CRes
{
public:
	CRes();
	~CRes();

public:
	void		SetKey(wstring _key) { m_strKey = _key; }
	void		SetRelativePath(const wstring _path) { m_strRelativePath = _path; }

public:
	const wstring		GetKey() { return m_strKey; }
	const wstring		GetRelativePath() { return m_strRelativePath; }


private:
	wstring m_strKey;
	wstring m_strRelativePath;

};

