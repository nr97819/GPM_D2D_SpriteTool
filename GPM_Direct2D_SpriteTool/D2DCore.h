#pragma once

#include <Windows.h>

// ======== Direct2D ========
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
// ==========================

#include <string>
using std::wstring;

class SWCD2DCore
{
private:
	ID2D1Factory*				m_pD2D1Factory;
	IDWriteFactory*				m_pDWriteFactory;
	IWICImagingFactory*			m_pWICFactory;
	IDWriteTextFormat*			m_pDWriteTextFormat;
	// ============ :: Main Window :: ============
	HWND						m_hMainWnd;
	ID2D1HwndRenderTarget*		m_pMainRT;
	ID2D1Bitmap*				m_pD2DMainBitmap;
	// ============ :: Tool Window :: ============
	HWND						m_hToolWnd;
	ID2D1HwndRenderTarget*		m_pToolRT;
	ID2D1Bitmap*				m_pD2DToolBitmap;

public:
	static SWCD2DCore* GetInst()
	{
		static SWCD2DCore* m_inst = new SWCD2DCore;

		return m_inst;
	}

private:
	SWCD2DCore();
	~SWCD2DCore();

public:
	HRESULT InitMain(HWND m_hMainWnd);
	HRESULT InitTool(HWND m_hToolWnd);

	void Release();

public:
	ID2D1Factory** CreateMyD2D1Factory() { return &m_pD2D1Factory; }
	IDWriteFactory** CreateMyDWriteFactory() { return &m_pDWriteFactory; }
	IWICImagingFactory** CreateMyWICImagingFactory() { return &m_pWICFactory; }
	IDWriteTextFormat** CreateMyTextFormat(const WCHAR* _fontName, FLOAT _fontSize);

	// ============ :: Main Window :: ============
	ID2D1HwndRenderTarget** CreateMainRenderTarget() { return &m_pMainRT; }
	ID2D1Bitmap** CreateMainD2D1Bitmap(const wstring& _wsFileName);
	// ============ :: Tool Window :: ============
	ID2D1HwndRenderTarget** CreateToolRenderTarget() { return &m_pToolRT; }
	ID2D1Bitmap** CreateToolD2D1Bitmap(const wstring& _wsFileName);

public:
	ID2D1HwndRenderTarget* GetRT() { return m_pMainRT; }
	HWND GetMainHwnd() { return m_hMainWnd; }
};