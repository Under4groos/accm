
#include "pch.h"



#ifdef __cplusplus
extern "C"
{
#endif
#define null NULL
#define DLL __declspec(dllexport)
	typedef int(__stdcall* _mouse_hook)(int key);
	DLL void _cell_function(_mouse_hook);


#ifdef __cplusplus
}
#endif
HHOOK _mosuehook_thread;
_mouse_hook _g_mouse_hook;
WPARAM _wParam{};
LRESULT CALLBACK _mouse_hook_proc(
	int nCode, WPARAM wParam, LPARAM lParam
)
{
	MOUSEHOOKSTRUCT* mhs = (MOUSEHOOKSTRUCT*)lParam;
	if (mhs != null) {
		_wParam = wParam;
	}

	return CallNextHookEx(_mosuehook_thread, nCode, wParam, lParam);
}
DWORD WINAPI MouseTick(void* p)
{
	while (true)
	{

		if (_g_mouse_hook && _wParam != null)
			_g_mouse_hook((int)_wParam);

		_wParam = 0;

		Sleep(1);
	}



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

extern "C" __declspec(dllexport) int InitHook(_mouse_hook func) {
	if (!func)
		return -1;
	DWORD dwThread;
	CreateThread(0, 0, MouseTick, NULL, 0, NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CreateHook, NULL, NULL, &dwThread);
	_g_mouse_hook = func;
	

	return (int)_mosuehook_thread;
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



