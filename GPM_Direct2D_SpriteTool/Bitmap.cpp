#include "Bitmap.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib") // WIC Lib

#include <wchar.h>
#include "D2DCore.h"


SWCBitmap::SWCBitmap()
	: m_pBitmap(nullptr)
{}

SWCBitmap::~SWCBitmap()
{}

HRESULT SWCBitmap::Create(const wstring& _wsFileName)
{
	HRESULT hr = S_OK;

	m_pBitmap = *(SWCD2DCore::GetInst()->CreateMyD2D1Bitmap(_wsFileName));

	return S_OK;
}

void SWCBitmap::Release()
{
	// ���� �Ұ����� ������ �𸣰ڴ�.
	//if (m_pBitmap) { m_pBitmap->Release(); m_pBitmap = nullptr; }
	if (nullptr != this)
		delete this;
}
