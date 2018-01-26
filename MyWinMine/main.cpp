#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include <Windows.h>
#include "MineWnd.h"
#include "MineConfiguration.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pszCmdLine, int nCmdShow)
{
	CMineWnd mineWnd;
	
	RECT rect = { 0 };
	rect.right = MINE_BASE_WIDTH;
	rect.bottom = MINE_BASE_HEIGHT;
	rect.left = 0;
	rect.top = 0;
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX, FALSE);

	BOOL bResult = mineWnd.Create(MINE_WND_TITLE,
		WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX,
		0,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top,
		NULL,
		NULL
	);
	if (!bResult)
	{
		MessageBox(NULL, L"Create window failed.", L"Error", MB_OK);
		return 0;
	}

	::ShowWindow(mineWnd.GetWndHandle(), nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}