#pragma once
#include "IniReader.h"
#include "IniWriter.h"

class CMenu {
public:
	void Menu();

	void ReadCFG();

	void lAimbot();
	void DoTab();
	void lTriggerbot();
	void Visuals();
	void Colors();
	void Skins();
	void Misc();
	void initializeskins();
	void DrawRader();
	void DrawSL();
private:
	int VisualsSubTab;
	int LegitSubTab;
	int LegitSubTabMain;
	ImVec2 WindowSize;
}; extern CMenu* g_Menu;