#pragma once

// ======== Direct2D ========
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
// ==========================

#include "Bitmap.h"

class CToolApp
{
public:
	HWND						m_hWnd;
	HINSTANCE					m_hInstance;
	WCHAR						m_szWindowClass[32];
	WCHAR						m_szTitle[64];

	ID2D1Factory*				m_pD2D1Factory;
	IDWriteFactory*				m_pDWriteFactory;
	IDWriteTextFormat*			m_pDWriteTextFormat;

	CBitmap*					m_pMyBitmap;
	ID2D1Bitmap*				m_pBitmap;
	ID2D1HwndRenderTarget*		m_pRenderTarget;
	ID2D1SolidColorBrush*		m_pBlackBrush;

public:
	CToolApp();
	~CToolApp();

public:
	HRESULT Init(HINSTANCE hInstance, int nCmdShow);
	void Release();
	void Update();
	void Render();

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HRESULT InitAPI(HINSTANCE hInstance, int nCmdShow);

	static LRESULT CALLBACK ToolWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HRESULT InitToolAPI(HINSTANCE hInstance, int nCmdShow);

	int RunLoop();
};