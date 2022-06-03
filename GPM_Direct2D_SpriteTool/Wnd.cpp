#include "Wnd.h"

#include "D2DCore.h"

CWnd::CWnd()
	: m_hWnd(0)
	, m_szWindowClass{}
	, m_szTitle{}
{
}

CWnd::~CWnd()
{
}

HRESULT CWnd::Create(HINSTANCE _hInstance, int _nCmdShow, WCHAR* _wTitle, WCHAR* _wClassName, UINT _iWidth, UINT _iHeight)
{
	// ГЊСп
	wcscpy_s(m_szWindowClass, ARRAYSIZE(L"DesktopApp"), L"DesktopApp");
	wcscpy_s(m_szTitle, ARRAYSIZE(L"Windows Desktop Guided Tour Application"), L"Windows Desktop Guided Tour Application");

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _hInstance;
	wcex.hIcon = LoadIcon(_hInstance, IDI_APPLICATION);
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

	m_hWnd = CreateWindow(
		m_szWindowClass,
		m_szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		_iWidth, _iHeight,
		NULL,
		NULL,
		_hInstance,
		NULL);

	if (!m_hWnd)
	{
		MessageBox(NULL,
			L"Call to CreateWindow failed!",
			L"Windows Desktop Guided Tour",
			NULL);

		return E_FAIL;
	}
}

LRESULT CALLBACK CWnd::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	int width = 0;
	int height = 0;

	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
	{
		WORD x = HIWORD(lParam);
		WORD y = LOWORD(lParam);

		hdc = GetDC(hWnd);
		COLORREF color = GetPixel(hdc, x, y);
		wchar_t str[100];
		wsprintf(str, L"(%d, %d - %x)", x, y, color);
		TextOut(hdc, 10, 10, str, wcslen(str));
		ReleaseDC(hWnd, hdc);
	}
	break;

	case WM_SIZE:
		width = LOWORD(lParam);
		height = HIWORD(lParam);

		if (CD2DCore::GetInst()->GetRT())
			CD2DCore::GetInst()->GetRT()->Resize({ (UINT32)width, (UINT32)height });
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
