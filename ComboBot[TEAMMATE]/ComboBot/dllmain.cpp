// dllmain.cpp : Definiuje punkt wejścia dla aplikacji DLL.
#include "pch.h"
#include "Menu.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
	Menu::Init(hModule);
	Menu::HandleMsgs();


	FreeLibraryAndExitThread(hModule, 0);


	return 0;
}

//DWORD WINAPI SocketThread(HMODULE hModule)
//{
//	
//
//
//
//
//
//	
//
//
//
//
//
//
//
//	FreeLibraryAndExitThread(hModule, 0);
//	return 0;
//}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls(hModule);
		HANDLE hObject = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, NULL);
		//HANDLE hSocket = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SocketThread, hModule, 0, NULL);
		//if (hObject) {
		//	CloseHandle(hObject);
		//}
		//if (hSocket) {
		//	CloseHandle(hSocket);
		//}
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}