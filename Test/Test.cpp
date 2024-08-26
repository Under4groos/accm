// Test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
using namespace std;
HHOOK thread_;


LRESULT CALLBACK _hook(
	int nCode, WPARAM wParam, LPARAM lParam
)
{

	cout << thread_  << nCode << wParam << lParam << endl;
	return CallNextHookEx(thread_, nCode, wParam, lParam);
}


DWORD WINAPI CreateHook() {
	thread_ = SetWindowsHookEx(WH_KEYBOARD_LL, _hook, GetModuleHandle(NULL), NULL);
	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		cout << message.message << endl;
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(thread_);
	return 0;
}

int main()
{
	 
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CreateHook, NULL, NULL, NULL);
	MSG message;


	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		cout << message.message << endl;
		DispatchMessage(&message);
	}
}




 