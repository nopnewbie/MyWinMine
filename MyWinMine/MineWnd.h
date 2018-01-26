#pragma once
#include "BaseClass.hpp"
class CMineWnd : public CBaseClass<CMineWnd>
{
public:
	CMineWnd() = default;
	~CMineWnd() = default;
	
	HWND GetWndHandle() const;
	virtual LRESULT HandleMessage(UINT, WPARAM, LPARAM) override;
	virtual PCWSTR ClassName() const override;

private:
	LRESULT OnCreate(WPARAM, LPARAM);
	LRESULT OnPaint(WPARAM, LPARAM);
	LRESULT OnLBtnDown(WPARAM, LPARAM);
	LRESULT OnLBtnUp(WPARAM, LPARAM);
	LRESULT OnRBtnDown(WPARAM, LPARAM);
	LRESULT OnSize(WPARAM, LPARAM);

	int m_cxClient;
	int m_cyClient;
	int m_cxSource;
	int m_cySource;

	BITMAP m_bitmap;
	HBITMAP m_hBitmap;

};

