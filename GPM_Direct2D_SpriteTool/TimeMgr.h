#pragma once

#include <Windows.h>

class CTimeMgr
{
private:
	LARGE_INTEGER		m_llCurCount;
	LARGE_INTEGER		m_llPrevCount;
	LARGE_INTEGER		m_llFrequency;

	double				m_dDT;
	double				m_dAcc;
	UINT				m_iCallCount;
	UINT				m_iFPS;

private:
	CTimeMgr();
	~CTimeMgr();

public:
	static CTimeMgr* GetInst()
	{
		static CTimeMgr m_inst;
		return &m_inst;
	}

	void Init();
	void Update();
	void Release();

public:
	double GetDT() { return m_dDT; }
};

