#include "Main.h"

struct Sound_s
{
	float Radius = 0.0;
	ULONGLONG dwTime;
	Vector vOrigin;
}; std::vector<Sound_s> Sound;
std::string textDropped;

void AngleVectors2(const Vector &vAngles, Vector& vForward)
{
	float	sp, sy, cp, cy;

	sy = sin(DEG2RAD(vAngles[1]));
	cy = cos(DEG2RAD(vAngles[1]));

	sp = sin(DEG2RAD(vAngles[0]));
	cp = cos(DEG2RAD(vAngles[0]));

	vForward.x = cp * cy;
	vForward.y = cp * sy;
	vForward.z = -sp;
}

FORCEINLINE vec_t DotProduct(const Vector& a, const Vector& b)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	return(a.x*b.x + a.y*b.y + a.z*b.z);
}

void GrenadePrediction()
{
	if (I::Engine->IsInGame() && I::Engine->IsConnected())
	{
		C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
		if (!LocalPlayer)
			return;

		const float TIMEALIVE = 5.f;
		const float GRENADE_COEFFICIENT_OF_RESTITUTION = 0.4f;

		float fStep = 0.1f;
		float fGravity = 800.0f / 8.f;

		Vector vPos, vThrow, vThrow2;
		Vector vStart;

		int iCollisions = 0;

		QAngle vViewAngles;
		I::Engine->GetViewAngles(vViewAngles);

		vThrow[0] = vViewAngles[0];
		vThrow[1] = vViewAngles[1];
		vThrow[2] = vViewAngles[2];

		if (vThrow[0] < 0)
			vThrow[0] = -10 + vThrow[0] * ((90 - 10) / 90.0);
		else
			vThrow[0] = -10 + vThrow[0] * ((90 + 10) / 90.0);

		float fVel = (90 - vThrow[0]) * 4;
		if (fVel > 500)
			fVel = 500;

		AngleVectors2(vThrow, vThrow2);

		Vector vEye = LocalPlayer->GetEyePosition();
		vStart[0] = vEye[0] + vThrow2[0] * 16;
		vStart[1] = vEye[1] + vThrow2[1] * 16;
		vStart[2] = vEye[2] + vThrow2[2] * 16;

		vThrow2[0] = (vThrow2[0] * fVel) + LocalPlayer->GetVelocity()[0];
		vThrow2[1] = (vThrow2[1] * fVel) + LocalPlayer->GetVelocity()[1];
		vThrow2[2] = (vThrow2[2] * fVel) + LocalPlayer->GetVelocity()[2];


		if (LocalPlayer->IsValid() && LocalPlayer->GetActiveWeapon()->IsGrenade())
		{
			for (float fTime = 0.0f; fTime < TIMEALIVE; fTime += fStep)
			{
				vPos = vStart + vThrow2 * fStep;

				Ray_t ray;
				trace_t tr;
				CTraceFilter loc;
				loc.pSkip = LocalPlayer;

				ray.Init(vStart, vPos);
				I::EngineTrace->TraceRay(ray, MASK_SOLID, &loc, &tr);

				if (tr.DidHit())
				{
					float anglez = DotProduct(Vector(0, 0, 1), tr.plane.normal);
					float invanglez = DotProduct(Vector(0, 0, -1), tr.plane.normal);
					float angley = DotProduct(Vector(0, 1, 0), tr.plane.normal);
					float invangley = DotProduct(Vector(0, -1, 0), tr.plane.normal);
					float anglex = DotProduct(Vector(1, 0, 0), tr.plane.normal);
					float invanglex = DotProduct(Vector(3 - 1, 0, 0), tr.plane.normal);
					float scale = tr.endpos.DistTo(LocalPlayer->GetOrigin()) / 60;
					Color color = Color(0, 0, 255);

					vThrow2 = tr.plane.normal * -2.0f * DotProduct(vThrow2, tr.plane.normal) + vThrow2;
					vThrow2 *= GRENADE_COEFFICIENT_OF_RESTITUTION;

					iCollisions++;
					if (iCollisions > 2)
						break;

					vPos = vStart + vThrow2 * tr.fraction * fStep;
					fTime += (fStep * (1 - tr.fraction));
				}

				Vector vOutStart, vOutEnd;

				if (g_Utils->WorldToScreen(vStart, vOutStart) && g_Utils->WorldToScreen(vPos, vOutEnd))
				{
					g_ImRender->DrawLine((int)vOutStart.x, (int)vOutStart.y, (int)vOutEnd.x, (int)vOutEnd.y, Color::Black(), 2.25f);
					g_ImRender->DrawLine((int)vOutStart.x, (int)vOutStart.y, (int)vOutEnd.x, (int)vOutEnd.y, Color::White(), 2.0f);
				}

				vStart = vPos;
				vThrow2.z -= fGravity * tr.fraction * fStep;
			}
		}
	}
}

void RenderNadeEsp(C_BaseEntity* nade)
{
	if (!nade)
		return;

	Vector vPosScreen, pPos = nade->GetOrigin();
	if (pPos.IsZero())
		return;

	const model_t* model = nade->GetModel();
	if (!model)
		return;

	studiohdr_t* hdr = I::ModelInfo->GetStudioModel(model);
	if (!hdr)
		return;

	Color Nadecolor;
	std::string entityName = hdr->name, icon_character;
	switch (nade->GetClientClass()->m_ClassID)
	{
	case 9:
		if (entityName[16] == 's')
		{
			entityName = "* Flash *";
		}
		else
		{
			entityName = "* HE *";
		}
		break;
	case 134:
		entityName = "* Smoke *";
		break;
	case 98:
		entityName = "* Fire *";
		break;
	case 41:
		entityName = "* Decoy *";
		break;
	default:
		return;
	}

	if (g_Utils->WorldToScreen(pPos, vPosScreen))
		g_ImRender->DrawString(g_Globals->ESP_MAIN, 14.0f, 1, vPosScreen.x, vPosScreen.y, Color::White(), false, false, entityName.c_str());
}


void Visuals::ESP()
{
	if (I::Engine->IsInGame() && I::Engine->IsConnected() && I::Engine->IsActiveApp())
	{
		if (!g_Vars->Visuals.Enabled)
			return;

		if (g_Vars->Visuals.Sound.Enabled)
		{
			DrawSoundEsp();
			SoundUpdate();
		}

		if (g_Vars->Visuals.GH)
			GrenadePrediction();

		DrawEntity();
		DrawDropped();
		dOther();
	}
}

void Visuals::DrawEntity()
{
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	if (!LocalPlayer)
		return;

	for (int i = 1; i <= 65; ++i)
	{
		if (!playerStruct[i].isvisible && g_Vars->Visuals.VisibleCheck)
			continue;

		C_BaseEntity* Entity = I::EntityList->GetClientEntity(i);
		if (!Entity)
			continue;

		if (Entity == LocalPlayer)
			continue;

		if (!Entity->IsValid())
			continue;

		PlayerInfo_t pInfo;

		if (!I::Engine->GetPlayerInfo(i, &pInfo))
			continue;

		bool isEnemy = Entity->GetTeam() != LocalPlayer->GetTeam();

		if (!isEnemy && !g_Vars->Visuals.Filter.Teammates)
			continue;

		Vector m_vecFoot = Entity->GetOrigin();
		Vector m_vecHead;
		Vector m_screenFoot;
		Vector m_screenHead;

		if ((Entity->GetFlags() & FL_DUCKING))
			m_vecHead = m_vecFoot + Vector(0.f, 0.f, 52.f);
		else m_vecHead = m_vecFoot + Vector(0.f, 0.f, 72.f);

		if (g_Utils->WorldToScreen(m_vecFoot, m_screenFoot) &&
			g_Utils->WorldToScreen(m_vecHead, m_screenHead))
		{

			static DWORD IsSpotted = g_pNetvars->GetOffset("DT_BaseEntity", "m_bSpotted");
			if(g_Vars->Visuals.InGameRadar)
			*(char*)((DWORD)(Entity)+IsSpotted) = 1;

			if (g_Vars->Aimbot.BackTrackV)
				dBackTrack(i);

			if (g_Vars->Visuals.Skeleton)
				dSkeleton(Entity);

			float lineHeight = (m_screenFoot.y - m_screenHead.y), edgeWidth = lineHeight / 4;
			float pixelPerHp = lineHeight / 100.f, pad_h = 0, pad_h2 = 0;
			Vector leftUpCorn = Vector(m_screenHead.x - edgeWidth, m_screenHead.y, 0.f);
			Vector rightUpCorn = Vector(m_screenHead.x + edgeWidth, m_screenHead.y, 0.f);
			Vector leftDownCorn = Vector(m_screenHead.x - edgeWidth, m_screenFoot.y, 0.f);
			Vector rightDownCorn = Vector(m_screenHead.x + edgeWidth, m_screenFoot.y, 0.f);

			if (g_Vars->Visuals.Box)
			{
				if(playerStruct[i].isvisible)
					g_ImRender->DrawEspBox(leftUpCorn, rightDownCorn, !isEnemy ? Color(int(g_Vars->Colors.BoxTeamV[0] * 255.f), int(g_Vars->Colors.BoxTeamV[1] * 255.f), int(g_Vars->Colors.BoxTeamV[2] * 255.f)) : Color(int(g_Vars->Colors.BoxEnemyV[0] * 255.f), int(g_Vars->Colors.BoxEnemyV[1] * 255.f), int(g_Vars->Colors.BoxEnemyV[2] * 255.f)), 2.0f);
				else
					g_ImRender->DrawEspBox(leftUpCorn, rightDownCorn, !isEnemy ? Color(int(g_Vars->Colors.BoxTeam[0] * 255.f), int(g_Vars->Colors.BoxTeam[1] * 255.f), int(g_Vars->Colors.BoxTeam[2] * 255.f)) : Color(int(g_Vars->Colors.BoxEnemy[0] * 255.f), int(g_Vars->Colors.BoxEnemy[1] * 255.f), int(g_Vars->Colors.BoxEnemy[2] * 255.f)), 2.0f);
			}

			if (g_Vars->Visuals.ARMORbar && Entity->GetArmor() >= 1)
			{
				g_ImRender->DrawLine(rightUpCorn.x + 5.75f, rightUpCorn.y - 1.0f, rightUpCorn.x + 5.75f, rightDownCorn.y, Color(30, 30, 30, 110), 3.0f);
				g_ImRender->DrawLine(rightUpCorn.x + 5.75f, rightUpCorn.y + ((pixelPerHp * (100 - Entity->GetArmor()))) - 1.0f, rightUpCorn.x + 5.75f, rightDownCorn.y, Color(65, 125, 193), 3.0f);
				g_ImRender->DrawRect(rightUpCorn.x + 3.5f, rightUpCorn.y - 1.0f, rightUpCorn.x + 8.0f, rightDownCorn.y + 1.5f, Color::Black(), 0.25f);
			}

			if (g_Vars->Visuals.HPbar)
			{
				g_ImRender->DrawLine(leftUpCorn.x - 5.75f, leftUpCorn.y - 1.0f, leftUpCorn.x - 5.75f, leftDownCorn.y, Color(30, 30, 30, 110), 3.0f);
				g_ImRender->DrawLine(leftUpCorn.x - 5.75f, leftUpCorn.y + ((pixelPerHp * (100 - Entity->GetHealth()))) - 1.0f, leftUpCorn.x - 5.75f, leftDownCorn.y, Color(65, 193, 133), 3.0f);
				g_ImRender->DrawRect(leftUpCorn.x - 8.0f, leftUpCorn.y - 1.0f, leftUpCorn.x - 3.5f, leftDownCorn.y + 1.5f, Color::Black(), 0.25f);
			}

			if (g_Vars->Visuals.NickName)
				g_ImRender->DrawString(g_Globals->ESP_MAIN, 14.0f, 1, rightUpCorn.x - ((rightUpCorn.x - leftUpCorn.x) / 2), rightUpCorn.y - 14.0f, Color(int(g_Vars->Colors.ESPtext[0] * 255.f), int(g_Vars->Colors.ESPtext[1] * 255.f), int(g_Vars->Colors.ESPtext[2] * 255.f)), false, false, pInfo.szName);

			if (Entity->IsDefusing())
			{
				g_ImRender->DrawString(g_Globals->ESP_MAIN, 15.0f, 0, rightUpCorn.x + 12.5f, rightUpCorn.y - 0.5f, Color::Red(), false, false, "Defusing!");
				pad_h2 += 14.5f;
			}

			C_BaseCombatWeapon* currentWeapon = Entity->GetActiveWeapon();
			if (currentWeapon)
			{
				if (g_Vars->Visuals.InfoBox)
				{
					float distance = g_Utils->GetDistance(m_screenFoot, LocalPlayer), font_size = 16.0f - ((distance / 100.0f) * 0.20f);
					g_ImRender->DrawString(g_Globals->ESP_MAIN, font_size, 1, rightUpCorn.x - ((rightUpCorn.x - leftUpCorn.x) / 2), rightUpCorn.y - 18.0f, Color(int(g_Vars->Colors.ESPtext[0] * 255.f), int(g_Vars->Colors.ESPtext[1] * 255.f), int(g_Vars->Colors.ESPtext[2] * 255.f)), true, isEnemy, "[%s] %s | %dhp", currentWeapon->GetWeaponName().c_str(), pInfo.szName, Entity->GetHealth());
				}

				if (g_Vars->Visuals.WeaponIC)
				{
					if (g_Vars->Visuals.WeaponStyle == 0) g_ImRender->DrawString(g_Globals->WEAP_ICON, 16.0f, 2, rightDownCorn.x - ((rightDownCorn.x - leftDownCorn.x) / 2), rightDownCorn.y + 2.0f, Color(int(g_Vars->Colors.ESPtext[0] * 255.f), int(g_Vars->Colors.ESPtext[1] * 255.f), int(g_Vars->Colors.ESPtext[2] * 255.f)), false, false, currentWeapon->GetWeaponNameIcon().c_str());
					else g_ImRender->DrawString(g_Globals->ESP_MAIN, 14.0f, 1, rightDownCorn.x - ((rightDownCorn.x - leftDownCorn.x) / 2), rightDownCorn.y + 2.0f, Color(int(g_Vars->Colors.ESPtext[0] * 255.f), int(g_Vars->Colors.ESPtext[1] * 255.f), int(g_Vars->Colors.ESPtext[2] * 255.f)), false, false, currentWeapon->GetWeaponName().c_str());
				}

				if (!currentWeapon->IsKnife())
					if (g_Vars->Visuals.Ammo)
						g_ImRender->DrawString(g_Globals->ESP_MAIN, 15.0f, 1, rightUpCorn.x + 12.5f, rightUpCorn.y - 0.5f + pad_h2, Color(int(g_Vars->Colors.ESPtext[0] * 255.f), int(g_Vars->Colors.ESPtext[1] * 255.f), int(g_Vars->Colors.ESPtext[2] * 255.f)), false, false, "[%d/%d]", currentWeapon->GetClip1(), currentWeapon->GetClip2());
			}
		}
	}
}

void Visuals::DrawDropped()
{
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	if (!LocalPlayer)
		return;

	for (int i = 65; i <= I::EntityList->GetMaxEntities(); ++i)
	{
		C_BaseEntity* Entity = I::EntityList->GetClientEntity(i);
		if (!Entity)
			continue;

		Vector vPosScreen, pPos = Entity->GetOrigin();
		if (pPos.IsZero())
			continue;

		char* EntityName = Entity->GetClientClass()->m_pNetworkName;

		if (!EntityName)
			continue;

		if (g_Vars->Visuals.DroppedWeap)
		{
			if (strstr(EntityName, charenc("CWeapon"))) {
				textDropped = std::string(EntityName).substr(7);
				if (g_Utils->WorldToScreen(pPos, vPosScreen))
					g_ImRender->DrawString(g_Globals->ESP_MAIN, 14.0f, 1, vPosScreen.x, vPosScreen.y, Color(int(g_Vars->Colors.ESPtext[0] * 255.f), int(g_Vars->Colors.ESPtext[1] * 255.f), int(g_Vars->Colors.ESPtext[2] * 255.f)), false, false, textDropped.c_str());
			}

			if (strstr(EntityName, charenc("CAK47"))) {
				textDropped = strenc("AK47");
				if (g_Utils->WorldToScreen(pPos, vPosScreen))
					g_ImRender->DrawString(g_Globals->ESP_MAIN, 14.0f, 1, vPosScreen.x, vPosScreen.y, Color(int(g_Vars->Colors.ESPtext[0] * 255.f), int(g_Vars->Colors.ESPtext[1] * 255.f), int(g_Vars->Colors.ESPtext[2] * 255.f)), false, false, textDropped.c_str());
			}

			if (strstr(EntityName, charenc("CDEagle"))) {
				textDropped = strenc("Deagle");
				if (g_Utils->WorldToScreen(pPos, vPosScreen))
					g_ImRender->DrawString(g_Globals->ESP_MAIN, 14.0f, 1, vPosScreen.x, vPosScreen.y, Color(int(g_Vars->Colors.ESPtext[0] * 255.f), int(g_Vars->Colors.ESPtext[1] * 255.f), int(g_Vars->Colors.ESPtext[2] * 255.f)), false, false, textDropped.c_str());
			}

			if (strcmp(EntityName, charenc("CKnife")) == 0) {
				textDropped = strenc("Knife");
				if (g_Utils->WorldToScreen(pPos, vPosScreen))
					g_ImRender->DrawString(g_Globals->ESP_MAIN, 14.0f, 1, vPosScreen.x, vPosScreen.y, Color(int(g_Vars->Colors.ESPtext[0] * 255.f), int(g_Vars->Colors.ESPtext[1] * 255.f), int(g_Vars->Colors.ESPtext[2] * 255.f)), false, false, textDropped.c_str());
			}
		}

		if (g_Vars->Visuals.DroppedC4)
		{
			if (strcmp(EntityName, charenc("CC4")) == 0)
			{
				textDropped = strenc("C4");
				if (g_Utils->WorldToScreen(pPos, vPosScreen))
					g_ImRender->DrawString(g_Globals->ESP_MAIN, 14.0f, 1, vPosScreen.x, vPosScreen.y, Color(int(g_Vars->Colors.ESPtext[0] * 255.f), int(g_Vars->Colors.ESPtext[1] * 255.f), int(g_Vars->Colors.ESPtext[2] * 255.f)), false, false, textDropped.c_str());
			}

			if (strcmp(EntityName, charenc("CPlantedC4")) == 0)
			{
				int w, h;
				I::Engine->GetScreenSize(w, h);
				char buffer[64];
				int w_cor = w / 12;
				int h_cor = h / 12;
				int h_space = 0;
				float lineHeightHor = ((w_cor * 8) - (w_cor * 4)) / 40.0f;
				float lifetime = Entity->GetC4BlowTime() - (I::Globals->intervalPerTick * LocalPlayer->GetTickBase());
				if (lifetime < 0.0f) lifetime = 0.0f;

				if (lifetime > 0.001f)
				{
					// Draw background
					g_ImRender->DrawRectFilled((w_cor * 4), (h_cor * 11), (w_cor * 8), (h_cor * 11) + 10, Color(30, 30, 30, 110));
					// Draw green line
					g_ImRender->DrawRectFilledMulti((w_cor * 4), (h_cor * 11), (w_cor * 8) - ((lineHeightHor * (40.0f - lifetime))) - 1.0f, (h_cor * 11) + 10, Color(65, 193, 133), Color(65, 193, 133), Color(65, 216, 133), Color(65, 216, 133));
					// Draw blue line
					if (lifetime > 5.001f)
						g_ImRender->DrawRectFilledMulti((w_cor * 4), (h_cor * 11), (w_cor * 8) - ((lineHeightHor * (40.0f - 5.f))) - 1.0f, (h_cor * 11) + 10, Color(65, 82, 193), Color(65, 82, 193), Color(65, 135, 202), Color(65, 135, 202));
					// Draw outline
					g_ImRender->DrawRect((w_cor * 4), (h_cor * 11), (w_cor * 8), (h_cor * 11) + 10, Color::Black(), 0.25f);

					h_space += 35;
				}

				if (Entity->GetBombDefuser() > 0)
				{
					float countdown = Entity->GetC4DefuseCountDown() - (LocalPlayer->GetTickBase() * I::Globals->intervalPerTick);
					if (countdown > 0.01f)
					{
						if (lifetime > countdown)
						{
							char defuseTimeString[64];
							sprintf_s(defuseTimeString, sizeof(defuseTimeString) - 1, "D, %.1f", countdown);
							textDropped = defuseTimeString;
						}
						else
						{
							textDropped = strenc("You've not time!");
						}
					}
				}
				else
				{
					sprintf_s(buffer, "C4, %.1f", lifetime);
					textDropped = buffer;
				}

				if (g_Utils->WorldToScreen(pPos, vPosScreen))
					g_ImRender->DrawString(g_Globals->ESP_MAIN, 14.0f, 1, vPosScreen.x, vPosScreen.y, Color(int(g_Vars->Colors.ESPtext[0] * 255.f), int(g_Vars->Colors.ESPtext[1] * 255.f), int(g_Vars->Colors.ESPtext[2] * 255.f)), false, false, textDropped.c_str());
			}
		}

		if (g_Vars->Visuals.DrawGrenades)
			RenderNadeEsp(Entity);
	}
}

void Visuals::dOther()
{
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	if (!LocalPlayer)
		return;

	int W, H;
	I::Engine->GetScreenSize(W, H);
	if (g_Vars->Visuals.FOV)
	{
		if (g_Legit->FOV > 0.05f) g_ImRender->DrawFilledCircle(W / 2, H / 2, g_Legit->FOV * (H / 90.0f), Color(1, 1, 1, 115));

		if (g_Legit->pSilentFOV > 0.05f) g_ImRender->DrawFilledCircle(W / 2, H / 2, g_Legit->pSilentFOV * (H / 90.0f), Color(115, 1, 1, 115));
	}

	if(g_Vars->Misc.LegitAA)
	if (g_Vars->Misc.Direction == true)
		g_ImRender->DrawString(g_Globals->ESP_MAIN, 14.0f, 1, 20.0f, 20.0f, Color::Green(), false, false, " < left");
	else
		g_ImRender->DrawString(g_Globals->ESP_MAIN, 14.0f, 1, 20.0f, 20.0f, Color::Red(), false, false, "right > ");

	if (g_Globals->HitMarker < 0.f)
		g_Globals->HitMarker = 0.f;
	else if (g_Globals->HitMarker > 0.f)
		g_Globals->HitMarker -= 0.01f;

	if (g_Globals->HitMarker > 0.f)
	{
		g_ImRender->DrawLine(W / 2 - 5, H / 2 - 5, W / 2 - 3, H / 2 - 3, Color(255, 255, 255, int(g_Globals->HitMarker * 255.f)), 1.0f);
		g_ImRender->DrawLine(W / 2 - 5, H / 2 + 5, W / 2 - 3, H / 2 + 3, Color(255, 255, 255, int(g_Globals->HitMarker * 255.f)), 1.0f);
		g_ImRender->DrawLine(W / 2 + 5, H / 2 - 5, W / 2 + 3, H / 2 - 3, Color(255, 255, 255, int(g_Globals->HitMarker * 255.f)), 1.0f);
		g_ImRender->DrawLine(W / 2 + 5, H / 2 + 5, W / 2 + 3, H / 2 + 3, Color(255, 255, 255, int(g_Globals->HitMarker * 255.f)), 1.0f);
	}

	if (g_Vars->Visuals.RecoilCS)
	{
		if (LocalPlayer->iShotsFired() > 0)
		{
			int crX = W / 2, crY = H / 2;
			int dy = H / g_Globals->FOV;
			int dx = H / g_Globals->FOV;
			int drX = crX - (int)(dx * LocalPlayer->GetPunch().y);
			int drY = crY + (int)(dy * LocalPlayer->GetPunch().x);
			g_ImRender->DrawFilledCircle(drX, drY, 2.55f, Color::Black());
			g_ImRender->DrawFilledCircle(drX, drY, 2.35f, Color::White());
		}
	}

	if (g_Vars->Misc.SniperCross)
	{
		C_BaseCombatWeapon* localWeapon = LocalPlayer->GetActiveWeapon();

		if (localWeapon != nullptr)
		{
			if (localWeapon->IsSniper())
			{
				int crX = W / 2, crY = H / 2;
				g_ImRender->DrawLine(crX - 5, crY, crX + 5, crY, Color(255, 255, 255), 1.0f);
				g_ImRender->DrawLine(crX, crY - 5, crX, crY + 5, Color(255, 255, 255), 1.0f);
			}
		}
	}
}

void Visuals::SoundUpdate() {
	for (size_t i = 0; i < Sound.size(); i++)
	{
		if (Sound[i].Radius <= 25)
			Sound[i].Radius += 0.3;

		if (Sound[i].dwTime + g_Vars->Visuals.Sound.Time <= GetTickCount64())
			Sound.erase(Sound.begin() + i);
	}
}

void Visuals::AddSound(Vector vOrigin) {
	Sound_s Sound_Entry;
	Sound_Entry.dwTime = GetTickCount64();
	Sound_Entry.vOrigin = vOrigin;
	Sound.push_back(Sound_Entry);
}

void Visuals::DrawSoundEsp() {
	for (size_t i = 0; i < Sound.size(); i++) {
		Vector vScreen;
		if (g_Utils->WorldToScreen(Sound[i].vOrigin, vScreen))
			g_ImRender->DrawWave(Sound[i].vOrigin, Sound[i].Radius, Color(int(g_Vars->Colors.Sound[0] * 255.f), int(g_Vars->Colors.Sound[1] * 255.f), int(g_Vars->Colors.Sound[2] * 255.f)), 2.5f);
	}
}

void Visuals::OnPlaySound(const Vector* pOrigin, int iEntIndex) {
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());

	if (!LocalPlayer)
		return;

	C_BaseEntity* Entity = I::EntityList->GetClientEntity(iEntIndex);

	if (!Entity)
		return;

	if (Entity == LocalPlayer)
		return;

	if (Entity->GetTeam() == LocalPlayer->GetTeam() && !g_Vars->Visuals.Filter.Teammates)
		return;

	if (g_Vars->Visuals.Sound.Enabled && LocalPlayer && pOrigin)
		AddSound(*pOrigin);
}

void Visuals::ResetESP() {
	Sound.clear();
}

void Visuals::dBackTrack(int index)
{
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	if (!LocalPlayer)
		return;

	if (LocalPlayer->IsValid())
	{
		for (int t = 0; t < g_Vars->Aimbot.BT_ticks; ++t)
		{
			Vector screenbacktrack[64][12];
			if (headPositions[index][t].simtime && headPositions[index][t].simtime + 1 > LocalPlayer->GetSimulationTime())
				if (g_Utils->WorldToScreen(headPositions[index][t].hitboxPos, screenbacktrack[index][t]))
					g_ImRender->DrawLine(screenbacktrack[index][t].x, screenbacktrack[index][t].y, screenbacktrack[index][t].x + 2, screenbacktrack[index][t].y + 2, Color::Red(), 1.0f);
		}
	}
	else memset(&headPositions[0][0], 0, sizeof(headPositions));
}

void Visuals::dSkeleton(C_BaseEntity* Entity)
{
	if (Entity)
	{
		studiohdr_t* pStudioModel = I::ModelInfo->GetStudioModel(Entity->GetModel());
		if (pStudioModel && pStudioModel != nullptr)
		{

			for (int i = 0; i < pStudioModel->numbones; i++) {
				mstudiobone_t* pBone = pStudioModel->pBone(i);
				if (pBone && (pBone->flags & 0x100) && pBone->parent != -1)
				{
					Vector vecParentPos, vecChildPos;
					Vector vecParent, vecChild;
					M::MatrixPosition(playerStruct[Entity->EntIndex()].matrix[i], vecChildPos);
					M::MatrixPosition(playerStruct[Entity->EntIndex()].matrix[pBone->parent], vecParentPos);
					if (g_Utils->WorldToScreen(vecChildPos, vecChild) && g_Utils->WorldToScreen(vecParentPos, vecParent))
						g_ImRender->DrawLine(vecChild.x, vecChild.y, vecParent.x, vecParent.y, Color(int(g_Vars->Colors.Skeleton[0] * 255.f), int(g_Vars->Colors.Skeleton[1] * 255.f), int(g_Vars->Colors.Skeleton[2] * 255.f)), g_Vars->Visuals.SkeletonSize);
				}
			}
		}
	}
}