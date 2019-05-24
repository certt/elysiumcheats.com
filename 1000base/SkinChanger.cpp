#include "Main.h"

void pChanger::SkinChanger()
{
	PlayerInfo_t localPlayerInfo; C_BaseEntity* LocalPlayer;
	LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());

	if (!LocalPlayer) return;
	if (!I::Engine->GetPlayerInfo(I::Engine->GetLocalPlayer(), &localPlayerInfo)) return;

	int* hweapons = LocalPlayer->GetWeapons();
	if (!hweapons) return;

	for (int i = 0; hweapons[i] != INVALID_EHANDLE_INDEX; i++)
	{
		C_BaseCombatWeapon* pWeapon = (C_BaseCombatWeapon*)I::EntityList->GetClientEntity(hweapons[i] & 0xFFF);
		if (!pWeapon) continue;

		if (g_Vars->Skinchanger.KnifeChanger)
		{
			if (pWeapon->GetItemDefinitionIndex() == 59 || pWeapon->GetItemDefinitionIndex() == 500 || pWeapon->GetItemDefinitionIndex() == 42 || pWeapon->GetItemDefinitionIndex() == 523
				|| pWeapon->GetItemDefinitionIndex() == 507 || pWeapon->GetItemDefinitionIndex() == 506 || pWeapon->GetItemDefinitionIndex() == 508
				|| pWeapon->GetItemDefinitionIndex() == 509 || pWeapon->GetItemDefinitionIndex() == 515 || pWeapon->GetItemDefinitionIndex() == 516
				|| pWeapon->GetItemDefinitionIndex() == 505 || pWeapon->GetItemDefinitionIndex() == 514 || pWeapon->GetItemDefinitionIndex() == 512
				|| pWeapon->GetItemDefinitionIndex() == 520 || pWeapon->GetItemDefinitionIndex() == 519 || pWeapon->GetItemDefinitionIndex() == 522)
			{			
				pWeapon->GetModelIndex() = GetModelIndex_knife();
				pWeapon->GetItemDefinitionIndexB() = GetItemDefIndex_knife();
				pWeapon->m_iEntityQuality() = 3;
				if (LocalPlayer->GetActiveWeapon()->IsKnife())
				{
					static int m_ViewModel = g_pNetvars->GetOffset("DT_BasePlayer", "m_hViewModel[0]");
					DWORD hViewModel = *(DWORD*)(DWORD(LocalPlayer) + m_ViewModel);
					C_BaseEntity* pViewModel = (C_BaseEntity*)I::EntityList->GetClientEntityFromHandle(hViewModel);

					if (pViewModel && pViewModel != NULL && pViewModel != nullptr)
						((C_BaseEntity*)pViewModel)->SetModelIndex(GetModelIndex_knife());
				}
			}
		}

		short WeaponID = pWeapon->GetItemDefinitionIndex();

		if (g_Vars->Skinchanger.W[WeaponID].ChangerEnabled)
		{
			if (g_Vars->Skinchanger.W[WeaponID].ChangerSkin != 0)
				pWeapon->FallbackPaintKit() = g_Vars->Skinchanger.W[WeaponID].ChangerSkin;

			if (!g_Vars->Skinchanger.W[WeaponID].LiveSC)
				if (g_Vars->Skinchanger.W[WeaponID].SC != 0)
					pWeapon->FallbackStatTrak() = g_Vars->Skinchanger.W[WeaponID].SC;

			if (g_Vars->Skinchanger.W[WeaponID].Wear == 0)
				pWeapon->GetFallbackWear() = 0.0001f;

			if (g_Vars->Skinchanger.W[WeaponID].Wear != 0)
				pWeapon->GetFallbackWear() = g_Vars->Skinchanger.W[WeaponID].Wear;

			if (g_Vars->Skinchanger.W[WeaponID].Seed != 0)
				pWeapon->GetFallbackSeed() = g_Vars->Skinchanger.W[WeaponID].Seed;
		}

		pWeapon->iAccountID() = localPlayerInfo.xuidLow;
		pWeapon->iItemIDHigh() = -1;
	}
}

int pChanger::GetItemDefIndex_knife()
{
	switch (g_Vars->Skinchanger.knifemodel)
	{
	case 0:
		return 500;
	case 1:
		return 505;
	case 2:
		return 506;
	case 3:
		return 507;
	case 4:
		return 508;
	case 5:
		return 509;
	case 6:
		return 512;
	case 7:
		return 514;
	case 8:
		return 515;
	case 9:
		return 516;
	case 10:
		return 520;
	case 11:
		return 522;
	case 12:
		return 519;
	case 13:
		return 523;
	}

	return 0;
}

int pChanger::GetModelIndex_knife()
{
	switch (g_Vars->Skinchanger.knifemodel)
	{
	case 0:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
	case 1:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_flip.mdl");
	case 2:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_gut.mdl");
	case 3:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
	case 4:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
	case 5:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_tactical.mdl");
	case 6:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_falchion_advanced.mdl");
	case 7:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_survival_bowie.mdl");
	case 8:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_butterfly.mdl");
	case 9:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_push.mdl");
	case 10:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_gypsy_jackknife.mdl");
	case 11:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_stiletto.mdl");
	case 12:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_ursus.mdl");
	case 13:
		return I::ModelInfo->GetModelIndex("models/weapons/v_knife_widowmaker.mdl");
	}

	return 0;
}