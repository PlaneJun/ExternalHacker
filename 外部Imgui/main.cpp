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
		ImGui::Text(u8"����Ե�");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		if (ImGui::Button(u8"��Ѫ"))
		{
			hp -= 5;
		}
		CImgui::Init()->End();
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow)
{
	CExternalDraw::Init()->m_dwKey_ShowHide = 0x2D;
	CExternalDraw::Init()->m_strFontName = "����";  //Dx��ʾ���� imguiĬ��simkai.ttf(�������岻һ������ʾ����) //����
	CExternalDraw::Init()->m_strGameClassName = "MainWindow";  //����
	CExternalDraw::Init()->m_strGameTitle = "ֲ���ս��ʬ���İ�";  //����
	CExternalDraw::Init()->pImguiThread = RenderImgui;   //����
	CExternalDraw::Init()->pDrawThread = RnederDraw;   //����
	CExternalDraw::Init()->create(hInstance, hSecInstance, nCmdLine, nCmdShow); //����
	return 0;
}


