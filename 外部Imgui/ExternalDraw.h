#ifndef __ExternalDraw_H__
#define __ExternalDraw_H__

#include<string>
#include<windows.h>
#include"DxInit.h"
#include"Thread.h"

//回调函数
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

class CExternalDraw
{
private:
	static CExternalDraw* m_Instance;

	int m_nWidth;
	int m_nHeight;

	HWND m_hWindow;
	HWND m_hGameHwnd;
	RECT m_tGameSize;
	MSG m_Message;
	MARGINS* m_Margin;
	

public:
	static CExternalDraw* Init();

	HWND m_nWindowHandle;
	bool m_bShowMenu;
	DWORD m_dwKey_ShowHide;
	std::string m_strGameTitle;
	std::string m_strGameClassName;
	std::string m_strFontName;

	void (*pImguiThread)();
	void (*pDrawThread)();
	bool create(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow); //创建窗口
	void Render();
	MARGINS* getMARGINS() const { return m_Margin; }
protected:
};


#endif