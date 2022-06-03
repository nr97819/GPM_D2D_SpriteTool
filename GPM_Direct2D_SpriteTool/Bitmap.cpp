#include "Bitmap.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib") // WIC Lib

#include <wchar.h>
#include "D2DCore.h"


SWCBitmap::SWCBitmap()
	: m_pD2DMainBitmap(nullptr)
	, m_pD2DToolBitmap(nullptr)
{}

SWCBitmap::~SWCBitmap()
{}

HRESULT SWCBitmap::CreateMain(const wstring& _wsFileName)
{
	HRESULT hr = S_OK;

	m_pD2DMainBitmap = *(SWCD2DCore::GetInst()->CreateMainD2D1Bitmap(_wsFileName));

	return S_OK;
}

HRESULT SWCBitmap::CreateTool(const wstring& _wsFileName)
{
	HRESULT hr = S_OK;

	m_pD2DToolBitmap = *(SWCD2DCore::GetInst()->CreateToolD2D1Bitmap(_wsFileName));

	return S_OK;
}

void SWCBitmap::Release()
{
	// 해제 불가능한 이유를 모르겠다.
	
	//if (m_pD2DMainBitmap) { m_pD2DMainBitmap->Release(); m_pD2DMainBitmap = nullptr; }
	//if (m_pD2DToolBitmap) { m_pD2DToolBitmap->Release(); m_pD2DToolBitmap = nullptr; }

	if (nullptr != this)
		delete this;
}
