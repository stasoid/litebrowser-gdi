#pragma once

#define BROWSERWND_CLASS	L"BROWSER_WINDOW"

class CHTMLViewWnd;

class CBrowserWnd
{
	HWND				m_hWnd;
	HINSTANCE			m_hInst;
	CHTMLViewWnd*		m_view;
public:
	CBrowserWnd(HINSTANCE hInst);
	virtual ~CBrowserWnd(void);

	void create();
	void open(LPCWSTR path);

	void back();
	void forward();
	void reload();
	void calc_time(int calc_repeat = 1);
	void calc_redraw(int calc_repeat = 1);
	void on_page_loaded(LPCWSTR url);

protected:
	virtual void OnCreate();
	virtual void OnSize(int width, int height);
	virtual void OnDestroy();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
};
