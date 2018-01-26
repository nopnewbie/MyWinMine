#pragma once
#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include <Windows.h>

template <typename DERIVED_TYPE>
class CBaseClass
{
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		DERIVED_TYPE *pThis = NULL;
		if (WM_NCCREATE == uMsg)
		{
			CREATESTRUCT *pCs = reinterpret_cast<CREATESTRUCT*>(lParam);
			pThis = reinterpret_cast<DERIVED_TYPE*>(pCs->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));

			pThis->m_hWnd = hWnd;
		}
		else
		{
			pThis = reinterpret_cast<DERIVED_TYPE*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		}

		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	CBaseClass() : m_hWnd(NULL) {}
	virtual ~CBaseClass() {}

	BOOL Create(PCWSTR lpszWndName,
		DWORD dwStyle, DWORD dwExStyle = 0,
		int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT,
		HWND hWndParent = NULL, HMENU hMenu = NULL
	)
	{
		WNDCLASS wc = { 0 };
		wc.lpfnWndProc = CBaseClass::WndProc;
		wc.lpszClassName = this->ClassName();
		wc.hInstance = ::GetModuleHandle(NULL);

		::RegisterClass(&wc);

		m_hWnd = CreateWindowEx(
			dwExStyle,
			this->ClassName(),
			lpszWndName,
			dwStyle,
			x, y, nWidth, nHeight,
			hWndParent, hMenu,
			::GetModuleHandle(NULL),
			static_cast<LPVOID>(this)
		);

		return (m_hWnd ? TRUE : FALSE);
	}

protected:
	virtual PCWSTR ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT, WPARAM, LPARAM) = 0;

	HWND m_hWnd;

};

