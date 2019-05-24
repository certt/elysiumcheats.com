#include "Main.h"

#define TICK_INTERVAL			(I::Globals->intervalPerTick)
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( I::Globals->intervalPerTick *( t ) )

bool pSilent, Nearest;
float Smooth, rcs_x, rcs_y;
int rcs_start, bone, best_target, nClosestBone;

void lAimbot::Run(CUserCmd* pCmd)
{
	if (I::Engine->IsInGame() && I::Engine->IsConnected() && I::Engine->IsActiveApp() && !g_Vars->Menu.Opened)
	{
		C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
		if (!LocalPlayer) return;
		if (!LocalPlayer->GetAlive()) return;
		FOV = 0.0f; pSilentFOV = 0.0f;
		SetupSettings();
		if (g_Vars->Aimbot.OnKey)
		{
			if (GetAsyncKeyState(g_Vars->Aimbot.Key))
				DoAimbot(pCmd);
		}
		else
		{
			if (pCmd->buttons & IN_ATTACK)
				DoAimbot(pCmd);
		}
	}
}

void lAimbot::DoAimbot(CUserCmd* pCmd)
{
	if (g_Globals->KillDelay >= GetTickCount())
		return;

	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	if (!LocalPlayer) return;
	FindTarget(pCmd);
	if (best_target == -1) return;
	C_BaseEntity* Entity = I::EntityList->GetClientEntity(best_target);
	if (!Entity) return;
	Vector vecBone = Entity->GetBonePosition(ClosestBone(Entity, pCmd));
	if (vecBone.IsZero()) return;

	typedef bool(__cdecl* GoesThroughSmoke)(Vector, Vector);
	static uint32_t GoesThroughSmokeOffset = (uint32_t)g_Utils->FindPatternIDA("client_panorama.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0");
	static GoesThroughSmoke GoesThroughSmokeFunction = (GoesThroughSmoke)GoesThroughSmokeOffset;

	if (g_Vars->Aimbot.SmokeCheck && GoesThroughSmokeFunction(LocalPlayer->GetEyePosition(), vecBone))
		return;

	if (g_Vars->Aimbot.FlashCheck && LocalPlayer->IsFlashed())
		return;

	int ShotsFired = LocalPlayer->iShotsFired();
	QAngle dst = M::CalcAngle(LocalPlayer->GetEyePosition(), vecBone);
	bool doPsile = false;
	doPsile = (ShotsFired < 1 && pSilent) ? true : false;
	float flFov = GetFov(pCmd->viewangles, M::CalcAngle(LocalPlayer->GetEyePosition(), Entity->GetBonePosition(nClosestBone)));
	float dFOV = doPsile ? pSilentFOV : FOV;

	if (flFov > dFOV)
		return;

	if ((rcs_x > 1 || rcs_y > 1) && ShotsFired > rcs_start) {
		if (LocalPlayer->GetPunch().Length() > 0 && LocalPlayer->GetPunch().Length() < 150)
		{
			if (rcs_x > 1)
				dst.x -= LocalPlayer->GetPunch().x * (rcs_x / 50.f);

			if (rcs_y > 1)
				dst.y -= LocalPlayer->GetPunch().y * (rcs_y / 50.f);
		}
	}

	float dSmooth = doPsile ? 0.0f : Smooth / 100.f;

	if (doPsile)
		g_Globals->SendPacket = false;

	dst = CurveSmooth(pCmd->viewangles, dst, dSmooth);
	dst.Normalized();
	dst.Clamp();

	if (doPsile)
	{
		pCmd->viewangles = dst;
		g_Globals->SendPacket = false;
	}
	else
	{
		pCmd->viewangles = dst;
		I::Engine->SetViewAngles(dst);
	}
}

void lAimbot::SetupSettings()
{
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	if (!LocalPlayer) return;
	if (!LocalPlayer->GetAlive()) return;

	C_BaseCombatWeapon* Weapon = LocalPlayer->GetActiveWeapon();
	if (!Weapon) return;

	FOV = 0.0f; pSilentFOV = 0.0f; Smooth = 0.0f; best_target = -1;
	short cwID = Weapon->GetItemDefinitionIndex();

	pSilent = g_Vars->Skinchanger.W[cwID].pSilent;
	pSilentFOV = g_Vars->Skinchanger.W[cwID].pSilentFOV;
	rcs_x = g_Vars->Skinchanger.W[cwID].rcs_x;
	rcs_y = g_Vars->Skinchanger.W[cwID].rcs_y;
	Smooth = g_Vars->Skinchanger.W[cwID].Smooth;
	FOV = g_Vars->Skinchanger.W[cwID].FOV;
	Nearest = g_Vars->Skinchanger.W[cwID].Nearest;
	rcs_start = g_Vars->Skinchanger.W[cwID].rcs_start;
	bone = g_Vars->Skinchanger.W[cwID].bone;
}

QAngle lAimbot::CurveSmooth(QAngle& viewangles, QAngle target, float factor)
{
	factor *= 10;

	if (factor <= 0.0f)
		return target;

	QAngle delta = target - viewangles;
	delta.Clamp();

	float factorx = factor, factory = factor;

	if (delta.x < 0.0f)
	{
		if (factorx > fabs(delta.x))
			factorx = fabs(delta.x);

		target.x = viewangles.x - factorx;
	}
	else
	{
		if (factorx > delta.x)
			factorx = delta.x;

		target.x = viewangles.x + factorx;
	}

	if (delta.y < 0.0f)
	{
		if (factory > fabs(delta.y))
			factory = fabs(delta.y);

		target.y = viewangles.y - factory;
	}
	else
	{
		if (factory > delta.y)
			factory = delta.y;

		target.y = viewangles.y + factory;
	}

	return target;
}

void lAimbot::FindTarget(CUserCmd* pCmd)
{
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	if (!LocalPlayer) 
		return;

	float flMax = 8192.f;
	for (int i = 0; i <= 65; ++i)
	{
		C_BaseEntity* Entity = I::EntityList->GetClientEntity(i);

		if (!Entity)
			continue;

		if (!Entity->IsValid())
			continue;

		if (Entity->GetTeam() == LocalPlayer->GetTeam() && !g_Vars->Aimbot.OnTeam)
			continue;

		nClosestBone = ClosestBone(Entity, pCmd);

		if (!Entity->IsVisible(nClosestBone))
			continue;

		float flFov = GetFov(pCmd->viewangles, M::CalcAngle(LocalPlayer->GetEyePosition(), Entity->GetBonePosition(nClosestBone)));

		if (flFov < flMax) {
			flMax = flFov;
			best_target = i;
		}
	}

    best_target;
}

float lAimbot::GetFov(const QAngle& viewAngle, const QAngle& aimAngle)
{
	QAngle delta = aimAngle - viewAngle;
	delta.Normalized();
	return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}

int lAimbot::ClosestBone(C_BaseEntity *Entity, CUserCmd* cmd)
{
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	if (LocalPlayer)
	{
		if (Nearest)
		{
			float flBestFov = 360.f;

			studiohdr_t* pStudioModel = I::ModelInfo->GetStudioModel(Entity->GetModel());
			if (!pStudioModel) return -1;
			mstudiohitboxset_t* set = pStudioModel->pHitboxSet(Entity->GetHitboxSet());
			if (!set) return -1;

			for (int i = 0; i < 8; i++)
			{
				mstudiobbox_t* hitbox = set->pHitbox(i);
				if (!hitbox) continue;
				float Fov = GetFov(cmd->viewangles, M::CalcAngle(LocalPlayer->GetEyePosition(), Vector(playerStruct[Entity->EntIndex()].matrix[hitbox->bone][0][3], playerStruct[Entity->EntIndex()].matrix[hitbox->bone][1][3], playerStruct[Entity->EntIndex()].matrix[hitbox->bone][2][3])));

				if (Fov < flBestFov)
				{
					flBestFov = Fov;
					bone = hitbox->bone;
					continue;
				}
			}
			return bone;
		}
		else return bone;
	}
}

void lAimbot::legitBackTrack(CUserCmd* cmd)
{
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	if (!LocalPlayer)
		return;

	if (g_Vars->Aimbot.BackTrack)
	{
		int bestTargetIndex = -1;
		float bestFov = FLT_MAX;
		if (!LocalPlayer->IsValid())
			return;

		for (int i = 0; i < I::Engine->GetMaxClients(); i++)
		{
			C_BaseEntity* entity = I::EntityList->GetClientEntity(i);

			if (!entity)
				continue;

			if (entity == LocalPlayer)
				continue;

			if (!entity->IsValid())
				continue;

			if (entity->GetTeam() == LocalPlayer->GetTeam())
				continue;

			float simtime = entity->GetSimulationTime();
			Vector hitboxPos = entity->GetBonePosition(0);

			headPositions[i][cmd->command_number % 13] = backtrackData{ simtime, hitboxPos };
			Vector ViewDir = angle_vector(cmd->viewangles + (LocalPlayer->GetPunch() * 2.f));
			float FOVDistance = distance_point_to_line(hitboxPos, LocalPlayer->GetEyePosition(), ViewDir);

			if (bestFov > FOVDistance)
			{
				bestFov = FOVDistance;
				bestTargetIndex = i;
			}
		}

		float bestTargetSimTime = 0;
		if (bestTargetIndex != -1)
		{
			float tempFloat = FLT_MAX;
			Vector ViewDir = angle_vector(cmd->viewangles + (LocalPlayer->GetPunch() * 2.f));

			if (ViewDir.IsZero() || !ViewDir.IsValid())
				return;

			for (int t = 0; t < g_Vars->Aimbot.BT_ticks; ++t)
			{
				float tempFOVDistance = distance_point_to_line(headPositions[bestTargetIndex][t].hitboxPos, LocalPlayer->GetEyePosition(), ViewDir);
				if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > LocalPlayer->GetSimulationTime() - 1)
				{
					tempFloat = tempFOVDistance;
					bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
				}
			}
			if (!bestTargetSimTime == 0)
				if (cmd->buttons & IN_ATTACK)
					cmd->tick_count = TIME_TO_TICKS(bestTargetSimTime);
		}
	}
}

backtrackData headPositions[64][12];