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
	ID2D1Bitmap*			m_pD2DMainBitmap;
	ID2D1Bitmap*			m_pD2DToolBitmap;

public:
	SWCBitmap();
	~SWCBitmap();

public:
	HRESULT CreateMain(const wstring& _wsFileName);
	HRESULT CreateTool(const wstring& _wsFileName);
	void Release();

public:
	ID2D1Bitmap** GetMainBitmap() { return &m_pD2DMainBitmap; }
	ID2D1Bitmap** GetToolBitmap() { return &m_pD2DToolBitmap; }
};

