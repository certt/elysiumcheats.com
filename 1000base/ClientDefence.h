#pragma once

class cSecurity {
public:
	void HideModuleFromPEB(HINSTANCE hInstance);
	void RemovePeHeader(DWORD ModuleBase);
	void HideModule(HANDLE hModule);
	void HideModuleXta(HINSTANCE hModule);
	bool DestroyModuleHeader(HMODULE hModule);
	DWORD HideMod(HMODULE mod);
	class Glob {
	public:
		bool License();
		void Ban();
		bool IsBanned();
	};
}; extern cSecurity* g_Security;