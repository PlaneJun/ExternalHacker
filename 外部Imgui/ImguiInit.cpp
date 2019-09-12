#include "ImguiInit.h"

CImgui* CImgui::m_Instance = NULL;


CImgui* CImgui::Init()
{
	if (!m_Instance)
	{
		m_Instance = new CImgui();
	}
		
	return m_Instance;
}

bool CImgui::Start(const char* title , int width , int height , int style,  int flage)
{
	ImGui::Begin(title,false, flage);
	m_nWidth = width;
	m_nHeight = height;
	m_nStyle = style;
	return true;
}

void CImgui::End()
{
	ImGui::End();
}

void CImgui::Quit()
{
	ImGui::DestroyContext(ImGui::GetCurrentContext());
	ImGui::Shutdown();
}


void CImgui::installImGui(HWND hwnd, IDirect3DDevice9Ex* pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = 1.0f / 60.0f;
	io.Fonts->AddFontFromFileTTF("c:/windows/fonts/simhei.ttf", 13.0f, NULL, io.Fonts->GetGlyphRangesChinese());
	ImGui_ImplDX9_Init(hwnd, pDevice);
}

void CImgui::BeginImgui()
{
	if (m_nStyle == 0)
		ImGui::StyleColorsDark();
	else if (m_nStyle == 1)
		ImGui::StyleColorsLight();
	else if (m_nStyle == 2)
	{
		//ImVec4* colors = ImGui::GetStyle().Colors;
		//colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		//colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		//colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
		//colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
		//colors[ImGuiCol_CheckMark] = ImVec4(0.62f, 0.93f, 0.06f, 1.00f);
		ImGui::StyleColorsClassic();
	}
	
	
	ImGui_ImplDX9_NewFrame();
	ImGui::SetNextWindowSize(ImVec2(m_nWidth, m_nHeight), ImGuiCond_FirstUseEver);
}

void CImgui::EndImgui()
{
	ImGui::Render();
}
