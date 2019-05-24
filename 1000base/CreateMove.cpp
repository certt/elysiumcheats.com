#include "Main.h"

void RankRevealAll()
{
	using ServerRankRevealAll = char(__cdecl*)(int*);
	static auto fnServerRankRevealAll = g_Utils->FindPatternIDA("client_panorama.dll", "55 8B EC 8B 0D ? ? ? ? 85 C9 75 28 A1 ? ? ? ? 68 ? ? ? ? 8B 08 8B 01 FF 50 04 85 C0 74 0B 8B C8 E8 ? ? ? ? 8B C8 EB 02 33 C9 89 0D ? ? ? ? 8B 45 08");
	int v[3] = { 0,0,0 };
	reinterpret_cast<ServerRankRevealAll>(fnServerRankRevealAll)(v);
}

void LegitStrafe(CUserCmd* pCmd)
{
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	if (!LocalPlayer)
		return;

	if (!g_Vars->Misc.AutoStrafe)
		return;

	if (!(LocalPlayer->GetFlags() & FL_ONGROUND))
	{
		pCmd->forwardmove = 0.0f;

		if (pCmd->mousedx < 0)
		{
			pCmd->sidemove = -g_Vars->Misc.StrafeFirst;
		}
		else if (pCmd->mousedx > 0)
		{
			pCmd->sidemove = g_Vars->Misc.StrafeSecond;
		}
	}
}

void RunBhop(CUserCmd* cmd)
{
	if (!g_Vars->Misc.Bhop)
		return;

	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());

	if (!LocalPlayer)
		return;

	if (cmd->buttons & IN_JUMP && !(LocalPlayer->GetFlags() & FL_ONGROUND) && !(LocalPlayer->GetFlags() & FL_ONTRAIN))
		cmd->buttons &= ~IN_JUMP;
}

void Marquee(std::string& clantag)
{
	std::string temp = clantag;
	clantag.erase(0, 1);
	clantag += temp[0];
}

void MarqueeTag()
{
	static std::string cur_clantag = " ElysiumProject ";
	static float oldTime;

	if (I::Engine->IsInGame())
	{
		if (I::Globals->curtime - oldTime >= 0.5f)
		{
			Marquee(cur_clantag);
			g_Utils->SetClantag(cur_clantag.c_str());
			oldTime = I::Globals->curtime;
		}
	}
}

void LegitAA(C_BaseEntity* local, C_BaseCombatWeapon* weapon, CUserCmd* pCmd, bool& bSendPacket)
{
	if (g_Vars->Misc.LegitAA)
	{
		if (GetAsyncKeyState(VK_LEFT)) g_Vars->Misc.Direction = true;
		if (GetAsyncKeyState(VK_RIGHT)) g_Vars->Misc.Direction = false;
		if (!local) return;
		if (pCmd->buttons & IN_ATTACK || pCmd->buttons & IN_USE || local->GetMoveType() & 9) return;
		if (weapon->IsGrenade()) return;
		{
			static int ChokedPackets = -1;
			ChokedPackets++;
			if (ChokedPackets < 1)
			{
				bSendPacket = true;
			}
			else
			{
				bSendPacket = false;
				pCmd->viewangles.y -= g_Vars->Misc.Direction ? 90 : -90;
				ChokedPackets = -1;
			}
		}
	}

}

inline float sseSqrt(float x)
{
	float root = 0.0f;

	__asm
	{
		sqrtss xmm0, x
		movss root, xmm0
	}

	return root;
}
#define square( x ) ( x * x )
void vectorAnglesVec(Vector forward, Vector& angles)
{
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f;
		angles[1] = 0.0f;
	}
	else
	{
		float len2d = sseSqrt(square(forward[0]) + square(forward[1]));

		angles[0] = RAD2DEG(atan2f(-forward[2], len2d));
		angles[1] = RAD2DEG(atan2f(forward[1], forward[0]));

		if (angles[0] < 0.0f)
			angles[0] += 360.0f;
		if (angles[1] < 0.0f)
			angles[1] += 360.0f;
	}
}

static Vector Normalizekek(Vector& angs)
{
	while (angs.y < -180.0f)
		angs.y += 360.0f;
	while (angs.y > 180.0f)
		angs.y -= 360.0f;
	if (angs.x > 89.0f)
		angs.x = 89.0f;
	if (angs.x < -89.0f)
		angs.x = -89.0f;
	angs.z = 0;
	return angs;
}

inline void movementfix(QAngle realvec, CUserCmd* cmd)
{
	Vector vMove(cmd->forwardmove, cmd->sidemove, cmd->upmove);
	float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
	Vector vMove2;
	vectorAnglesVec(vMove, vMove2);
	Normalizekek(vMove2);
	flYaw = DEG2RAD(cmd->viewangles.y - realvec.y + vMove2.y);
	cmd->forwardmove = cos(flYaw) * flSpeed;
	cmd->sidemove = sin(flYaw) * flSpeed;
	if (90 < abs(cmd->viewangles.x) && 180 > abs(cmd->viewangles.x))
		cmd->forwardmove *= -1;
}

void MarqueeTag2()
{
	static std::string cur_clantag_gf = "";
	if (g_Globals->DoCustomAnimUpdt == true)
	{
		cur_clantag_gf = g_Vars->Misc.Tag;
		g_Globals->DoCustomAnimUpdt = false;
	}
	static float oldTime;

	if (I::Engine->IsInGame())
	{
		if (I::Globals->curtime - oldTime >= 0.5f)
		{
			Marquee(cur_clantag_gf);
			g_Utils->SetClantag(cur_clantag_gf.c_str());
			oldTime = I::Globals->curtime;
		}
	}
}

void DoClanTagChanger() {
	if (g_Vars->Misc.TagChanger == 0)
	{
		g_Utils->SetClantag("ElysiumProject");
	}
	else if (g_Vars->Misc.TagChanger == 1)
	{
		MarqueeTag();
	}
	else if (g_Vars->Misc.TagChanger == 2)
	{
		g_Utils->SetClantag(g_Vars->Misc.Tag);
	}
	else if (g_Vars->Misc.TagChanger == 3)
		MarqueeTag2();
}

CreateMoveFn oCreateMove;
bool __stdcall Hooks::CreateMove(float flInputSampleTime, CUserCmd* pCmd)
{
	oCreateMove(flInputSampleTime, pCmd);

	if (!pCmd || !pCmd->command_number)
		return false;

	g_Globals->SendPacket = true;
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());

	if (!LocalPlayer)
		return false;

	if (g_Vars->Misc.ClanTagChanger)
		DoClanTagChanger();

	if (I::Engine->IsInGame() && I::Engine->IsConnected() && g_Vars->Misc.RankReview && GetAsyncKeyState(VK_TAB))
		RankRevealAll();

	if (!LocalPlayer->IsValid())
		return false;

	DWORD* fp;
	__asm mov fp, ebp;

	C_BaseCombatWeapon* currentWeapon = LocalPlayer->GetActiveWeapon();
	// Auto Pistol
	static bool WasFiring = false;
	if (currentWeapon != nullptr)
	{
		if (currentWeapon->IsPistol() && g_Vars->Misc.AutoPistol && currentWeapon->GetItemDefinitionIndex() != 64)
		{
			if (pCmd->buttons & IN_ATTACK && !currentWeapon->IsKnife() && !currentWeapon->IsGrenade())
			{
				if (WasFiring)
				{
					pCmd->buttons &= ~IN_ATTACK;
				}
			}

			WasFiring = pCmd->buttons & IN_ATTACK ? true : false;
		}
	}


	RunBhop(pCmd);
	LegitStrafe(pCmd);
	g_Legit->legitBackTrack(pCmd);
	g_Trigger->Run(pCmd);
	g_Legit->Run(pCmd);

	/*QAngle oldAngle = pCmd->viewangles;
	C_BaseCombatWeapon* weapon = LocalPlayer->GetActiveWeapon();
	if (weapon)
		LegitAA(LocalPlayer, weapon, pCmd, g_Globals->SendPacket);

	movementfix(oldAngle, pCmd);*/
	pCmd->viewangles.Clamp();
	*(bool*)(*fp - 0x1C) = g_Globals->SendPacket;
	return false;
}