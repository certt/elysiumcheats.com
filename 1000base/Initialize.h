#pragma once

class Initialize
{
private:
	void DoInit()
	{
		VIRTUALIZER_EAGLE_BLACK_START
		std::unique_ptr<cSecurity::Glob> Global;
		bool IsBanned = Global->IsBanned();
		bool HaveLicense = Global->License();

		if (IsBanned)
			exit(GetTickCount());

		if (!HaveLicense)
		{
			Global->Ban();
			exit(GetTickCount());
		}

		Global.release(); Global.reset(nullptr);

		if (!IsBanned && HaveLicense)
		{
			if (g_Interfaces->InitInterfaces())
				g_Utils->InitHooks();
			g_pNetvars = new CNetVarManager();
			g_pNetvars->Initialize();
		}
		VIRTUALIZER_EAGLE_BLACK_END
	}
public:
	void Init()
	{	
		VIRTUALIZER_EAGLE_BLACK_START
		while (!(g_Globals->CSGOWindow = FindWindowA("Valve001", NULL)))
			Sleep(200);

		Hooks::oldWindowProc = (WNDPROC)SetWindowLongPtr(g_Globals->CSGOWindow, GWL_WNDPROC, (LONG_PTR)Hooks::WndProc);
		DoInit(); // Call license check, etc.
		VIRTUALIZER_EAGLE_BLACK_END
	}
};