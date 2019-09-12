#ifndef __DxInit_h__
#define __DxInit_h__

#include <iostream>

#include <d3d9.h>
#include<d3dx9.h>

#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

#include"ExternalDraw.h"
#include"ImguiInit.h"

#define BLOOD_UPTODOWN 1
#define BLOOD_DOWNTOUP 2

struct D3DTLVERTEX
{
	float x, y, z, rhw;
	DWORD color;
};

class CDxInit
{
private:
	static CDxInit* m_Instance;
	IDirect3D9Ex* m_pObject = 0;
	IDirect3DDevice9Ex* m_pDevice = 0;
	D3DPRESENT_PARAMETERS m_pParams;
	ID3DXFont* m_pFontSmall = 0;
	ID3DXLine* m_pLine = 0;

	std::string m_strFontName;
public:
	static CDxInit* Init();
	void hook(HWND hWnd, int Width, int Height,const char* fontPath);
	void Render(HWND hGameHwnd, void (*pDrawThread)(),void (*pImguiThread)());
	IDirect3D9Ex* getDirect3Object() const { return m_pObject; }
	IDirect3DDevice9Ex* getDirect3Device() const { return m_pDevice; }
	D3DPRESENT_PARAMETERS* getDirect3DParamenters()  {return &m_pParams;}

	void Box3D(int HeadX, int HeadY, int bottomX, int bottomY, D3DCOLOR Color);  //立体框
	void DrawLine(float x, float y, float x2, float y2, float width, D3DCOLOR color);   //画划线
	void DrawString(const char* fmt, int fontsize, int x, int y, D3DCOLOR color);  //写字
	void DrawFilledRectangle(float x, float y, float w, float h, D3DCOLOR color); //填充矩形
	void DrawBorderBox(int x, int y, int w, int h, int thickness, D3DCOLOR color);  //空心矩形
	void DrawCircle(float x, float y, float r, D3DCOLOR color);//画圆
	void DrawPoint(float x, float y, D3DCOLOR color); //画点
	void DrawBlood_Vertical(float Hp,float x, float y,int width,int height, D3DCOLOR color);//竖向血条
	void DrawBlood_Horizontal(float Hp,float x, float y, int width, int height, D3DCOLOR color,int style);//竖向血条 style=0从下往上减血  style=1 从上往下减血
protected:

};
#endif
