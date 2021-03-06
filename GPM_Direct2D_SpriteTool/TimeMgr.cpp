#include "TimeMgr.h"

#include <Windows.h>
#include <wchar.h>

#include "D2DCore.h"

SWCTimeMgr::SWCTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
	, m_iFPS(0)
{}

SWCTimeMgr::~SWCTimeMgr()
{}

void SWCTimeMgr::Init()
{
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llFrequency);
}

void SWCTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)
		/ (double)(m_llFrequency.QuadPart);

	m_llPrevCount = m_llCurCount;
	++m_iCallCount;
	m_dAcc += m_dDT;

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;

		WCHAR wsBuf[64] = {};
		swprintf_s(wsBuf, L"FPS : %d", m_iFPS);
		SetWindowText(SWCD2DCore::GetInst()->GetMainHwnd(), wsBuf);

		m_dAcc = 0;
		m_iCallCount = 0;
	}
}

void SWCTimeMgr::Release()
{
	// 해제할 내용이 아직 없음
}
