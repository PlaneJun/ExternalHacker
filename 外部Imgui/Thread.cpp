#include"Thread.h"


namespace Thread {
	void LateUpdate() {
		while (true) {

			//Only execute when window is in focus
			if (CExternalDraw::Init()->m_nWindowHandle == GetForegroundWindow()) {}

			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
	}



	void Update() {
		while (true) {

			//Only execute when window is in focus
			if (CExternalDraw::Init()->m_nWindowHandle == GetForegroundWindow()) {}

			//Toggle Menu
			if (GetAsyncKeyState(CExternalDraw::Init()->m_dwKey_HowHide)) {
				other();
				while (GetAsyncKeyState(CExternalDraw::Init()->m_dwKey_HowHide)) {}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(32));
		}
	}

	void other()
	{
		if (!CExternalDraw::Init()->m_bShowMenu) {
			long winlong = GetWindowLong(CExternalDraw::Init()->m_nWindowHandle, GWL_EXSTYLE);

			if (winlong != WS_EX_LAYERED | WS_EX_TOPMOST)
				SetWindowLong(CExternalDraw::Init()->m_nWindowHandle, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST);
		}

		if (CExternalDraw::Init()->m_bShowMenu) {
			long winlong = GetWindowLong(CExternalDraw::Init()->m_nWindowHandle, GWL_EXSTYLE);

			if (winlong != WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT)
				SetWindowLong(CExternalDraw::Init()->m_nWindowHandle, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT);
		}
		CExternalDraw::Init()->m_bShowMenu = !CExternalDraw::Init()->m_bShowMenu;

	}
}