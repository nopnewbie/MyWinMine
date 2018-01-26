#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include "MineWnd.h"
#include "MineConfiguration.h"
#include "resource.h"

HWND CMineWnd::GetWndHandle() const
{
	return m_hWnd;
}

LRESULT CMineWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		return this->OnCreate(wParam, lParam);

	case WM_PAINT:
		return this->OnPaint(wParam, lParam);

	case WM_LBUTTONDOWN:
		return this->OnLBtnDown(wParam, lParam);

	case WM_LBUTTONUP:
		return this->OnLBtnUp(wParam, lParam);

	case WM_RBUTTONDOWN:
		return this->OnRBtnDown(wParam, lParam);

	case WM_SIZE:
		return this->OnSize(wParam, lParam);

	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

PCWSTR CMineWnd::ClassName() const
{
	return L"MyWinMine";
}

LRESULT CMineWnd::OnCreate(WPARAM wParam, LPARAM lParam)
{
	m_hBitmap = LoadBitmap(::GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BMP_CELL));
	GetObject(m_hBitmap, sizeof(m_bitmap), &m_bitmap);
	m_cxSource = m_bitmap.bmWidth;
	m_cySource = m_bitmap.bmHeight;

	return 0;
}

LRESULT CMineWnd::OnPaint(WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(m_hWnd, &ps);
	const int row = MINE_BASIC_ROW;
	const int col = MINE_BASIC_COL;
	// ??
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem, m_hBitmap);
	// paint cells
	for (int r = 0; r < row; ++r)
	{
		int x = r * m_cxSource;
		for (int c = 0; c < col; ++c)
		{
			int y = c * m_cySource / 16;
			// read mine cell datas and according to it to paint
			BitBlt(hdc, x, y, m_cxSource, m_cySource / 16, hdcMem, 0, 0, SRCCOPY);
		}
	}

	DeleteDC(hdcMem);
	EndPaint(m_hWnd, &ps);

	return 0;
}

LRESULT CMineWnd::OnLBtnDown(WPARAM wParam, LPARAM lParam)
{

	return 0;
}

LRESULT CMineWnd::OnLBtnUp(WPARAM, LPARAM)
{
	return LRESULT();
}

LRESULT CMineWnd::OnRBtnDown(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CMineWnd::OnSize(WPARAM wParam, LPARAM lParam)
{
	m_cxClient = LOWORD(lParam);
	m_cyClient = HIWORD(lParam);
	return 0;
}
