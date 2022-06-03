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
	/*: m_pD2D1Factory(nullptr)
	, m_pDWriteFactory(nullptr)
	, m_pRenderTarget(nullptr)
	, m_pDWriteTextFormat(nullptr)
	, m_pBlackBrush(nullptr)
	, m_pBitmap(nullptr)
	, m_hWnd(0)
	, m_szWindowClass{}
	, m_szTitle{}
	, m_hInstance(0)
	, m_pMyBitmap(nullptr)*/
{}

SWCToolApp::~SWCToolApp()
{}

HRESULT SWCToolApp::Init(HINSTANCE hInstance, int nCmdShow)
{
	HRESULT hr = S_OK;

	wcscpy_s(m_szWindowClass, ARRAYSIZE(L"DesktopApp"), L"DesktopApp");
	wcscpy_s(m_szTitle, ARRAYSIZE(L"Windows Desktop Guided Tour Application"), L"Windows Desktop Guided Tour Application");

	// CBitmap에서 D2DBitmap만 받아오고, CBitmap은 바로 버리기?
	m_pMyBitmap = new SWCBitmap();
	const wstring& wsFileName = L"midnight.png";

	hr = InitAPI(hInstance, nCmdShow);
	if (FAILED(hr)) return E_FAIL;

	hr = SWCD2DCore::GetInst()->Init(m_hWnd);
	if (FAILED(hr)) return E_FAIL;

	hr = m_pMyBitmap->Create(wsFileName);
	if (FAILED(hr)) return E_FAIL;


	// Singletom
	SWCTimeMgr::GetInst()->Init();
	/*CKeyMgr::GetInst()->Init();
	CAnimMgr::GetInst()->Init();*/


	// D2DCore에서 만들어준 거니까, 초기화는 D2DCore에서 하는게 맞는건지?
	m_pD2D1Factory = *(SWCD2DCore::GetInst()->CreateMyD2D1Factory());
	m_pDWriteFactory = *(SWCD2DCore::GetInst()->CreateMyDWriteFactory());
	m_pRenderTarget = *(SWCD2DCore::GetInst()->CreateMyRenderTarget());
	m_pDWriteTextFormat = *(SWCD2DCore::GetInst()->CreateMyTextFormat(L"Gabriola", 50));

	// Bitmap 초기화
	m_pBitmap = *(m_pMyBitmap->GetBitmap());

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

	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);

	return S_OK;
}

void SWCToolApp::Release()
{
	if (m_pMyBitmap) { m_pMyBitmap->Release(); m_pMyBitmap = nullptr; }

	if (m_pBlackBrush) { m_pBlackBrush->Release(); m_pBlackBrush = nullptr; }

	SWCTimeMgr::GetInst()->Release();
	/*CKeyMgr::GetInst()->Release();
	CAnimMgr::GetInst()->Release();*/
}

void SWCToolApp::Update()
{
	// 업데이트 관련 코드 작성 (애니메이션)
	SWCTimeMgr::GetInst()->Update();
	/*CKeyMgr::GetInst()->Update();
	CAnimMgr::GetInst()->Update();*/
}

void SWCToolApp::Render()
{
	m_pRenderTarget->BeginDraw();

	// ============================= [ Drawing ] ==================================
	D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	m_pRenderTarget->DrawTextW(L"SAMPLE_TEXT", ARRAYSIZE(L"SAMPLE_TEXT") - 1,
		m_pDWriteTextFormat, D2D1::RectF(50, 50, rtSize.width, rtSize.height),
		m_pBlackBrush);

	// Bitmap
	m_pRenderTarget->DrawBitmap(m_pBitmap, D2D1::RectF(10.f, 10.f,
		10.f + m_pBitmap->GetSize().width,
		10.f + m_pBitmap->GetSize().height),
		0.2f, // Alpha 값
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(0.f, 0.f, m_pBitmap->GetSize().width, m_pBitmap->GetSize().height));
	//======================================================================================

	m_pRenderTarget->EndDraw();
}

HRESULT SWCToolApp::InitAPI(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
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
		1620, 700,
		NULL,
		NULL,
		hInstance,
		NULL);

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

LRESULT CALLBACK SWCToolApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}