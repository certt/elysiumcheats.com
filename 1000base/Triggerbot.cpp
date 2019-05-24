#include "Main.h"

void lTrigger::Run(CUserCmd* pCmd)
{
	static int CustomDelay = 0;
	if (I::Engine->IsInGame() && I::Engine->IsConnected() && I::Engine->IsActiveApp()) {
		if (g_Vars->Triggerbot.Enabled && !g_Vars->Menu.Opened) {
			if ((GetAsyncKeyState(g_Vars->Triggerbot.Key) || !g_Vars->Triggerbot.OnKey)) {
				C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
				if (!LocalPlayer)
					return;

				if (LocalPlayer->GetAlive()) 
				{
					if (g_Vars->Triggerbot.Delay > 1)
					{
						if (GetTickCount() > CustomDelay)
						{
							DoTrigger(pCmd, LocalPlayer);
							CustomDelay = GetTickCount() + g_Vars->Triggerbot.Delay;
						}
					}
					else
						DoTrigger(pCmd, LocalPlayer);
				}
			}
		}
	}
}

bool IsHitChance(float flChance, C_BaseCombatWeapon* pWep)
{
	if (flChance >= 99.f)
		flChance = 99.f;

	if (flChance < 1)
		flChance = 1;

	float flSpread = pWep->GetInaccuracyReal() * 10;
	return((((100.f - flChance) * 0.65f) * 0.01125) >= flSpread);
}

void lTrigger::DoTrigger(CUserCmd* pCmd, C_BaseEntity* LocalPlayer)
{
	Vector traceStart, traceEnd;
	trace_t tr;
	QAngle viewAngles;
	I::Engine->GetViewAngles(viewAngles);
	QAngle viewAngles_rcs = viewAngles + LocalPlayer->GetPunch() * 2.0f;
	M::AngleVectors(viewAngles_rcs, &traceEnd);
	traceStart = LocalPlayer->GetEyePosition();
	traceEnd = traceStart + (traceEnd * 8192.0f);
	Ray_t ray;
	ray.Init(traceStart, traceEnd);
	CTraceFilter traceFilter;
	traceFilter.pSkip = LocalPlayer;
	I::EngineTrace->TraceRay(ray, 0x46004003, &traceFilter, &tr);
	C_BaseEntity* player = tr.m_pEnt;

	if (!player->IsValid()) return;
	if (player->GetImmune()) return;
	if (player->GetClientClass()->m_ClassID != CCSPlayer) return;
	if (player == LocalPlayer) return;
	if (player->GetTeam() == LocalPlayer->GetTeam() && !g_Vars->Triggerbot.OnTeam) return;

	if (!tr.m_pEnt) return;
	int hitgroup = tr.hitgroup;
	bool didHit = false;

	typedef bool(__cdecl* GoesThroughSmoke)(Vector, Vector);
	static uint32_t GoesThroughSmokeOffset = (uint32_t)g_Utils->FindPatternIDA("client_panorama.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0");
	static GoesThroughSmoke GoesThroughSmokeFunction = (GoesThroughSmoke)GoesThroughSmokeOffset;

	Vector CrosshairForward;
	M::AngleVectors(pCmd->viewangles, &CrosshairForward);
	CrosshairForward *= 10000.0f;

	if (g_Vars->Triggerbot.SmokeCheck && GoesThroughSmokeFunction(LocalPlayer->GetEyePosition(), CrosshairForward))
		return;

	if (g_Vars->Triggerbot.FlashCheck && LocalPlayer->IsFlashed())
		return;

	if (g_Vars->Triggerbot.Head && hitgroup == HITGROUP_HEAD) didHit = true;
	if (g_Vars->Triggerbot.Chest && hitgroup == HITGROUP_CHEST) didHit = true;
	if (g_Vars->Triggerbot.Stomach && hitgroup == HITGROUP_STOMACH) didHit = true;
	if (g_Vars->Triggerbot.Arms && (hitgroup == HITGROUP_LEFTARM || hitgroup == HITGROUP_RIGHTARM)) didHit = true;
	if (g_Vars->Triggerbot.Legs && (hitgroup == HITGROUP_LEFTLEG || hitgroup == HITGROUP_RIGHTLEG)) didHit = true;

	if (didHit && (!g_Vars->Triggerbot.Hitchance || IsHitChance(g_Vars->Triggerbot.HitchanceAM, LocalPlayer->GetActiveWeapon())))
	{
		if(LocalPlayer->GetActiveWeapon()->GetItemDefinitionIndex() == WEAPON_REVOLVER)
			pCmd->buttons |= IN_ATTACK2;
		else
		{
			pCmd->buttons |= IN_ATTACK;

			static bool already_shot = false;
			if (LocalPlayer->GetActiveWeapon()->IsPistol())
			{
				if (pCmd->buttons & IN_ATTACK)
					if (already_shot)
						pCmd->buttons &= ~IN_ATTACK;

				already_shot = pCmd->buttons & IN_ATTACK ? true : false;
			}
		}
	}		
}