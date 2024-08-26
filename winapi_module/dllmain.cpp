
#include "pch.h"



#ifdef __cplusplus
extern "C"
{
#endif
#define null NULL
#define DLL __declspec(dllexport)
	typedef int(__stdcall* _moue_hook)();
	DLL void _cell_function(_moue_hook);


#ifdef __cplusplus
}
#endif
HHOOK _mosuehook_thread;
_moue_hook _g__moue_hook;
LRESULT CALLBACK _mouse_hook_proc(
	int nCode,
	WPARAM wParam,
	LPARAM lParam
)
{
	if (_g__moue_hook)
		_g__moue_hook();
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
extern "C" __declspec(dllexport) int InitHook(_moue_hook func) {
	if (func)
		return -1;

	_g__moue_hook = func;
	_mosuehook_thread = SetWindowsHookEx(WH_MOUSE_LL, _mouse_hook_proc, null, null);
	
	return (int)_mosuehook_thread;
}


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

