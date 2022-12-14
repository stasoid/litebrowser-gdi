#include "globals.h"
#include "BrowserWnd.h"
#include "HtmlViewWnd.h"

CBrowserWnd::CBrowserWnd(HINSTANCE hInst)
{
	m_hInst		= hInst;
	m_hWnd		= NULL;
	m_view		= new CHTMLViewWnd(hInst, this);

	WNDCLASS wc;
	if(!GetClassInfo(m_hInst, BROWSERWND_CLASS, &wc))
	{
		ZeroMemory(&wc, sizeof(wc));
		wc.style          = CS_DBLCLKS /*| CS_HREDRAW | CS_VREDRAW*/;
		wc.lpfnWndProc    = (WNDPROC)CBrowserWnd::WndProc;
		wc.cbClsExtra     = 0;
		wc.cbWndExtra     = 0;
		wc.hInstance      = m_hInst;
		wc.hIcon          = NULL;
		wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground  = (HBRUSH) (COLOR_WINDOW + 1);
		wc.lpszMenuName   = NULL;
		wc.lpszClassName  = BROWSERWND_CLASS;

		RegisterClass(&wc);
	}
}

CBrowserWnd::~CBrowserWnd(void)
{
	if(m_view)		delete m_view;
}

LRESULT CALLBACK CBrowserWnd::WndProc( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	CBrowserWnd* pThis = NULL;
	if(IsWindow(hWnd))
	{
		pThis = (CBrowserWnd*)GetProp(hWnd, TEXT("browser_this"));
		if(pThis && pThis->m_hWnd != hWnd)
		{
			pThis = NULL;
		}
	}

	if(pThis || uMessage == WM_CREATE)
	{
		switch (uMessage)
		{
		case WM_ERASEBKGND:
			return TRUE;
		case WM_CREATE:
			{
				LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
				pThis = (CBrowserWnd*)(lpcs->lpCreateParams);
				SetProp(hWnd, TEXT("browser_this"), (HANDLE) pThis);
				pThis->m_hWnd = hWnd;
				pThis->OnCreate();
			}
			break;
		case WM_SIZE:
			pThis->OnSize(LOWORD(lParam), HIWORD(lParam));
			return 0;
		case WM_DESTROY:
			RemoveProp(hWnd, TEXT("browser_this"));
			pThis->OnDestroy();
			delete pThis;
			return 0;
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		case WM_ACTIVATE:
			if(LOWORD(wParam) != WA_INACTIVE)
			{
				SetFocus(pThis->m_view->wnd());
			}
			return 0;
		}
	}

	return DefWindowProc(hWnd, uMessage, wParam, lParam);
}

void CBrowserWnd::OnCreate()
{
	RECT rcClient;
	GetClientRect(m_hWnd, &rcClient);
	m_view->create(rcClient.left, rcClient.top, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, m_hWnd);
	SetFocus(m_view->wnd());
}

void CBrowserWnd::OnSize( int width, int height )
{
	RECT rcClient;
	GetClientRect(m_hWnd, &rcClient);
	SetWindowPos(m_view->wnd(), NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, SWP_NOZORDER);
	UpdateWindow(m_view->wnd());
}

void CBrowserWnd::OnDestroy()
{

}

void CBrowserWnd::create()
{
	m_hWnd = CreateWindow(BROWSERWND_CLASS, L"Light HTML", WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, m_hInst, (LPVOID) this);

	ShowWindow(m_hWnd, SW_SHOW);
}

void CBrowserWnd::open( LPCWSTR path )
{
	if(m_view)
	{
		m_view->open(path, true);
	}
}

void CBrowserWnd::back()
{
	if(m_view)
	{
		m_view->back();
	}
}

void CBrowserWnd::forward()
{
	if(m_view)
	{
		m_view->forward();
	}
}

void CBrowserWnd::reload()
{
	if(m_view)
	{
		m_view->refresh();
	}
}

void CBrowserWnd::calc_time(int calc_repeat)
{
	if (m_view)
	{
		m_view->render(TRUE, TRUE, calc_repeat);
	}
}

void CBrowserWnd::calc_redraw(int calc_repeat)
{
	if (m_view)
	{
		m_view->calc_draw(calc_repeat);
	}
}

void CBrowserWnd::on_page_loaded(LPCWSTR url)
{
	if (m_view)
	{
		SetFocus(m_view->wnd());
	}
}
