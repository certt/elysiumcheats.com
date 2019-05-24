#pragma once

#include "IClientNetworkable.h"
#include "IClientRenderable.h"
#include "IClientUnknown.h"
#include "IClientThinkable.h"

class C_BaseCombatWeapon;
class C_BaseEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
private:
	template<class T>
	T GetValue(const int offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
	}
	template< typename T >
	T GetVFunc(void* vTable, int iIndex)
	{
		return (*(T**)vTable)[iIndex];
	}
public:

	bool GetLifeState()
	{
		static int m_lifeState = g_pNetvars->GetOffset("DT_BasePlayer", "m_lifeState");
		return GetValue<bool>(m_lifeState) == 0;
	}

	int GetMoveType() 
	{
		static int m_MoveType = g_pNetvars->GetOffset("DT_BaseEntity", "m_MoveType");
		return GetValue<int>(m_MoveType);
	}

	int* GetWeapons()
	{
		return (int*)((DWORD)this + 0x2DF8);
	}

	int* GetWearables()
	{
		static const int m_hMyWearables = g_pNetvars->GetOffset("DT_BaseCombatCharacter", "m_hMyWearables");
		return (int*)((uintptr_t)this + m_hMyWearables);
	}

	bool IsHostage()
	{
		if (this->GetClientClass()->m_ClassID == CHostage)
			return true;

		return false;
	}

	bool IsScoped()
	{
		static int m_bIsScoped = g_pNetvars->GetOffset("DT_CSPlayer", "m_bIsScoped");
		return GetValue<bool>(m_bIsScoped);
	}

	int GetTeam()
	{
		static int m_iTeamNum = g_pNetvars->GetOffset("DT_BaseEntity", "m_iTeamNum");
		return GetValue<int>(m_iTeamNum);
	}

	int GetArmor()
	{
		static int m_ArmorValue = g_pNetvars->GetOffset("DT_CSPlayer", "m_ArmorValue");
		return GetValue<int>(m_ArmorValue);
	}

	int GetHealth()
	{
		static int m_iHealth = g_pNetvars->GetOffset("DT_BasePlayer", "m_iHealth");
		return GetValue<int>(m_iHealth);
	}

	int iShotsFired()
	{
		static int m_iShotsFired = g_pNetvars->GetOffset("DT_CSPlayer", "m_iShotsFired");
		return GetValue<int>(m_iShotsFired);
	}

	bool IsValid()
	{
		if (!this)
			return false;

		if (this->GetHealth() < 1)
			return false;

		if (this->GetLifeState() == false)
			return false;

		if (this->IsDormant())
			return false;

		return true;
	}

	bool IsVisible(int bone)
	{
		if (!this)
			return false;

		if (bone < 0)
			return false;

		C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
		
		if (!LocalPlayer)
			return false;

		Vector e_vecHead = this->GetBonePosition(bone);
		Vector p_vecHead = LocalPlayer->GetEyePosition();

		Ray_t ray;
		trace_t tr;
		ray.Init(p_vecHead, e_vecHead);
		CTraceFilter traceFilter;
		traceFilter.pSkip = LocalPlayer;
		I::EngineTrace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);

		return (tr.m_pEnt == this || tr.IsVisible());
	}

	int GetHitboxSet()
	{
		static int m_nHitboxSet = g_pNetvars->GetOffset("DT_BasePlayer", "m_nHitboxSet");
		return GetValue<int>(m_nHitboxSet);
	}

	bool IsDefusing()
	{
		static int m_bIsDefusing = g_pNetvars->GetOffset("DT_CSPlayer", "m_bIsDefusing");
		return GetValue<bool>(m_bIsDefusing);
	}

	float GetFlashDuration() {
		static int m_flFlashDuration = g_pNetvars->GetOffset("DT_CSPlayer", "m_flFlashDuration");
		return GetValue<float>(m_flFlashDuration);
	}

	bool IsFlashed()
	{
		return GetFlashDuration() > 0;
	}

	Vector GetOrigin()
	{
		static int m_vecOrigin = g_pNetvars->GetOffset("DT_BaseEntity", "m_vecOrigin");
		return GetValue<Vector>(m_vecOrigin);
	}

	Vector GetVelocity()
	{
		static int m_vecVelocity = g_pNetvars->GetOffset("DT_CSPlayer", "m_vecVelocity[0]");
		return GetValue<Vector>(m_vecVelocity);
	}

	QAngle GetPunch()
	{
		static int m_vecOrigin = g_pNetvars->GetOffset("DT_BasePlayer", "m_aimPunchAngle");
		return GetValue<QAngle>(m_vecOrigin);
	}

	Vector GetViewOffset()
	{
		static int m_vecViewOffset = g_pNetvars->GetOffset("DT_CSPlayer", "m_vecViewOffset[0]");
		return GetValue<Vector>(m_vecViewOffset);
	}

	EntityFlags GetFlags()
	{
		static int m_fFlags = g_pNetvars->GetOffset("DT_BasePlayer", "m_fFlags");
		return GetValue<EntityFlags>(m_fFlags);
	}

	C_BaseCombatWeapon* GetActiveWeapon()
	{
		static int m_hActiveWeapon = g_pNetvars->GetOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
		const auto weaponData = GetValue<CBaseHandle>(m_hActiveWeapon);
		return reinterpret_cast<C_BaseCombatWeapon*>(I::EntityList->GetClientEntityFromHandle(weaponData));
	}

	bool GetAlive()
	{
		if (this->GetHealth() <= 0)
			return false;
		if (this->GetLifeState() == false)
			return false;

		return true;
	}

	float GetC4BlowTime()
	{
		static int m_flC4Blow = g_pNetvars->GetOffset("DT_PlantedC4", "m_flC4Blow");
		return GetValue<float>(m_flC4Blow);
	}

	int GetTickBase()
	{
		static int m_nTickBase = g_pNetvars->GetOffset("DT_BasePlayer", "m_nTickBase");
		return GetValue<int>(m_nTickBase);
	}

	float GetC4DefuseCountDown()
	{
		static int m_flDefuseCountDown = g_pNetvars->GetOffset("DT_PlantedC4", "m_flDefuseCountDown");
		return GetValue<float>(m_flDefuseCountDown);
	}

	int GetBombDefuser()
	{
		static int m_hBombDefuser = g_pNetvars->GetOffset("DT_PlantedC4", "m_hBombDefuser");
		return GetValue<int>(m_hBombDefuser);
	}

	bool IsBombDefused()
	{
		static int m_bBombDefused = g_pNetvars->GetOffset("DT_PlantedC4", "m_bBombDefused");
		return GetValue<bool>(m_bBombDefused);
	}

	bool GetImmune()
	{
		static int m_bGunGameImmunity = g_pNetvars->GetOffset("DT_CSPlayer", "m_bGunGameImmunity");
		return GetValue<bool>(m_bGunGameImmunity);
	}

	void SetModelIndex(int index)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int);
		return GetVFunc<OriginalFn>(this, 75)(this, index);
	}

	DWORD GetObserverTargetHandle()
	{
		static int m_hObserverTarget = g_pNetvars->GetOffset("DT_BasePlayer", "m_hObserverTarget");
		return *(DWORD*)((DWORD)this + m_hObserverTarget);
	}

	Vector GetBonePosition(int iBone)
	{
		if(!this)
			return Vector(0, 0, 0);

		matrix3x4_t boneMatrixes[128];
		if (this->SetupBones(boneMatrixes, 128, 0x100, 0))
		{
			matrix3x4_t boneMatrix = boneMatrixes[iBone];
			return Vector(boneMatrix.flMatVal[0][3], boneMatrix.flMatVal[1][3], boneMatrix.flMatVal[2][3]);
		}
		return Vector(0, 0, 0);
	}

	Vector GetEyePosition()
	{
		Vector origin = this->GetOrigin();
		Vector offset = this->GetViewOffset();
		return(origin + offset);
	}

	float& GetSimulationTime()
	{
		static int m_flSimulationTime = g_pNetvars->GetOffset("DT_BaseEntity", "m_flSimulationTime");
		return *(float*)((DWORD)this + m_flSimulationTime);
	}

	IClientRenderable* GetClientRenderable()
	{
		return (IClientRenderable*)((DWORD)this + 0x4);
	}

	ClientClass* GetClientClass()
	{
		PVOID pNetworkable = (PVOID)((DWORD)(this) + 0x8);
		typedef ClientClass*(__thiscall* OriginalFn)(PVOID);
		return g_Utils->get_vfunc<OriginalFn>(pNetworkable, 2)(pNetworkable);
	}
};


class C_BaseCombatWeapon : public C_BaseEntity
{
private:
	template<class T>
	T GetValue(const int offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
	}
public:

	short GetItemDefinitionIndex()
	{
		static int m_iItemDefinitionIndex = g_pNetvars->GetOffset("DT_WeaponCSBase", "m_iItemDefinitionIndex");
		return GetValue<short>(m_iItemDefinitionIndex);
	}

	void Release()
	{
		PVOID pNetworkable = (PVOID)((DWORD)(this) + 0x8);
		typedef void(__thiscall* OriginalFn)(PVOID);
		return g_Utils->get_vfunc<OriginalFn>(pNetworkable, 1)(pNetworkable);
	}

	void SetDestroyedOnRecreateEntities(void)
	{
		PVOID pNetworkable = (PVOID)((DWORD)(this) + 0x8);
		typedef void(__thiscall* OriginalFn)(PVOID);
		return g_Utils->get_vfunc<OriginalFn>(pNetworkable, 13)(pNetworkable);
	}

	int GetClip1()
	{
		static int m_iClip1 = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_iClip1");
		return GetValue<int>(m_iClip1);
	}

	int GetClip2()
	{
		static int m_iClip2 = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount");
		return GetValue<int>(m_iClip2);
	}

	int& FallbackPaintKit()
	{
		static int m_nFallbackPaintKit = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_nFallbackPaintKit");
		return *(int*)((DWORD)this + m_nFallbackPaintKit);
	}

	int& FallbackStatTrak()
	{
		static int m_nFallbackStatTrak = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_nFallbackStatTrak");
		return *(int*)((DWORD)this + m_nFallbackStatTrak);
	}

	int& GetFallbackSeed()
	{
		static int m_nFallbackSeed = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_nFallbackSeed");
		return *(int*)((DWORD)this + m_nFallbackSeed);
	}

	float& GetFallbackWear()
	{
		static int m_flFallbackWear = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_flFallbackWear");
		return *(float*)((DWORD)this + m_flFallbackWear);
	}

	int& GetModelIndex()
	{
		static int m_nModelIndex = g_pNetvars->GetOffset("DT_BasePlayer", "m_nModelIndex");
		return *(int*)((DWORD)this + m_nModelIndex);
	}

	int& iAccountID()
	{
		static int m_iAccountID = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_iAccountID");
		return *(int*)((DWORD)this + m_iAccountID);
	}

	int& m_iEntityQuality()
	{
		static int m_iEntityQuality = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_iEntityQuality");
		return *(int*)((DWORD)this + m_iEntityQuality);
	}

	int& iItemIDHigh()
	{
		static int m_iItemIDHigh = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_iItemIDHigh");
		return *(int*)((DWORD)this + m_iItemIDHigh);
	}

	float GetInaccuracyReal() {
		return g_Utils->get_vfunc<float(__thiscall*)(void*)>(this, 471)(this);
	}

	int& GetItemDefinitionIndexB()
	{
		static int m_iItemDefinitionIndex = g_pNetvars->GetOffset("DT_WeaponCSBase", "m_iItemDefinitionIndex");
		return *(int*)((DWORD)this + m_iItemDefinitionIndex);
	}

	HANDLE m_hWeaponWorldModel()
	{
		static int m_hWeaponWorldModel = g_pNetvars->GetOffset("DT_BaseCombatWeapon", "m_hWeaponWorldModel");
		return *(HANDLE*)((uintptr_t)this + m_hWeaponWorldModel);
	}

	IClientNetworkable* GetNetworkable()
	{
		return (IClientNetworkable*)((DWORD)this + 0x8);
	}

	std::string GetWeaponName()
	{
		if (!this)
			return "";

		int id = (int)this->GetItemDefinitionIndex();

		switch (id)
		{
		case WEAPON_DEAGLE:
			return strenc("Deagle");
		case WEAPON_ELITE:
			return strenc("Berettas");
		case WEAPON_FIVESEVEN:
			return strenc("Five-SeveN");
		case WEAPON_GLOCK:
			return strenc("Glock-18");
		case WEAPON_AK47:
			return strenc("AK-47");
		case WEAPON_AUG:
			return strenc("AUG");
		case WEAPON_AWP:
			return strenc("AWP");
		case WEAPON_FAMAS:
			return strenc("FAMAS");
		case WEAPON_G3SG1:
			return strenc("G3SG1");
		case WEAPON_GALILAR:
			return strenc("Galil");
		case WEAPON_M249:
			return strenc("M249");
		case WEAPON_M4A1:
			return strenc("M4A1");
		case WEAPON_MAC10:
			return strenc("MAC-10");
		case WEAPON_P90:
			return strenc("P90");
		case WEAPON_UMP45:
			return strenc("UMP-45");
		case WEAPON_XM1014:
			return strenc("XM1014");
		case WEAPON_BIZON:
			return strenc("PP-Bizon");
		case WEAPON_MAG7:
			return strenc("MAG-7");
		case WEAPON_NEGEV:
			return strenc("Negev");
		case WEAPON_SAWEDOFF:
			return strenc("Sawed-Off");
		case WEAPON_TEC9:
			return strenc("Tec-9");
		case WEAPON_TASER:
			return strenc("Taser");
		case WEAPON_HKP2000:
			return strenc("P2000");
		case WEAPON_MP7:
			return strenc("MP7");
		case WEAPON_MP9:
			return strenc("MP9");
		case WEAPON_NOVA:
			return strenc("Nova");
		case WEAPON_P250:
			return strenc("P250");
		case WEAPON_SCAR20:
			return strenc("SCAR-20");
		case WEAPON_SG556:
			return strenc("SG 553");
		case WEAPON_SSG08:
			return strenc("SSG 08");
		case WEAPON_KNIFE:
			return strenc("Knife");
		case WEAPON_FLASHBANG:
			return strenc("Flashbang");
		case WEAPON_HEGRENADE:
			return strenc("HE");
		case WEAPON_SMOKEGRENADE:
			return strenc("Smoke");
		case WEAPON_MOLOTOV:
			return strenc("Molotov");
		case WEAPON_DECOY:
			return strenc("Decoy");
		case WEAPON_INCGRENADE:
			return strenc("Incendiary");
		case WEAPON_C4:
			return strenc("C4");
		case WEAPON_KNIFE_T:
			return strenc("Knife");
		case WEAPON_M4A1_SILENCER:
			return strenc("M4A1-S");
		case WEAPON_USP_SILENCER:
			return strenc("USP-S");
		case WEAPON_CZ75A:
			return strenc("CZ75-Auto");
		case WEAPON_REVOLVER:
			return strenc("R8 Revolver");
		case 23:
			return strenc("MP5-SD");
		default:
			return strenc("Knife");
		}

		return "";
	}

	bool IsKnife()
	{
		if (!this)
			return false;

		switch (this->GetItemDefinitionIndex())
		{
		case WEAPON_KNIFE:
		case WEAPON_KNIFE_T:
		case WEAPON_KNIFE_GUT:
		case WEAPON_KNIFE_FLIP:
		case WEAPON_BAYONET:
		case WEAPON_KNIFE_M9_BAYONET:
		case WEAPON_KNIFE_KARAMBIT:
		case WEAPON_KNIFE_TACTICAL:
		case WEAPON_KNIFE_BUTTERFLY:
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
		case WEAPON_KNIFE_FALCHION:
		case WEAPON_KNIFE_PUSH:
		case 520:
		case 519:
		case 522:
		case 523:
			return true;
		default:
			return false;
		}
	}

	std::string GetWeaponNameIcon()
	{
		if (!this)
			return "";

		int id = this->GetItemDefinitionIndex();

		switch (id)
		{
		case WEAPON_DEAGLE:
			return "A";
		case WEAPON_ELITE:
			return "B";
		case WEAPON_FIVESEVEN:
			return "C";
		case WEAPON_GLOCK:
			return "D";
		case WEAPON_AK47:
			return "W";
		case WEAPON_AUG:
			return "U";
		case WEAPON_AWP:
			return "Z";
		case WEAPON_FAMAS:
			return "R";
		case WEAPON_G3SG1:
			return "X";
		case WEAPON_GALILAR:
			return "Q";
		case WEAPON_M249:
			return "g";
		case WEAPON_M4A1:
			return "S";
		case WEAPON_MAC10:
			return "K";
		case WEAPON_P90:
			return "P";
		case WEAPON_UMP45:
			return "L";
		case WEAPON_XM1014:
			return "b";
		case WEAPON_BIZON:
			return "M";
		case WEAPON_MAG7:
			return "d";
		case WEAPON_NEGEV:
			return "f";
		case WEAPON_SAWEDOFF:
			return "c";
		case WEAPON_TEC9:
			return "H";
		case WEAPON_TASER:
			return "h";
		case WEAPON_HKP2000:
			return "E";
		case WEAPON_MP7:
			return "N";
		case WEAPON_MP9:
			return "O";
		case WEAPON_NOVA:
			return "e";
		case WEAPON_P250:
			return "F";
		case WEAPON_SCAR20:
			return "Y";
		case WEAPON_SG556:
			return "V";
		case WEAPON_SSG08:
			return "a";
		case WEAPON_KNIFE:
			return "]";
		case WEAPON_BAYONET:
			return "1";
		case WEAPON_KNIFE_BUTTERFLY:
			return "8";
		case WEAPON_KNIFE_FALCHION:
			return "0";
		case WEAPON_KNIFE_FLIP:
			return "2";
		case WEAPON_KNIFE_GUT:
			return "3";
		case WEAPON_KNIFE_KARAMBIT:
			return "4";
		case WEAPON_KNIFE_M9_BAYONET:
			return "5";
		case WEAPON_KNIFE_PUSH:
			return "9";
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return "7";
		case WEAPON_KNIFE_T:
			return "[";
		case WEAPON_KNIFE_TACTICAL:
			return "6";
		case WEAPON_FLASHBANG:
			return "i";
		case WEAPON_HEGRENADE:
			return "j";
		case WEAPON_SMOKEGRENADE:
			return "k";
		case WEAPON_MOLOTOV:
			return "l";
		case WEAPON_DECOY:
			return "m";
		case WEAPON_INCGRENADE:
			return "n";
		case WEAPON_C4:
			return "o";
		case WEAPON_M4A1_SILENCER:
			return "T";
		case WEAPON_USP_SILENCER:
			return "G";
		case WEAPON_CZ75A:
			return "I";
		case WEAPON_REVOLVER:
			return "J";
		default:
			return "]";
		}

		return "";
	}

	bool IsSniper()
	{
		if (!this)
			return false;

		switch (this->GetItemDefinitionIndex())
		{
		case WEAPON_DEAGLE:
		case WEAPON_ELITE:
		case WEAPON_FIVESEVEN:
		case WEAPON_GLOCK:
		case WEAPON_AK47:
		case WEAPON_AUG:
			return false;
		case WEAPON_AWP:
			return true;
		case WEAPON_FAMAS:
			return false;
		case WEAPON_G3SG1:
			return true;
		case WEAPON_GALILAR:
		case WEAPON_M249:
		case WEAPON_M4A1:
		case WEAPON_MAC10:
		case WEAPON_P90:
		case WEAPON_UMP45:
		case WEAPON_XM1014:
		case WEAPON_BIZON:
		case WEAPON_MAG7:
		case WEAPON_NEGEV:
		case WEAPON_SAWEDOFF:
		case WEAPON_TEC9:
		case WEAPON_TASER:
		case WEAPON_HKP2000:
		case WEAPON_MP7:
		case WEAPON_MP9:
		case WEAPON_NOVA:
		case WEAPON_P250:
			return false;
		case WEAPON_SCAR20:
			return true;
		case WEAPON_SG556:
			return false;
		case WEAPON_SSG08:
			return true;
		case WEAPON_KNIFE:
		case WEAPON_FLASHBANG:
		case WEAPON_HEGRENADE:
		case WEAPON_SMOKEGRENADE:
		case WEAPON_MOLOTOV:
		case WEAPON_DECOY:
		case WEAPON_INCGRENADE:
		case WEAPON_C4:
		case WEAPON_KNIFE_T:
		case WEAPON_M4A1_SILENCER:
		case WEAPON_USP_SILENCER:
		case WEAPON_CZ75A:
		case WEAPON_REVOLVER:
			return false;
		default:
			return false;
		}
	}

	bool IsRifle()
	{
		if (!this)
			return false;

		switch (this->GetItemDefinitionIndex())
		{
		case WEAPON_DEAGLE:
		case WEAPON_ELITE:
		case WEAPON_FIVESEVEN:
		case WEAPON_GLOCK:
			return false;
		case WEAPON_AK47:
		case WEAPON_AUG:
			return true;
		case WEAPON_AWP:
			return false;
		case WEAPON_FAMAS:
			return true;
		case WEAPON_G3SG1:
			return false;
		case WEAPON_GALILAR:
		case WEAPON_M249:
		case WEAPON_M4A1:
			return true;
		case WEAPON_MAC10:
		case WEAPON_P90:
		case WEAPON_UMP45:
		case WEAPON_XM1014:
		case WEAPON_BIZON:
		case WEAPON_MAG7:
			return false;
		case WEAPON_NEGEV:
			return true;
		case WEAPON_SAWEDOFF:
			return false;
		case WEAPON_TEC9:
		case WEAPON_TASER:
		case WEAPON_HKP2000:
		case WEAPON_MP7:
		case WEAPON_MP9:
		case WEAPON_NOVA:
		case WEAPON_P250:
		case WEAPON_SCAR20:
			return false;
		case WEAPON_SG556:
			return true;
		case WEAPON_SSG08:
		case WEAPON_KNIFE:
		case WEAPON_FLASHBANG:
		case WEAPON_HEGRENADE:
		case WEAPON_SMOKEGRENADE:
		case WEAPON_MOLOTOV:
		case WEAPON_DECOY:
		case WEAPON_INCGRENADE:
		case WEAPON_C4:
		case WEAPON_KNIFE_T:
			return false;
		case WEAPON_M4A1_SILENCER:
			return true;
		case WEAPON_USP_SILENCER:
		case WEAPON_CZ75A:
		case WEAPON_REVOLVER:
			return false;
		default:
			return false;
		}
	}

	bool IsSMG()
	{
		if (!this)
			return false;

		switch (this->GetItemDefinitionIndex())
		{
		case WEAPON_DEAGLE:
		case WEAPON_ELITE:
		case WEAPON_FIVESEVEN:
		case WEAPON_GLOCK:
		case WEAPON_AK47:
		case WEAPON_AUG:
		case WEAPON_AWP:
		case WEAPON_FAMAS:
		case WEAPON_G3SG1:
		case WEAPON_GALILAR:
		case WEAPON_M249:
		case WEAPON_M4A1:
			return false;
		case WEAPON_MAC10:
		case WEAPON_P90:
		case WEAPON_UMP45:
			return true;
		case WEAPON_XM1014:
			return false;
		case WEAPON_BIZON:
			return true;
		case WEAPON_MAG7:
		case WEAPON_NEGEV:
		case WEAPON_SAWEDOFF:
		case WEAPON_TEC9:
		case WEAPON_TASER:
		case WEAPON_HKP2000:
			return false;
		case WEAPON_MP7:
		case WEAPON_MP9:
		case 23:
			return true;
		case WEAPON_NOVA:
		case WEAPON_P250:
		case WEAPON_SCAR20:
		case WEAPON_SG556:
		case WEAPON_SSG08:
		case WEAPON_KNIFE:
		case WEAPON_FLASHBANG:
		case WEAPON_HEGRENADE:
		case WEAPON_SMOKEGRENADE:
		case WEAPON_MOLOTOV:
		case WEAPON_DECOY:
		case WEAPON_INCGRENADE:
		case WEAPON_C4:
		case WEAPON_KNIFE_T:
		case WEAPON_M4A1_SILENCER:
		case WEAPON_USP_SILENCER:
		case WEAPON_CZ75A:
		case WEAPON_REVOLVER:
			return false;
		default:
			return false;
		}
	}

	bool IsShotgun()
	{
		if (!this)
			return false;

		switch (this->GetItemDefinitionIndex())
		{
		case WEAPON_DEAGLE:
		case WEAPON_ELITE:
		case WEAPON_FIVESEVEN:
		case WEAPON_GLOCK:
		case WEAPON_AK47:
		case WEAPON_AUG:
		case WEAPON_AWP:
		case WEAPON_FAMAS:
		case WEAPON_G3SG1:
		case WEAPON_GALILAR:
		case WEAPON_M249:
		case WEAPON_M4A1:
		case WEAPON_MAC10:
		case WEAPON_P90:
		case WEAPON_UMP45:
			return false;
		case WEAPON_XM1014:
			return true;
		case WEAPON_BIZON:
			return false;
		case WEAPON_MAG7:
			return true;
		case WEAPON_NEGEV:
			return false;
		case WEAPON_SAWEDOFF:
			return true;
		case WEAPON_TEC9:
		case WEAPON_TASER:
		case WEAPON_HKP2000:
		case WEAPON_MP7:
		case WEAPON_MP9:
			return false;
		case WEAPON_NOVA:
			return true;
		case WEAPON_P250:
		case WEAPON_SCAR20:
		case WEAPON_SG556:
		case WEAPON_SSG08:
		case WEAPON_KNIFE:
		case WEAPON_FLASHBANG:
		case WEAPON_HEGRENADE:
		case WEAPON_SMOKEGRENADE:
		case WEAPON_MOLOTOV:
		case WEAPON_DECOY:
		case WEAPON_INCGRENADE:
		case WEAPON_C4:
		case WEAPON_KNIFE_T:
		case WEAPON_M4A1_SILENCER:
		case WEAPON_USP_SILENCER:
		case WEAPON_CZ75A:
		case WEAPON_REVOLVER:
			return false;
		default:
			return false;
		}
	}

	bool IsGrenade()
	{
		if (!this)
			return false;

		switch (this->GetItemDefinitionIndex())
		{
		case WEAPON_SMOKEGRENADE:
		case WEAPON_HEGRENADE:
		case WEAPON_INCGRENADE:
		case WEAPON_FLASHBANG:
		case WEAPON_MOLOTOV:
		case WEAPON_DECOY:
			return true;
		default:
			return false;
		}
	}

	bool IsPistol()
	{
		if (!this)
			return false;

		switch (this->GetItemDefinitionIndex())
		{
		case WEAPON_DEAGLE:
		case WEAPON_ELITE:
		case WEAPON_FIVESEVEN:
		case WEAPON_GLOCK:
			return true;
		case WEAPON_AK47:
		case WEAPON_AUG:
		case WEAPON_AWP:
		case WEAPON_FAMAS:
		case WEAPON_G3SG1:
		case WEAPON_GALILAR:
		case WEAPON_M249:
		case WEAPON_M4A1:
		case WEAPON_MAC10:
		case WEAPON_P90:
		case WEAPON_UMP45:
		case WEAPON_XM1014:
		case WEAPON_BIZON:
		case WEAPON_MAG7:
		case WEAPON_NEGEV:
		case WEAPON_SAWEDOFF:
			return false;
		case WEAPON_TEC9:
		case WEAPON_TASER:
		case WEAPON_HKP2000:
			return true;
		case WEAPON_MP7:
		case WEAPON_MP9:
		case WEAPON_NOVA:
			return false;
		case WEAPON_P250:
			return true;
		case WEAPON_SCAR20:
		case WEAPON_SG556:
		case WEAPON_SSG08:
		case WEAPON_KNIFE:
		case WEAPON_FLASHBANG:
		case WEAPON_HEGRENADE:
		case WEAPON_SMOKEGRENADE:
		case WEAPON_MOLOTOV:
		case WEAPON_DECOY:
		case WEAPON_INCGRENADE:
		case WEAPON_C4:
		case WEAPON_KNIFE_T:
		case WEAPON_M4A1_SILENCER:
			return false;
		case WEAPON_USP_SILENCER:
		case WEAPON_CZ75A:
		case WEAPON_REVOLVER:
			return true;
		default:
			return false;
		}
	}
};