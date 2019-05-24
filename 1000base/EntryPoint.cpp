#include "Main.h"

#ifdef _DEBUG
void Initialize() {
	while (!(g_Globals->CSGOWindow = FindWindowA("Valve001", NULL)))
		Sleep(200);

	Hooks::oldWindowProc = (WNDPROC)SetWindowLongPtr(g_Globals->CSGOWindow, GWL_WNDPROC, (LONG_PTR)Hooks::WndProc);

	if (g_Interfaces->InitInterfaces())
		g_Utils->InitHooks();
	g_pNetvars = new CNetVarManager();
	g_pNetvars->Initialize();
}
#endif

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	VIRTUALIZER_EAGLE_BLACK_START
		if (dwReason == DLL_PROCESS_ATTACH) {
#ifdef _DEBUG
			CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)Initialize, hModule, NULL, nullptr);
#else
			g_Security->HideModuleFromPEB(hModule);
			g_Security->HideModuleXta(hModule);
			g_Security->RemovePeHeader((DWORD)hModule);
			g_Security->DestroyModuleHeader(hModule);
			g_Security->HideMod(hModule);
			DisableThreadLibraryCalls(hModule);

			std::unique_ptr<Initialize> InitClass;
			InitClass->Init();
#endif
		}
	return TRUE;
	VIRTUALIZER_EAGLE_BLACK_END
}