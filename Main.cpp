#include "afxwin.h"
#include <fstream>

class CMyWindow : public CFrameWnd {

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
		myButton.Create("Okay", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, buttonRect, this, 1);


		RECT staticRect;
		staticRect.left = 200;
		staticRect.right = 400;
		staticRect.top = 300;
		staticRect.bottom = 500;
		imageStatic.Create("", WS_CHILD | WS_VISIBLE | SS_BITMAP, staticRect, this, 2);
		RECT staticRect2;
		staticRect.left = 500;
		staticRect.right = 700;
		staticRect.top = 300;
		staticRect.bottom = 500;
		imageStatic2.Create("", WS_CHILD | WS_VISIBLE | SS_BITMAP, staticRect, this, 3);

		LoadFile();

	}
protected:

	void OnButtonClicked()
	{
	}

	void LoadFile()
	{
		std::ifstream f;
		std::ifstream s;

		f.open("C:/с++/first.bmp", std::ios::binary);
		s.open("C:/с++/second.bmp", std::ios::binary);
		
		f.seekg(0, std::ios::end);
		int fileSize1 = f.tellg();
		f.seekg(0, std::ios::beg);

		s.seekg(0, std::ios::end);
		int fileSize2 = s.tellg();
		s.seekg(0, std::ios::beg);

		unsigned char* bytes = new unsigned char[fileSize1];

		unsigned char* bytes2 = new unsigned char[fileSize2];

		f.read((char*)bytes, fileSize1);
		s.read((char*)bytes2, fileSize2);

		unsigned int width = bytes[18];

		width = width + bytes[19] * 0x100;
		width = width + bytes[20] * 0x10000;
		width = width + bytes[21] * 0x1000000;

		unsigned int height = bytes[22];

		height = height + bytes[23] * 0x100;
		height = height + bytes[24] * 0x10000;
		height = height + bytes[25] * 0x1000000;

		unsigned char* pointerToImageData = bytes + 138;
		unsigned char* pointerToImageData2 = bytes2 + 138;

		BITMAPINFO info;
		BITMAPINFO info2;

		info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		info.bmiHeader.biWidth = width;
		info.bmiHeader.biHeight = height;
		info.bmiHeader.biPlanes = 1;
		info.bmiHeader.biBitCount = 24;
		info.bmiHeader.biCompression = 0;
		info.bmiHeader.biSizeImage = 0;
		info.bmiHeader.biXPelsPerMeter = 0;
		info.bmiHeader.biYPelsPerMeter = 0;
		info.bmiHeader.biClrUsed = 0;
		info.bmiHeader.biClrImportant = 0;
		info.bmiColors[0].rgbBlue = 0;
		info.bmiColors[0].rgbGreen = 0;
		info.bmiColors[0].rgbRed = 0;
		info.bmiColors[0].rgbReserved = 0;


		info2.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		info2.bmiHeader.biWidth = width;
		info2.bmiHeader.biHeight = height;
		info2.bmiHeader.biPlanes = 1;
		info2.bmiHeader.biBitCount = 24;
		info2.bmiHeader.biCompression = 0;
		info2.bmiHeader.biSizeImage = 0;
		info2.bmiHeader.biXPelsPerMeter = 0;
		info2.bmiHeader.biYPelsPerMeter = 0;
		info2.bmiHeader.biClrUsed = 0;
		info2.bmiHeader.biClrImportant = 0;
		info2.bmiColors[0].rgbBlue = 0;
		info2.bmiColors[0].rgbGreen = 0;
		info2.bmiColors[0].rgbRed = 0;
		info2.bmiColors[0].rgbReserved = 0;

		//DrawContext = DC
		HDC hdc = this->GetDC()->m_hDC;
		HDC hdc2 = this->GetDC()->m_hDC;
		
		double alpha = 0.5;

		for (int i =0 ; i < height * width *3; i++)
		{
			pointerToImageData[i] = static_cast<unsigned char>(alpha * pointerToImageData[i] + (1 - alpha) * pointerToImageData2[i]);
			pointerToImageData2[i] = static_cast<unsigned char>(alpha * pointerToImageData2[i] + (1 - alpha) * pointerToImageData[i]);

		}
	

		HBITMAP bitmap = CreateDIBitmap(hdc, &info.bmiHeader, CBM_INIT, pointerToImageData, &info, 0);
		HBITMAP bitmap2 = CreateDIBitmap(hdc2, &info2.bmiHeader, CBM_INIT, pointerToImageData2, &info2, 0);

		imageStatic.SetBitmap(bitmap);
		imageStatic2.SetBitmap(bitmap2);
	//	imageStatic.SetBitmap(blendedBitmap);
		f.close();
		s.close();
		
		delete[] bytes;


	}

	CButton myButton;
	CStatic imageStatic, imageStatic2;

	DECLARE_MESSAGE_MAP();
};

BEGIN_MESSAGE_MAP(CMyWindow, CFrameWnd)
	ON_COMMAND(1, &CMyWindow::OnButtonClicked)
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


