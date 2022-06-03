#pragma once

// ======== Direct2D ========
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
// ==========================

#include <string>
using std::wstring;

class SWCBitmap
{
private:
	ID2D1Bitmap*			m_pBitmap;

public:
	SWCBitmap();
	~SWCBitmap();

public:
	HRESULT Create(const wstring& _wsFileName);
	void Release();

public:
	ID2D1Bitmap** GetBitmap() { return &m_pBitmap; }
};

