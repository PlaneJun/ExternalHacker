#include "DxInit.h"

CDxInit* CDxInit::m_Instance = NULL;


CDxInit* CDxInit::Init()
{
	if (!m_Instance)
		m_Instance = new CDxInit();
	return m_Instance;
}

void CDxInit::hook(HWND hWnd,int Width,int Height, const char* fontPath)
{
	m_strFontName = fontPath;
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &m_pObject)))
		exit(1);

	ZeroMemory(&m_pParams, sizeof(m_pParams));
	m_pParams.Windowed = TRUE;
	m_pParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_pParams.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_pParams.BackBufferWidth = Width;
	m_pParams.BackBufferHeight = Height;
	m_pParams.EnableAutoDepthStencil = TRUE;
	m_pParams.AutoDepthStencilFormat = D3DFMT_D16;
	m_pParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(m_pObject->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_pParams, 0, &m_pDevice)))
		exit(1);

	if (!m_pLine)
		D3DXCreateLine(m_pDevice, &m_pLine);

	CImgui::Init()->installImGui(hWnd, m_pDevice);

}

void CDxInit::Render(HWND hGameHwnd, void (*pDrawThread)(), void (*pImguiThread)())
{
	if (m_pDevice == nullptr) return;

	m_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	m_pDevice->BeginScene();  //D3D绘制开始
	if (hGameHwnd == GetForegroundWindow() || GetActiveWindow() == GetForegroundWindow())
	{

		if(pDrawThread ) pDrawThread();
		if (CExternalDraw::Init()->m_bShowMenu)
		{
			CImgui::Init()->BeginImgui();
			if (pImguiThread) pImguiThread(); 
			CImgui::Init()->EndImgui();
		}
		
	}

	if (m_pFontSmall)
		m_pFontSmall->Release();
	m_pFontSmall = nullptr;

	m_pDevice->EndScene();//D3D绘制结束
	m_pDevice->PresentEx(0, 0, 0, 0, 0);
}




void CDxInit::Box3D(int HeadX, int HeadY, int bottomX, int bottomY, D3DCOLOR Color)
{
	//立体原型
	/*float DrawBox1 = 480 / Player_Distance;
	float DrawBox2 = 260 / Player_Distance;
	float DrawBox3 = 100 / Player_Distance;

	DrawLine （pDevice ，bottomX - DrawBox1 ，bottomY ，bottomX + DrawBox1 ，bottomY ，Color ）;
	DrawLine （pDevice ，HeadX - DrawBox1 ，HeadY ，HeadX + DrawBox1 ，HeadY ，Color ）;
	DrawLine （pDevice ，HeadX - DrawBox1 ，HeadY ，bottomX - DrawBox1 ，bottomY ，Color ）;
	DrawLine （pDevice ，HeadX + DrawBox1 ，HeadY ，bottomX + DrawBox1 ，bottomY ，Color ）;
	DrawLine （pDevice ，HeadX - DrawBox2 ，HeadY - DrawBox3 ，bottomX - DrawBox2 ，bottomY - DrawBox3 ，Color ）;
	DrawLine （pDevice ，bottomX - DrawBox1 ，bottomY ，bottomX - DrawBox2 ，bottomY - DrawBox3 ，Color ）;
	DrawLine （pDevice ，HeadX - DrawBox1 ，HeadY ，HeadX - DrawBox2 ，HeadY - DrawBox3 ，Color ）;
	DrawLine （pDevice ，（HeadX + DrawBox1 ） + DrawBox2 ，HeadY - DrawBox3 ，（bottomX + DrawBox1 ） + DrawBox2 ，bottomY - DrawBox3 ，Color ）;
	DrawLine （pDevice ，bottomX + DrawBox1 ，bottomY ，（bottomX + DrawBox1 ） + DrawBox2 ，bottomY - DrawBox3 ，Color ）;
	DrawLine （pDevice ，HeadX + DrawBox1 ，HeadY ，（HeadX + DrawBox1 ） + DrawBox2 ，HeadY - DrawBox3 ，Color ）;
	DrawLine （pDevice ，HeadX - DrawBox2 ，HeadY - DrawBox3 ，（HeadX + DrawBox1 ） + DrawBox2 ，HeadY - DrawBox3 ，Color ）;
	DrawLine （pDevice ，bottomX - DrawBox2 ，bottomY - DrawBox3 ，（bottomX + DrawBox1 ） + DrawBox2 ，bottomY - DrawBox3 ，Color ）;
*/

	DrawLine(bottomX - 5, bottomY, bottomX + 5, bottomY, 1.5, Color);
	DrawLine(HeadX - 5, HeadY, HeadX + 5, HeadY, 1.5, Color);
	DrawLine(HeadX - 5, HeadY, bottomX - 5, bottomY, 1.5, Color);
	DrawLine(HeadX + 5, HeadY, bottomX + 5, bottomY, 1.5, Color);
	DrawLine(HeadX - 7, HeadY - 10, bottomX - 7, bottomY - 10, 1.5, Color);
	DrawLine(bottomX - 5, bottomY, bottomX - 7, bottomY - 10, 1.5, Color);
	DrawLine(HeadX - 5, HeadY, HeadX - 7, HeadY - 10, 1.5, Color);
	DrawLine((HeadX + 5) + 7, HeadY - 10, (bottomX + 5) + 7, bottomY - 10, 1.5, Color);
	DrawLine(bottomX + 5, bottomY, (bottomX + 5) + 7, bottomY - 10, 1.5, Color);
	DrawLine(HeadX + 5, HeadY, (HeadX + 5) + 7, HeadY - 10, 1.5, Color);
	DrawLine(HeadX - 7, HeadY - 10, (HeadX + 5) + 7, HeadY - 10, 1.5, Color);
	DrawLine(bottomX - 7, bottomY - 10, (bottomX + 5) + 7, bottomY - 10, 1.5, Color);
}

void CDxInit::DrawLine(float x, float y, float x2, float y2, float width, D3DCOLOR color)
{

	//D3DTLVERTEX qV[2] =
	//{
	//	{ (float)x, (float)y, 0.0f, 1.0f, color },
	//{ (float)x2, (float)y2, 0.0f, 1.0f, color },
	//};

	//m_pDevice->SetTexture(0, NULL);
	//m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
	//m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//m_pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	//m_pDevice->SetRenderState(D3DRS_FOGENABLE, false);
	//m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	//m_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, qV, sizeof(D3DTLVERTEX));
	D3DXVECTOR2 dLine[2];

	m_pLine->SetWidth(width);

	dLine[0].x = x;
	dLine[0].y = y;

	dLine[1].x = x2;
	dLine[1].y = y2;

	m_pLine->Draw(dLine, 2, color);
}

void CDxInit::DrawString(const char* fmt, int fontsize, int x, int y, D3DCOLOR color)
{
	//string 转 LPCWSTR
	size_t size = m_strFontName.length();
	wchar_t fontName[100];
	MultiByteToWideChar(CP_ACP,0, m_strFontName.c_str(), size, fontName, size*sizeof(wchar_t));
	D3DXCreateFont(m_pDevice, fontsize, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fontName, &m_pFontSmall);
	RECT FontPos;
	FontPos.left = x;
	FontPos.top = y;

	CHAR buf[124] = { '\0' };
	va_list va_alist;
	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);

	m_pFontSmall->DrawTextA(0, buf, -1, &FontPos, DT_NOCLIP, color);

}

void CDxInit::DrawFilledRectangle(float x, float y, float w, float h, D3DCOLOR color)
{
	D3DRECT rect = { x, y, w, h };
	m_pDevice->Clear(1, &rect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
}


void CDxInit::DrawBorderBox(int x, int y, int w, int h, int thickness, D3DCOLOR color)
{
	DrawFilledRectangle(x, y, w, y + thickness, color); // x
	DrawFilledRectangle(x, y, x + thickness, h, color); // y
	DrawFilledRectangle(x, h, w, h + thickness, color); // w
	DrawFilledRectangle(w, y, w + thickness, h + thickness, color); // h
}

void CDxInit::DrawCircle(float x, float y, float r, D3DCOLOR color)
{
	if (m_pLine)
	{
		float d = 1.25f - r;
		float tx = 0, ty = r, fx = r / 1.4f;
		while ((int)tx != (int)fx)
		{

			if (d < 0)
				d += 2 * tx + 3;
			else
			{
				d += 2 * (tx - ty) + 5;
				--ty;
			}

			//八分画法
			DrawPoint(x + tx, y + ty, color);
			DrawPoint(x + tx, y - ty, color);
			DrawPoint(x - tx, y + ty, color);
			DrawPoint(x - tx, y - ty, color);
			DrawPoint(x + ty, y - tx, color);
			DrawPoint(x + ty, y + tx, color);
			DrawPoint(x - ty, y + tx, color);
			DrawPoint(x - ty, y - tx, color);
			++tx;
		}
	}
}

void CDxInit::DrawPoint(float x, float y, D3DCOLOR color)
{
	DrawLine(x,y,x+2,y+2,1, color);
}

void CDxInit::DrawBlood_Vertical(float Hp, float x, float y, int width, int height, D3DCOLOR color)
{
	if (Hp < 0.0f) return;
	float temp1 = width / 100 * Hp;
	DrawLine(x, y , x+temp1, y , height, color);//从上往下减血
}

void CDxInit::DrawBlood_Horizontal(float Hp, float x, float y, int width, int height, D3DCOLOR color, int style)
{
	if (Hp < 0.0f) return;
	float temp1 = height / 100 * Hp;
	float temp2 = (height / 100 * 100) - temp1;
	if(style == BLOOD_UPTODOWN)
		DrawLine(x, y + height, x, y + temp2, width, color);//从上往下减血
	else if(style == BLOOD_DOWNTOUP)
		DrawLine(x, y, x, y + temp1, width, color);//从下往上减血
	
}
