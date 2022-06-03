#include "ToolApp.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib") // WIC Lib

#include <wchar.h>
#include <string>
using std::wstring;

#include "D2DCore.h"
#include "TimeMgr.h"

SWCToolApp::SWCToolApp()
	: m_pD2D1Factory(nullptr)
	, m_pDWriteFactory(nullptr)
	, m_pDWriteTextFormat(nullptr)
	, m_pBlackBrush(nullptr)
	, m_hInstance(0)

	// Main
	, m_hWnd(0)
	, m_pMainRT(nullptr)
	, m_szWindowClass{}
	, m_szTitle{}
	, m_pD2DMainBitmap(nullptr)
	, m_pMyBitmap(nullptr)

	// Tool
	, m_hToolWnd(0)
	, m_pToolRT(nullptr)
	, m_szToolWindowClass{}
	, m_szToolTitle{}
	, m_pD2DToolBitmap(nullptr)
	//, m_pToolBitmap(nullptr)
{}

SWCToolApp::~SWCToolApp()
{}

HRESULT SWCToolApp::Init(HINSTANCE hInstance, int nCmdShow)
{
	HRESULT hr = S_OK;

	// ================== :: Main Window :: ==================
	wcscpy_s(m_szWindowClass, ARRAYSIZE(L"MainApp"), L"MainApp");
	wcscpy_s(m_szTitle, ARRAYSIZE(L"Main Application"), L"Main Application");

	m_pMyBitmap = new SWCBitmap();
	const wstring& wsFileName = L"midnight.png";
	const wstring& wsFileName_woman = L"woman.png";

	hr = InitAPI(hInstance, nCmdShow);
	if (FAILED(hr)) return E_FAIL;

	// ================== :: Tool Window :: ==================
	wcscpy_s(m_szToolWindowClass, ARRAYSIZE(L"ToolApp"), L"ToolApp");
	wcscpy_s(m_szToolTitle, ARRAYSIZE(L"Tool Application"), L"Tool Application");

	hr = InitToolAPI(hInstance, nCmdShow);
	if (FAILED(hr)) return E_FAIL;
	// =======================================================

	/*m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };*/
	RECT rtMain = { 0, 0, 1000, 700 };
	RECT rtTool = { 0, 0, 400, 700 };
	
	AdjustWindowRect(&rtMain, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rtMain.right - rtMain.left, rtMain.bottom - rtMain.top, 0);
	
	AdjustWindowRect(&rtTool, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hToolWnd, nullptr, (100 + rtMain.right), 100, rtTool.right - rtTool.left, rtTool.bottom - rtTool.top, 0);
	// =======================================================


	hr = SWCD2DCore::GetInst()->InitMain(m_hWnd);
	if (FAILED(hr)) return E_FAIL;
	hr = SWCD2DCore::GetInst()->InitTool(m_hToolWnd);
	if (FAILED(hr)) return E_FAIL;


	hr = m_pMyBitmap->CreateMain(wsFileName);
	if (FAILED(hr)) return E_FAIL;
	hr = m_pMyBitmap->CreateTool(wsFileName_woman);
	if (FAILED(hr)) return E_FAIL;


	//hr = m_pToolBitmap->CreateTool(wsFileName); // 얘는 추후에 지워야 함 !!!!
	//if (FAILED(hr)) return E_FAIL;

	// Singletom
	SWCTimeMgr::GetInst()->Init();
	/*CKeyMgr::GetInst()->Init();
	CAnimMgr::GetInst()->Init();*/


	// D2DCore에서 만들어준 거니까, 초기화는 D2DCore에서 하는게 맞는건지?
	m_pD2D1Factory = *(SWCD2DCore::GetInst()->CreateMyD2D1Factory());
	m_pDWriteFactory = *(SWCD2DCore::GetInst()->CreateMyDWriteFactory());
	m_pDWriteTextFormat = *(SWCD2DCore::GetInst()->CreateMyTextFormat(L"Gabriola", 50));

	// RT 생성 및 초기화
	m_pMainRT = *(SWCD2DCore::GetInst()->CreateMainRenderTarget());
	m_pToolRT = *(SWCD2DCore::GetInst()->CreateToolRenderTarget());

	// Bitmap 생성 및 초기화
	m_pD2DMainBitmap = *(m_pMyBitmap->GetMainBitmap());
	m_pD2DToolBitmap = *(m_pMyBitmap->GetToolBitmap()); // Tool 비트맵 추가

	// Sprite 초기화 (애니메이션에 있어서, 이제 지워도 됨)
	//m_sprite_sample = new CSprite();
	//m_sprite_sample->Init(m_pBitmap, 0.f, 0.f, 784.f, 320.f);

	/*AnimationProperty sAnimProperty = {};
	sAnimProperty._bitmap = m_pBitmap;
	sAnimProperty._iTimes = 4;
	sAnimProperty._startX = 0.f;
	sAnimProperty._startY = 0.f;
	sAnimProperty._deltaX = 789.f;
	sAnimProperty._deltaY = 325.f;
	sAnimProperty._width = 784.f;
	sAnimProperty._height = 320.f;
	sAnimProperty._rows = 2;
	sAnimProperty._columns = 2;
	sAnimProperty._interval = 0.f;

	CAnimMgr::GetInst()->CreateAnimation((UINT)ANIM_INDEX::MIDNIGHT, sAnimProperty);*/

	//m_pMainRT->CreateSolidColorBrush(
	//	D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
	//// Tool은 브러쉬 안만듦
	//m_pToolRT->CreateSolidColorBrush(
	//	D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);

	return S_OK;
}

void SWCToolApp::Release()
{
	if (m_pMyBitmap) { m_pMyBitmap->Release(); m_pMyBitmap = nullptr; }
	//if (m_pToolBitmap) { m_pMyBitmap->Release(); m_pMyBitmap = nullptr; }

	if (m_pBlackBrush) { m_pBlackBrush->Release(); m_pBlackBrush = nullptr; }

	SWCTimeMgr::GetInst()->Release();
	/*CKeyMgr::GetInst()->Release();
	CAnimMgr::GetInst()->Release();*/
}

void SWCToolApp::Update()
{
	// 업데이트 관련 코드 작성 (애니메이션 추가됨)
	SWCTimeMgr::GetInst()->Update();
	/*CKeyMgr::GetInst()->Update();
	CAnimMgr::GetInst()->Update();*/
}

void SWCToolApp::Render()
{
	m_pMainRT->BeginDraw();
	// ============================= [ Main Draw ] ==================================
	D2D1_SIZE_F rtSize = m_pMainRT->GetSize();
	m_pMainRT->Clear(D2D1::ColorF(D2D1::ColorF::White));
	/*m_pMainRT->DrawTextW(L"SAMPLE_TEXT", ARRAYSIZE(L"SAMPLE_TEXT") - 1,
		m_pDWriteTextFormat, D2D1::RectF(50, 50, rtSize.width, rtSize.height),
		m_pBlackBrush);*/

	// Bitmap
	m_pMainRT->DrawBitmap(m_pD2DMainBitmap, D2D1::RectF(10.f, 10.f,
		10.f + m_pD2DMainBitmap->GetSize().width,
		10.f + m_pD2DMainBitmap->GetSize().height),
		0.2f, // Alpha 값
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(0.f, 0.f, m_pD2DMainBitmap->GetSize().width, m_pD2DMainBitmap->GetSize().height));
	//======================================================================================
	m_pMainRT->EndDraw();

	m_pToolRT->BeginDraw();
	// ============================= [ Tool Draw ] ==================================
	D2D1_SIZE_F rtToolSize = m_pToolRT->GetSize();
	m_pToolRT->Clear(D2D1::ColorF(D2D1::ColorF::White));
	/*m_pToolRT->DrawTextW(L"SAMPLE_TEXT", ARRAYSIZE(L"SAMPLE_TEXT") - 1,
		m_pDWriteTextFormat, D2D1::RectF(50, 50, rtToolSize.width, rtToolSize.height),
		m_pBlackBrush);*/

	// Bitmap
	m_pToolRT->DrawBitmap(m_pD2DToolBitmap, D2D1::RectF(10.f, 10.f,
		10.f + m_pD2DToolBitmap->GetSize().width,
		10.f + m_pD2DToolBitmap->GetSize().height),
		0.2f, // Alpha 값
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(0.f, 0.f, m_pD2DToolBitmap->GetSize().width, m_pD2DToolBitmap->GetSize().height));
	//======================================================================================
	m_pToolRT->EndDraw();
}

HRESULT SWCToolApp::InitAPI(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR); // 클래스화 수정됨
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			L"Call to RegisterClassEx failed!",
			L"Windows Desktop Guided Tour",
			NULL);

		return E_FAIL;
	}

	m_hInstance = hInstance;

	m_hWnd = CreateWindow(
		m_szWindowClass,
		m_szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		700, 700,
		NULL,
		NULL,
		hInstance,
		this); // 클래스화 수정됨

	if (!m_hWnd)
	{
		MessageBox(NULL,
			L"Call to CreateWindow failed!",
			L"Windows Desktop Guided Tour",
			NULL);

		return E_FAIL;
	}

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return S_OK;
}

HRESULT SWCToolApp::InitToolAPI(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = ToolWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR); // 클래스화 수정됨
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_szToolWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			L"Call to RegisterClassEx failed!",
			L"Windows Desktop Guided Tour",
			NULL);

		return E_FAIL;
	}

	m_hInstance = hInstance;

	m_hToolWnd = CreateWindow(
		m_szToolWindowClass,
		m_szToolTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		400, 700,
		NULL,
		NULL,
		hInstance,
		this); // 클래스화 수정됨

	if (!m_hToolWnd)
	{
		MessageBox(NULL,
			L"Call to CreateWindow failed!",
			L"Windows Desktop Guided Tour",
			NULL);

		return E_FAIL;
	}

	ShowWindow(m_hToolWnd, nCmdShow);
	UpdateWindow(m_hToolWnd);

	return S_OK;
}

int SWCToolApp::RunLoop()
{
	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
			Render();
		}
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK SWCToolApp::MessageProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	int width = 0;
	int height = 0;

	switch (_message)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(_hWnd, &ps);
		EndPaint(_hWnd, &ps);
		break;

	case WM_MOUSEMOVE:
	{
		WORD x = HIWORD(_lParam);
		WORD y = LOWORD(_lParam);

		hdc = GetDC(_hWnd);
		COLORREF color = GetPixel(hdc, x, y);
		wchar_t str[100];
		wsprintf(str, L"(%d, %d - %x)", x, y, color);
		TextOut(hdc, 10, 10, str, wcslen(str));
		ReleaseDC(_hWnd, hdc);
	}
	break;

	case WM_SIZE:
		//Resize
	{
		width = LOWORD(_lParam);
		height = HIWORD(_lParam);

		if (SWCD2DCore::GetInst()->GetRT())
			SWCD2DCore::GetInst()->GetRT()->Resize({ (UINT32)width, (UINT32)height });
	}
	break;

	case WM_COMMAND:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(_hWnd, _message, _wParam, _lParam);
		break;
	}
	return 0;
}

LRESULT CALLBACK SWCToolApp::ToolMessageProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	int width = 0;
	int height = 0;

	switch (_message)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(_hWnd, &ps);
		EndPaint(_hWnd, &ps);
		break;

	case WM_MOUSEMOVE:
	{
		WORD x = HIWORD(_lParam);
		WORD y = LOWORD(_lParam);

		hdc = GetDC(_hWnd);
		COLORREF color = GetPixel(hdc, x, y);
		wchar_t str[100];
		wsprintf(str, L"(%d, %d - %x)", x, y, color);
		TextOut(hdc, 10, 10, str, wcslen(str));
		ReleaseDC(_hWnd, hdc);
	}
	break;

	case WM_SIZE:
		//Resize
	{
		width = LOWORD(_lParam);
		height = HIWORD(_lParam);

		if (SWCD2DCore::GetInst()->GetRT())
			SWCD2DCore::GetInst()->GetRT()->Resize({ (UINT32)width, (UINT32)height });
	}
	break;

	case WM_COMMAND:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(_hWnd, _message, _wParam, _lParam);
		break;
	}
	return 0;
}

// ===================== :: global Procdure Func :: =====================
LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	SWCToolApp* pToolApp = nullptr;
	if (_message == WM_NCCREATE)
	{
		LPCREATESTRUCT pCS = (LPCREATESTRUCT)_lParam;
		SetLastError(0); // 이전 오류값 지우기
		pToolApp = reinterpret_cast<SWCToolApp*>(pCS->lpCreateParams);
		if (!SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)pToolApp))
		{
			if (GetLastError() != NULL)
				return E_FAIL;
		}
	}
	else
	{
		pToolApp = reinterpret_cast<SWCToolApp*>(GetWindowLongPtr(_hWnd, GWLP_USERDATA));
	}

	// Proc 함수와 연결된 부분
	if (pToolApp)
	{
		return pToolApp->MessageProc(_hWnd, _message, _wParam, _lParam);
	}

	return DefWindowProc(_hWnd, _message, _wParam, _lParam);
}

LRESULT CALLBACK ToolWndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	SWCToolApp* pToolApp = nullptr;
	if (_message == WM_NCCREATE)
	{
		LPCREATESTRUCT pCS = (LPCREATESTRUCT)_lParam;
		SetLastError(0); // 이전 오류값 지우기
		pToolApp = reinterpret_cast<SWCToolApp*>(pCS->lpCreateParams);
		if (!SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)pToolApp))
		{
			if (GetLastError() != NULL)
				return E_FAIL;
		}
	}
	else
	{
		pToolApp = reinterpret_cast<SWCToolApp*>(GetWindowLongPtr(_hWnd, GWLP_USERDATA));
	}

	// Proc 함수와 연결된 부분
	if (pToolApp)
	{
		return pToolApp->MessageProc(_hWnd, _message, _wParam, _lParam);
	}

	return DefWindowProc(_hWnd, _message, _wParam, _lParam);
}