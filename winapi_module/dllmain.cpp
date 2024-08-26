
#include "pch.h"
#include <exception>


struct Mouse_wParam {
	int X;
	int Y;
	int wParam;

};
#ifdef __cplusplus
extern "C"
{
#endif
#define null NULL
#define DLL __declspec(dllexport)
	typedef int(__stdcall* _mouse_hook_pkm)(int key, int x, int y);



#ifdef __cplusplus
}
#endif
HHOOK _mosuehook_thread;
_mouse_hook_pkm _g_mouse_hook_pkm;
Mouse_wParam mousewParam{};
WPARAM _wParam{};
HWND win_hwnd;


void setWinPosition(HWND win, int x, int y, bool isShow) {
	SetWindowPos(win, HWND_TOPMOST, x, y, 0, 0, 0x0001 | 0x0004 /*| (isShow ? 0x0040 : 0x0080)*/);
}
RECT rect;
HWND FocusWindow{};
LRESULT CALLBACK _mouse_hook_proc(
	int nCode, WPARAM wParam, LPARAM lParam
)
{

	MOUSEHOOKSTRUCT* mhs = (MOUSEHOOKSTRUCT*)lParam;
	
	


	if (mhs != null && win_hwnd != null) {

		if (wParam == WM_LBUTTONDOWN) {
			FocusWindow = GetForegroundWindow();
			
			
			
			setWinPosition(win_hwnd, -mhs->pt.x, -mhs->pt.y, false);
			ShowWindow(win_hwnd, SW_HIDE);
		}
			
		if (wParam == WM_RBUTTONDOWN) {
			FocusWindow = GetActiveWindow();

			if (GetWindowRect(FocusWindow, &rect))
			{
				/*int width = rect.right - rect.left;
				int height = rect.bottom - rect.top;*/

				if (mhs->pt.y > rect.top  && mhs->pt.y  < rect.top + 30) {


					
					Sleep(100);
					setWinPosition(win_hwnd, mhs->pt.x - 105, mhs->pt.y , true);
					ShowWindow(win_hwnd, SW_SHOWNA);

				}

			}


			



		}
			
	}
	return CallNextHookEx(_mosuehook_thread, nCode, wParam, lParam);
}


DWORD WINAPI CreateHook() {
	_mosuehook_thread = SetWindowsHookEx(WH_MOUSE_LL, _mouse_hook_proc, GetModuleHandle(NULL), null);
	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(_mosuehook_thread);
	return 0;
}

extern "C" __declspec(dllexport) int InitHook(HWND win) {
	if (!win)
		return -1;
	DWORD dwThread;
	win_hwnd = win;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CreateHook, NULL, NULL, &dwThread);



	return (int)_mosuehook_thread;
}
extern "C" __declspec(dllexport) void SetHWNDWindow(HWND win) {
	win = win;
}

extern "C" __declspec(dllexport) int Test() {
	return 100;
}

#pragma region dllmain
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#pragma endregion



