#include"ExternalDraw.h"
float hp = 100;
void RnederDraw()
{
	CDxInit::Init()->DrawBlood_Vertical(hp,100,100,100,3, D3DCOLOR_RGBA(255, 0, 0, 255));
}
void RenderImgui()
{
	if (CImgui::Init()->Start("WindowTest", IMGUI_DEFAULTWIDTH, IMGUI_DEFAULTHEIGHT, 1, 0))
	{
		ImGui::Text(u8"你麻痹的");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		if (ImGui::Button(u8"减血"))
		{
			hp -= 5;
		}
		CImgui::Init()->End();
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow)
{
	CExternalDraw::Init()->m_dwKey_ShowHide = 0x2D;
	CExternalDraw::Init()->m_strFontName = "黑体";  //Dx显示字体 imgui默认simkai.ttf(其他字体不一定能显示中文) //必须
	CExternalDraw::Init()->m_strGameClassName = "MainWindow";  //必须
	CExternalDraw::Init()->m_strGameTitle = "植物大战僵尸中文版";  //必须
	CExternalDraw::Init()->pImguiThread = RenderImgui;   //必须
	CExternalDraw::Init()->pDrawThread = RnederDraw;   //必须
	CExternalDraw::Init()->create(hInstance, hSecInstance, nCmdLine, nCmdShow); //必须
	return 0;
}


