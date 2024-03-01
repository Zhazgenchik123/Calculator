#include "afxwin.h"
#include <atlstr.h> 
#include <cstdlib>  
#include <iostream>
class CMyWindow : public CFrameWnd
{
public:
	CMyWindow()
	{
		RECT myRect;
		myRect.left = 0;
		myRect.right = 800;
		myRect.top = 0;
		myRect.bottom = 600;

		Create(NULL, "Пример MFC окна", WS_OVERLAPPEDWINDOW, myRect, nullptr, nullptr, WS_EX_WINDOWEDGE, nullptr);
		RECT buttonRect;
		buttonRect.left = 10;
		buttonRect.right = 100;
		buttonRect.top = 10;
		buttonRect.bottom = 40;
		addbtn.Create("Add", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, buttonRect, this, 1);
		minusbtn.Create("Minus", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			CRect(110, 10, 200, 40), 
			this, 2);
		multbtn.Create("Mult", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			CRect(210, 10, 300, 40),
			this, 3);
		divbtn.Create("Divide", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			CRect(310, 10, 400, 40),
			this, 4);
		RECT staticRect;
		staticRect.left = 10;
		staticRect.right = 100;
		staticRect.top = 50;
		staticRect.bottom = 70;
		myStatic.Create("This is static text", WS_CHILD | WS_VISIBLE, staticRect, this, 5);


		editBox1.Create(
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
			CRect(10, 80 + 10, 200, 80 + 30),
			this,
			6);
		editBox2.Create(
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
			CRect(10, 80 + 40, 200, 80 + 60),
			this,
			7);
		

	}
protected:

	void OnaddbtnClicked()
	{
		CString text1, text2,str ;
		editBox1.GetWindowText(text1);
		editBox2.GetWindowText(text2);
		char* strAnsi1 = (char*)CT2A(text1);
		char* strAnsi2 = (char*)CT2A(text2);
		
		double value1 = _tstof(text1);
		double value2 = _tstof(text2);
		double result = value1 + value2;
		str.Format(_T("%f"), result);
		MessageBox(str.GetString(), _T("My Application"), MB_OK | MB_ICONINFORMATION);
	}
	void OnminusbtnClicked()
	{
		CString text1, text2, str;
		editBox1.GetWindowText(text1);
		editBox2.GetWindowText(text2);
		char* strAnsi1 = (char*)CT2A(text1);
		char* strAnsi2 = (char*)CT2A(text2);

		double value1 = _tstof(text1);
		double value2 = _tstof(text2);
		double result = value1 - value2;
		str.Format(_T("%f"), result);
		MessageBox(str.GetString(), _T("My Application"), MB_OK | MB_ICONINFORMATION);
	}
	void OnmultbtnClicked()
	{
		CString text1, text2, str;
		editBox1.GetWindowText(text1);
		editBox2.GetWindowText(text2);
		char* strAnsi1 = (char*)CT2A(text1);
		char* strAnsi2 = (char*)CT2A(text2);

		double value1 = _tstof(text1);
		double value2 = _tstof(text2);
		double result = value1 * value2;
		str.Format(_T("%f"), result);
		MessageBox(str.GetString(), _T("My Application"), MB_OK | MB_ICONINFORMATION);
	}
	void OndivbtnClicked()
	{
		CString text1, text2, str;
		editBox1.GetWindowText(text1);
		editBox2.GetWindowText(text2);
		char* strAnsi1 = (char*)CT2A(text1);
		char* strAnsi2 = (char*)CT2A(text2);

		double value1 = _tstof(text1);
		double value2 = _tstof(text2);
		if (value2 != 0) {
			double result = value1 / value2;
			str.Format(_T("%f"), result);
			MessageBox(str.GetString(), _T("My Application"), MB_OK | MB_ICONINFORMATION);
		}
		else {
			MessageBox("divide on zero is unable", _T("My Application"), MB_OK | MB_ICONINFORMATION);
		}
	}

	CButton addbtn,minusbtn,multbtn,divbtn;
	CStatic myStatic;
	CEdit editBox1;
	CEdit editBox2;

	DECLARE_MESSAGE_MAP();
};

BEGIN_MESSAGE_MAP(CMyWindow, CFrameWnd)
	ON_COMMAND(1, &CMyWindow::OnaddbtnClicked)
	ON_COMMAND(2, &CMyWindow::OnminusbtnClicked)
	ON_COMMAND(3, &CMyWindow::OnmultbtnClicked)
	ON_COMMAND(4, &CMyWindow::OndivbtnClicked)
END_MESSAGE_MAP()


class CMyApp : CWinApp
{
	virtual BOOL InitApplication()
	{
		this->m_pMainWnd = new CMyWindow();
		this->m_pMainWnd->ShowWindow(SW_SHOW);
		this->m_pMainWnd->UpdateWindow();

		return TRUE;
	}
};


CMyApp myApplication;


