#include "Main.h"

FrameStageNotifyFn oFrameStageNotify;
void __stdcall Hooks::FrameStageNotify(ClientFrameStage_t stage)
{
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());

	if (!LocalPlayer)
		return oFrameStageNotify(stage);

	if (stage == FRAME_NET_UPDATE_START)
	{
		for (int i = 1; i <= 65; ++i)
		{
			C_BaseEntity* Entity = I::EntityList->GetClientEntity(i);

			if (!Entity)
				continue;

			if (LocalPlayer == Entity)
				continue;

			if (!Entity->IsValid())
				continue;

			studiohdr_t* pStudioModel = I::ModelInfo->GetStudioModel(Entity->GetModel());
			if (pStudioModel && pStudioModel != nullptr)
				Entity->SetupBones(&playerStruct[i].matrix[0], 128, 256, I::Globals->curtime);

			playerStruct[i].isvisible = Entity->IsVisible(0);
		}
	}

	if (stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		g_Changer->GloveChanger();
		g_Changer->SkinChanger();
	}

	oFrameStageNotify(stage);
}

#define SEQUENCE_DEFAULT_DRAW 0
#define SEQUENCE_DEFAULT_IDLE1 1
#define SEQUENCE_DEFAULT_IDLE2 2
#define SEQUENCE_DEFAULT_LIGHT_MISS1 3
#define SEQUENCE_DEFAULT_LIGHT_MISS2 4
#define SEQUENCE_DEFAULT_HEAVY_MISS1 9
#define SEQUENCE_DEFAULT_HEAVY_HIT1 10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB 11
#define SEQUENCE_DEFAULT_LOOKAT01 12

#define SEQUENCE_BUTTERFLY_DRAW 0
#define SEQUENCE_BUTTERFLY_DRAW2 1
#define SEQUENCE_BUTTERFLY_LOOKAT01 13
#define SEQUENCE_BUTTERFLY_LOOKAT03 15

#define SEQUENCE_FALCHION_IDLE1 1
#define SEQUENCE_FALCHION_HEAVY_MISS1 8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP 9
#define SEQUENCE_FALCHION_LOOKAT01 12
#define SEQUENCE_FALCHION_LOOKAT02 13

#define SEQUENCE_DAGGERS_IDLE1 1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 12

#define SEQUENCE_BOWIE_IDLE1 1

#define	LIFE_ALIVE 0

std::unique_ptr<RecvPropHook> sequenceHook;

RecvVarProxyFn oRecvProxySequence;
void RecvProxy_Sequence(CRecvProxyData* pDataConst, void* pStruct, void* pOut)
{
	static int lastSentSeq;
	CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);

	int iSequence = pData->m_Value.m_Int;

	C_BaseCombatWeapon* Weapon = static_cast<C_BaseCombatWeapon*>(pStruct);
	C_BaseEntity* pLocal = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());

	if (Weapon && Weapon->GetModelIndex() && pLocal)
	{
		std::string rWeapon = I::ModelInfo->GetModelName(Weapon->GetModel());

		if (rWeapon.find(XorString("v_knife_ursus.mdl")) != std::string::npos)
		{
			switch (iSequence)
			{
			case SEQUENCE_DEFAULT_DRAW:
				iSequence = RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
				break;
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence = RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
				break;
			default:
				iSequence++;
				break;
			}
		}
		else if (rWeapon.find(XorString("v_knife_stiletto.mdl")) != std::string::npos)
		{
			switch (iSequence)
			{
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence = RandomInt(12, 13);
				break;
			}
		}
		else if (rWeapon.find(XorString("v_knife_widowmaker.mdl")) != std::string::npos)
		{
			switch (iSequence)
			{
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence = RandomInt(14, 15);
				break;
			}
		}
		else if (rWeapon.find(XorString("v_knife_push.mdl")) != std::string::npos)
		{
			switch (iSequence) {
			case SEQUENCE_DEFAULT_IDLE2:
				iSequence = SEQUENCE_DAGGERS_IDLE1; break;
			case SEQUENCE_DEFAULT_LIGHT_MISS1:
			case SEQUENCE_DEFAULT_LIGHT_MISS2:
				iSequence = RandomInt(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5); break;
			case SEQUENCE_DEFAULT_HEAVY_MISS1:
				iSequence = RandomInt(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1); break;
			case SEQUENCE_DEFAULT_HEAVY_HIT1:
			case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence += 3; break;
			case SEQUENCE_DEFAULT_DRAW:
			case SEQUENCE_DEFAULT_IDLE1:
				break;
			default:
				iSequence += 2;
			}
		}
		else if (rWeapon.find(XorString("v_knife_falchion_advanced.mdl")) != std::string::npos)
		{
			switch (iSequence) {
			case SEQUENCE_DEFAULT_IDLE2:
				iSequence = SEQUENCE_FALCHION_IDLE1; break;
			case SEQUENCE_DEFAULT_HEAVY_MISS1:
				iSequence = RandomInt(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP); break;
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence = RandomInt(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02); break;
			case SEQUENCE_DEFAULT_DRAW:
			case SEQUENCE_DEFAULT_IDLE1:
				break;
			default:
				iSequence--;
			}
		}
		else if (rWeapon.find(XorString("v_knife_butterfly.mdl")) != std::string::npos)
		{
			switch (iSequence) {
			case SEQUENCE_DEFAULT_DRAW:
				iSequence = RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2); break;
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence = RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03); break;
			default:
				iSequence++;
			}
		}
		else if (rWeapon.find(XorString("v_knife_survival_bowie.mdl")) != std::string::npos)
		{
			switch (iSequence) {
			case SEQUENCE_DEFAULT_DRAW:
			case SEQUENCE_DEFAULT_IDLE1:
				break;
			case SEQUENCE_DEFAULT_IDLE2:
				iSequence = SEQUENCE_BOWIE_IDLE1; break;
			default:
				iSequence--;
			}
		}
		pData->m_Value.m_Int = iSequence;
	}

	if (!oRecvProxySequence)
		oRecvProxySequence = sequenceHook->GetOriginalFunction();

	oRecvProxySequence(pData, pStruct, pOut);
}

void Hooks::AnimationFixHook()
{
	ClientClass *pClass = I::Client->GetAllClasses();
	while (pClass)
	{
		const char *pszName = pClass->m_pRecvTable->m_pNetTableName;
		if (!strcmp(pszName, "DT_BaseViewModel"))
		{
			for (int i = 0; i < pClass->m_pRecvTable->m_nProps; i++)
			{
				RecvProp *pProp = &(pClass->m_pRecvTable->m_pProps[i]);
				const char *name = pProp->m_pVarName;
				if (!strcmp(name, "m_nSequence"))
				{
					oRecvProxySequence = (RecvVarProxyFn)pProp->m_ProxyFn;
					pProp->m_ProxyFn = RecvProxy_Sequence;
				}
			}
		}
		pClass = pClass->m_pNext;
	}
}