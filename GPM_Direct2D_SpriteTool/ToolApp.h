#pragma once

// ======== Direct2D ========
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
// ==========================

#include <Windows.h>
#include "Bitmap.h"

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
LRESULT CALLBACK ToolWndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

class SWCToolApp
{
public:
	HINSTANCE					m_hInstance;

	ID2D1SolidColorBrush*		m_pBlackBrush;
	SWCBitmap*					m_pMyBitmap;
	// ================== :: Main Window :: ==================
	HWND						m_hWnd;
	WCHAR						m_szWindowClass[32];
	WCHAR						m_szTitle[64];

	ID2D1Bitmap*				m_pD2DMainBitmap;
	ID2D1HwndRenderTarget*		m_pMainRT;
	// ================== :: Tool Window :: ==================
	HWND						m_hToolWnd;
	WCHAR						m_szToolWindowClass[32];
	WCHAR						m_szToolTitle[64];

	ID2D1Bitmap*				m_pD2DToolBitmap;
	ID2D1HwndRenderTarget*		m_pToolRT;
	// =======================================================
	ID2D1Factory*				m_pD2D1Factory;
	IDWriteFactory*				m_pDWriteFactory;
	IDWriteTextFormat*			m_pDWriteTextFormat;

public:
	SWCToolApp();
	~SWCToolApp();

public:
	HRESULT Init(HINSTANCE hInstance, int nCmdShow);
	void Release();

	void Update();
	void Render();

public:
	LRESULT CALLBACK MessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HRESULT InitAPI(HINSTANCE hInstance, int nCmdShow);

	static LRESULT CALLBACK ToolMessageProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HRESULT InitToolAPI(HINSTANCE hInstance, int nCmdShow);

	int RunLoop();
};