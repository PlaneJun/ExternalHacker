#ifndef __ImguiInit_H__
#define __ImguiInit_H__

#include "imgui.h"
#include "imgui_impl_dx9.h"

#include <thread>
#include <chrono>
#include<Windows.h>
#include <d3d9.h>
#include<d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


#define IMGUI_DEFAULTWIDTH 400
#define IMGUI_DEFAULTHEIGHT 300
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
class CImgui
{
private:
	friend class CDxInit;
	static CImgui* m_Instance;

	int m_nWidth;
	int m_nHeight;
	int m_nStyle;

	void installImGui(HWND hwnd, IDirect3DDevice9Ex* pDevice);
	void BeginImgui();
	void EndImgui();
public:
	static CImgui* Init();
	bool Start(const char* title,int width,int height,int style,int flage);
	void End();
	void Quit();
protected:

};


#endif
