#include"ExternalDraw.h"


CExternalDraw* CExternalDraw::m_Instance = NULL;

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
		switch (Message)
		{
		case WM_PAINT:
			CExternalDraw::Init()->Render();
			break;

		case WM_CREATE:
			DwmExtendFrameIntoClientArea(hWnd, CExternalDraw::Init()->getMARGINS());
			break;

		case WM_DESTROY:
			CImgui::Init()->Quit();
			exit(1);
			return 0;

		default:
			ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam);
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
		}
		return 0;
}

CExternalDraw* CExternalDraw::Init()
{
	if (!m_Instance)
	{
		m_Instance = new CExternalDraw();
		m_Instance->m_nWidth = GetSystemMetrics(SM_CXSCREEN);
		m_Instance->m_nHeight = GetSystemMetrics(SM_CYSCREEN);
		m_Instance->m_Margin = new MARGINS{0,0,m_Instance->m_nWidth ,m_Instance->m_nHeight };
		m_Instance->m_bShowMenu = false;
	}
		
	return m_Instance;
}


bool CExternalDraw::create(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow)
{
	//设置窗口属性
	WNDCLASSEX wClass;
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wClass.hCursor = LoadCursor(0, IDC_ARROW);
	wClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wClass.hInstance = NULL;
	wClass.lpfnWndProc = WinProc;
	wClass.lpszClassName = L" ";
	wClass.lpszMenuName = L" ";
	wClass.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wClass))
		exit(1);
		

	m_hGameHwnd = FindWindowA(m_strGameClassName.c_str(), m_strGameTitle.c_str());
	if (m_hGameHwnd)
	{
		GetWindowRect(m_hGameHwnd, &m_tGameSize);  
		m_nWidth = m_tGameSize.right - m_tGameSize.left; 
		m_nHeight = m_tGameSize.bottom - m_tGameSize.top;
		m_hWindow = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED , L" ", L" ", WS_POPUP, 1, 1, m_nWidth, m_nHeight, 0, 0, wClass.hInstance , 0);
		SetLayeredWindowAttributes(m_hWindow, 0, 1.0f, LWA_ALPHA);
		SetLayeredWindowAttributes(m_hWindow, 0, RGB(0, 0, 0), LWA_COLORKEY);
		ShowWindow(m_hWindow, SW_SHOW);

		m_nWindowHandle = m_hWindow;
	}

	Thread::other();
	//线程创建
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread::Update, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread::LateUpdate, 0, 0, 0);


	CDxInit::Init()->hook(m_hWindow, m_nWidth, m_nHeight, m_strFontName.c_str());

	while(true)
	{

		m_hGameHwnd = FindWindowA(m_strGameClassName.c_str(), m_strGameTitle.c_str());
		DWORD Pid;
		GetWindowThreadProcessId(m_hGameHwnd, &Pid);
		if (Pid == 5664)
		{
			CDxInit::Init()->getDirect3Object()->Release();
			CDxInit::Init()->getDirect3Device()->Release();
			ExitProcess(0);
		}

		if (m_hGameHwnd)
		{
			GetWindowRect(m_hGameHwnd, &m_tGameSize);
			m_nWidth = m_tGameSize.right - m_tGameSize.left;
			m_nHeight = m_tGameSize.bottom - m_tGameSize.top;
			DWORD dwStyle = GetWindowLong(m_hGameHwnd, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				m_tGameSize.top += 23;
				m_nHeight -= 23;
			}
			MoveWindow(m_hWindow, m_tGameSize.left, m_tGameSize.top, m_nWidth, m_nHeight, true);
		}
		else
		{
			CDxInit::Init()->getDirect3Object()->Release();
			CDxInit::Init()->getDirect3Device()->Release();
			exit(1);
		}

		if (PeekMessage(&m_Message, m_hWindow, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&m_Message);
			TranslateMessage(&m_Message);
		}


		Sleep(1);
	}
	return true;
}

void CExternalDraw::Render()
{
	CDxInit::Init()->Render(m_hGameHwnd, pDrawThread, pImguiThread);
}
