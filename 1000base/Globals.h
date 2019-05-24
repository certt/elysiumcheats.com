#pragma once

class Globals
{
public:
	HWND CSGOWindow;
	bool SendPacket;
	bool RenderInit;
	ImFont* ESP_MAIN;
	ImFont* MENU_FONT;
	ImFont* MENU_FONT_TABS;
	ImFont* MENU_FONT_SUBTABS;
	ImFont* WEAP_ICON;
	float HitMarker;
	C_BaseEntity* LocalPlayer;
	DWORD GlowManager;

	bool DoCustomAnimUpdt;
	float FOV;
	int KillDelay;
	int AimDelay;

	struct cPlayer
	{
		Vector vHitboxSkeletonArray[18][2];
		float ghay;
	};
	cPlayer cPlayer[64];
private:
}; extern Globals* g_Globals;

struct playerMatrix {
	matrix3x4_t matrix[128];
	bool isvisible;
}; extern playerMatrix playerStruct[64];