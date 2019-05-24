#include "Main.h"

static CreateClientClassFn GetWearableCreateFn()
{
	auto clazz = I::Client->GetAllClasses();

	while (strcmp(clazz->m_pNetworkName, "CEconWearable"))
		clazz = clazz->m_pNext;

	return clazz->m_pCreateFn;
}

void* CL_CreateDLLEntity(int iEnt, int iClass, int iSerialNum)
{
	ClientClass* pClient = I::Client->GetAllClasses();
	if (!pClient)
		return false;

	while (pClient)
	{
		if (pClient->m_ClassID == iClass)
			return pClient->m_pCreateFn(iEnt, iSerialNum);
		pClient = pClient->m_pNext;
	}
	return false;
}

typedef unsigned long CBaseHandle1;

void pChanger::GloveChanger()
{
	if (g_Vars->Misc.Glove == 0)
		return;

	auto local_id = I::Engine->GetLocalPlayer();
	if (!local_id) return;

	PlayerInfo_t localPlayerInfo;
	if (!I::Engine->GetPlayerInfo(local_id, &localPlayerInfo)) return;

	C_BaseEntity* local = (C_BaseEntity*)I::EntityList->GetClientEntity(local_id);
	if (!local) return;

	auto wearables = local->GetWearables();
	if (!wearables) return;

	static CBaseHandle1 glove_handle = 0;
	auto glove = reinterpret_cast<C_BaseCombatWeapon*>(I::EntityList->GetClientEntityFromHandle(wearables[0]));

	if (!glove)
	{
		auto our_glove = reinterpret_cast<C_BaseCombatWeapon*>(I::EntityList->GetClientEntityFromHandle(glove_handle));

		if (our_glove) // Our glove still exists
		{
			wearables[0] = glove_handle;
			glove = our_glove;
		}
	}

	if (!local->GetAlive())
	{
		if (glove)
		{
			glove->SetDestroyedOnRecreateEntities();
			glove->Release();
		}
		return;
	}

	if (!glove)
	{
		int iEnt = I::EntityList->GetHighestEntityIndex() + 1;
		int iSerialNumber = RandomInt(0x0, 0xFFF);

		C_BaseCombatWeapon* pWeapon = (C_BaseCombatWeapon*)CL_CreateDLLEntity(iEnt, CEconWearable, iSerialNumber);
		if (pWeapon)
		{
			auto m_Index = iEnt | (iSerialNumber << 16);
			glove_handle = m_Index;
			*(DWORD*)((DWORD)local + g_pNetvars->GetOffset("DT_BaseCombatCharacter", "m_hMyWearables")) = m_Index;
			glove = (C_BaseCombatWeapon*)I::EntityList->GetClientEntity(iEnt);
		}
	}

	*reinterpret_cast<int*>(uintptr_t(glove) + 0x64) = -1;


	if (glove)
	{
		PlayerInfo_t localplayer_info;
		I::Engine->GetPlayerInfo(I::Engine->GetLocalPlayer(), &localplayer_info);
		glove->GetItemDefinitionIndexB() = GetItemDefIndex_glove();
		glove->iItemIDHigh() = -1;
		glove->m_iEntityQuality() = 4;
		glove->iAccountID() = localplayer_info.xuidLow;
		glove->GetFallbackWear() = 0.00000001f;
		glove->GetFallbackSeed() = 0;
		glove->FallbackStatTrak() = -1;
		glove->FallbackPaintKit() = GetSkin_glove(g_Vars->Misc.Glove, g_Vars->Misc.GloveSkin);
		glove->SetModelIndex(GetModelIndex_glove());
		glove->PreDataUpdate(0);
	}
}

int pChanger::GetItemDefIndex_glove()
{
	switch (g_Vars->Misc.Glove)
	{
	case 1:
		return 5027;
	case 2:
		return 5030;
	case 3:
		return 5031;
	case 4:
		return 5032;
	case 5:
		return 5033;
	case 6:
		return 5034;
	case 7:
		return 5035;
	}

	return 0;
}

int pChanger::GetModelIndex_glove()
{
	switch (g_Vars->Misc.Glove)
	{
	case 1:
		return I::ModelInfo->GetModelIndex(charenc("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
	case 2:
		return I::ModelInfo->GetModelIndex(charenc("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
	case 3:
		return I::ModelInfo->GetModelIndex(charenc("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
	case 4:
		return I::ModelInfo->GetModelIndex(charenc("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
	case 5:
		return I::ModelInfo->GetModelIndex(charenc("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
	case 6:
		return I::ModelInfo->GetModelIndex(charenc("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
	case 7:
		return I::ModelInfo->GetModelIndex(charenc("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl"));
	}

	return 0;
}

int pChanger::GetSkin_glove(int gloveIndex, int skinIndex)
{
	if (gloveIndex == 1) // bloudhound
	{
		switch (skinIndex)
		{
		case 0:
			return 10006; //Charred
		case 1:
			return 10007; //Snakebite
		case 2:
			return 10008; //Bronzed
		case 3:
			return 10039; //Guerrilla
		default:
			return 0;
		}
	}
	else if (gloveIndex == 2) // Sport
	{
		switch (skinIndex)
		{
		case 0:
			return 10038; //Hedge Maze
		case 1:
			return 10037; //Pandora's Box
		case 2:
			return 10018; //Supercondutor
		case 3:
			return 10019; //Arid
		case 4:
			return 10048; //Vice
		case 5:
			return 10047; //Omega
		case 6:
			return 10045; //Amphibious
		case 7:
			return 10046; //Bronze Morph
		default:
			return 0;
		}
	}
	else if (gloveIndex == 3) // Driver
	{
		switch (skinIndex)
		{
		case 0:
			return 10013; //Lunar Weave
		case 1:
			return 10015; //Convoy
		case 2:
			return 10016; //Crimson Weave
		case 3:
			return 10040; //Diamond Back
		case 4:
			return 10043; //Overtake
		case 5:
			return 10044; //Racing Green
		case 6:
			return 10041; //King Snake
		case 7:
			return 10042; //Imperial Plaid
		default:
			return 0;
		}
	}
	else if (gloveIndex == 4) // Wraps
	{
		switch (skinIndex)
		{
		case 0:
			return 10009; //Leather
		case 1:
			return 10010; //Spruce DDPAT
		case 2:
			return 10021; //Slaughter
		case 3:
			return 10036; //Badlands
		case 4:
			return 10053; //Cobalt Skulls
		case 5:
			return 10054; //Overprint
		case 6:
			return 10055; //Duct Tape
		case 7:
			return 10056; //Arboreal
		default:
			return 0;
		}
	}
	else if (gloveIndex == 5) // Moto
	{
		switch (skinIndex)
		{
		case 0:
			return 10024; //Eclipse
		case 1:
			return 10026; //Spearmint
		case 2:
			return 10027; //BOOM!
		case 3:
			return 10028; //Cool Mint
		case 4:
			return 10050; //Turtle
		case 5:
			return 10051; //Transport
		case 6:
			return 10052; //Polygon
		case 7:
			return 10049; //POW!
		default:
			return 0;
		}
	}
	else if (gloveIndex == 6) // Specialist
	{
		switch (skinIndex)
		{
		case 0:
			return 10030; //Forest DDPAT
		case 1:
			return 10033; //Crimson Komono
		case 2:
			return 10034; //Emerald Web
		case 3:
			return 10035; //Foundation
		case 4:
			return 10061; //Crimson Web
		case 5:
			return 10062; //Buckshot
		case 6:
			return 10063; //Fade
		case 7:
			return 10064; //Mogul
		default:
			return 0;
		}
	}
	else if (gloveIndex == 7) //hydra
	{
		switch (skinIndex)
		{
		case 0:
			return 10060; //Hardened
		case 1:
			return 10059; //Rattler
		case 2:
			return 10058; //Mangrove
		case 3:
			return 10057; //Emerald
		default:
			return 0;
		}
	}

	return 0;
}