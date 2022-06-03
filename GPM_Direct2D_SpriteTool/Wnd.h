#pragma once

#include <windows.h>

class SWCWnd
{
protected:
	HWND			m_hWnd;
	WCHAR			m_szWindowClass[32];
	WCHAR			m_szTitle[64];

public:

protected:
public:
	SWCWnd();
	~SWCWnd();

public:
	HRESULT Create(HINSTANCE _hInstance, int _nCmdShow, WCHAR* _wTitle, WCHAR* _wClassName, UINT _iWidth, UINT _iHeight);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

