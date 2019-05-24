#include "Main.h"

namespace ChamsStuff
{
	IMaterial* chams_mat;
	IMaterial* chams_mat_ignorez;
	IMaterial* chams_mat_flat;
	IMaterial* chams_mat_ignorez_flat;
	IMaterial* chams_mat_classic;
	IMaterial* chams_mat_ignorez_classic;
	
	bool init = false;
}

void setup() {

	std::ofstream("csgo\\materials\\regular_reflective.vmt") << R"#("VertexLitGeneric" {
      "$basetexture" "vgui/white_additive"
      "$ignorez" "0"
      "$envmap" "env_cubemap"
      "$normalmapalphaenvmapmask" "1"
      "$envmapcontrast"  "1"
      "$nofog" "1"
      "$model" "1"
      "$nocull" "0"
      "$selfillum" "1"
      "$halflambert" "1"
      "$znearer" "0"
      "$flat" "1"  }
        )#";

	std::ofstream("csgo\\materials\\regular_reflective_ignorez.vmt") << R"#("VertexLitGeneric" {
      "$basetexture" "vgui/white_additive"
      "$ignorez" "1"
      "$envmap" "env_cubemap"
      "$normalmapalphaenvmapmask" "1"
      "$envmapcontrast"  "1"
      "$nofog" "1"
      "$model" "1"
      "$nocull" "0"
      "$selfillum" "1"
      "$halflambert" "1"
      "$znearer" "0"
      "$flat" "1"  }
        )#";

	std::ofstream("csgo\\materials\\regular_reflective_flat.vmt") << R"#("UnlitGeneric" {
      "$basetexture" "vgui/white_additive"
      "$ignorez" "0"
      "$envmap" ""
      "$normalmapalphaenvmapmask" "1"
      "$envmapcontrast"  "1"
      "$nofog" "1"
      "$model" "1"
      "$nocull" "0"
      "$selfillum" "1"
      "$halflambert" "1"
      "$znearer" "0"
      "$flat" "0"  }
        )#";

	std::ofstream("csgo\\materials\\regular_reflective_ignorez_flat.vmt") << R"#("UnlitGeneric" {
      "$basetexture" "vgui/white_additive"
      "$ignorez" "1"
      "$envmap" ""
      "$normalmapalphaenvmapmask" "1"
      "$envmapcontrast"  "1"
      "$nofog" "1"
      "$model" "1"
      "$nocull" "0"
      "$selfillum" "1"
      "$halflambert" "1"
      "$znearer" "0"
      "$flat" "0"  }
        )#";


	std::ofstream("csgo\\materials\\regular_reflective_classic.vmt") << R"#("VertexLitGeneric" {
      "$basetexture" "vgui/white_additive"
      "$ignorez" "0"
      "$envmap" ""
      "$normalmapalphaenvmapmask" "1"
      "$envmapcontrast"  "1"
      "$nofog" "1"
      "$model" "1"
      "$nocull" "0"
      "$selfillum" "1"
      "$halflambert" "1"
      "$znearer" "0"
      "$flat" "0"  }
        )#";

	std::ofstream("csgo\\materials\\regular_reflective_ignorez_classic.vmt") << R"#("VertexLitGeneric" {
      "$basetexture" "vgui/white_additive"
      "$ignorez" "1"
      "$envmap" ""
      "$normalmapalphaenvmapmask" "1"
      "$envmapcontrast"  "1"
      "$nofog" "1"
      "$model" "1"
      "$nocull" "0"
      "$selfillum" "1"
      "$halflambert" "1"
      "$znearer" "0"
      "$flat" "0"  }
        )#";

	ChamsStuff::chams_mat = I::MaterialSystem->FindMaterial("regular_reflective", "Model textures", true, NULL);
	ChamsStuff::chams_mat_ignorez = I::MaterialSystem->FindMaterial("regular_reflective_ignorez", "Model textures", true, NULL);

	ChamsStuff::chams_mat_flat = I::MaterialSystem->FindMaterial("regular_reflective_flat", "Model textures", true, NULL);
	ChamsStuff::chams_mat_ignorez_flat = I::MaterialSystem->FindMaterial("regular_reflective_ignorez_flat", "Model textures", true, NULL);

	ChamsStuff::chams_mat_classic = I::MaterialSystem->FindMaterial("regular_reflective_classic", "Model textures", true, NULL);
	ChamsStuff::chams_mat_ignorez_classic = I::MaterialSystem->FindMaterial("regular_reflective_ignorez_classic", "Model textures", true, NULL);

	ChamsStuff::init = true;
}

void doGlow() {
	if (I::Engine->IsInGame() && I::Engine->IsConnected() && I::Engine->IsActiveApp()) {
		C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
		if (LocalPlayer) {
			if (g_Vars->Visuals.Glow.Enabled)
			{
				CGlowObjectManager* GlowObjectManager = (CGlowObjectManager*)g_Globals->GlowManager;
				int a = g_Vars->Visuals.Glow.Alpha;
				for (int i = 0; i < GlowObjectManager->size; ++i)
				{
					CGlowObjectManager::GlowObjectDefinition_t* glowEntity = &GlowObjectManager->m_GlowObjectDefinitions[i];

					if (glowEntity->IsEmpty())
						continue;

					C_BaseEntity* Entity = glowEntity->getEntity();

					if (!Entity)
						continue;

					if (!Entity->IsValid())
						continue;

					if (Entity->GetTeam() == LocalPlayer->GetTeam() && !g_Vars->Visuals.Filter.Teammates)
						continue;

					if (g_Vars->Visuals.Glow.GlowBloom)
						glowEntity->m_bFullBloomRender = true;
					else
						glowEntity->m_bFullBloomRender = false;

					if (Entity->GetClientClass()->m_ClassID == CCSPlayer)
						glowEntity->set(Entity->GetTeam() == LocalPlayer->GetTeam() ? Color(int(g_Vars->Colors.GlowTeam[0] * 255.f), int(g_Vars->Colors.GlowTeam[1] * 255.f), int(g_Vars->Colors.GlowTeam[2] * 255.f), a) : Color(int(g_Vars->Colors.GlowEnemy[0] * 255.f), int(g_Vars->Colors.GlowEnemy[1] * 255.f), int(g_Vars->Colors.GlowEnemy[2] * 255.f), a));
				}
			}
		}
	}
}

SceneEndFn oSceneEnd;
void __fastcall Hooks::SceneEnd(void* thisptr, void* edx) {
	oSceneEnd(thisptr);

	doGlow();

	if (!ChamsStuff::init)
		setup();

	if (g_Vars->Visuals.Chams.Enabled && g_Vars->Visuals.Chams.Kind == 0)
		if (I::Engine->IsInGame() && I::Engine->IsConnected() && I::Engine->IsActiveApp()) {
			C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
			if (LocalPlayer) {

				for (int i = 1; i <= 65; ++i) {
					C_BaseEntity* Entity = I::EntityList->GetClientEntity(i);
					if (!Entity)
						continue;

					if (!Entity->IsValid())
						continue;

					if (Entity->GetTeam() == LocalPlayer->GetTeam() && !g_Vars->Visuals.Filter.Teammates)
						continue;

					if (g_Vars->Visuals.Chams.Ignorez) {
						I::RenderView->SetColorModulation(Entity->GetTeam() == LocalPlayer->GetTeam() ? Color(int(g_Vars->Colors.TeamIgnorez[0] * 255.f), int(g_Vars->Colors.TeamIgnorez[1] * 255.f), int(g_Vars->Colors.TeamIgnorez[2] * 255.f)).Base() : Color(int(g_Vars->Colors.EnemyIgnorez[0] * 255.f), int(g_Vars->Colors.EnemyIgnorez[1] * 255.f), int(g_Vars->Colors.EnemyIgnorez[2] * 255.f)).Base());
						
						if (g_Vars->Visuals.Chams.Style == 0)
							I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_ignorez_classic);
						else if (g_Vars->Visuals.Chams.Style == 1)
							I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_ignorez_flat);
						else if (g_Vars->Visuals.Chams.Style == 2)
							I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_ignorez);

						Entity->DrawModel(0x1, 255);
						I::ModelRender->ForcedMaterialOverride(NULL);
					}

					I::RenderView->SetColorModulation(Entity->GetTeam() == LocalPlayer->GetTeam() ? Color(int(g_Vars->Colors.TeamVisible[0] * 255.f), int(g_Vars->Colors.TeamVisible[1] * 255.f), int(g_Vars->Colors.TeamVisible[2] * 255.f)).Base() : Color(int(g_Vars->Colors.EnemyVisible[0] * 255.f), int(g_Vars->Colors.EnemyVisible[1] * 255.f), int(g_Vars->Colors.EnemyVisible[2] * 255.f)).Base());

					if (g_Vars->Visuals.Chams.Style == 0)
						I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_classic);
					else if (g_Vars->Visuals.Chams.Style == 1)
						I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_flat);
					else if (g_Vars->Visuals.Chams.Style == 2)
						I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat);

					Entity->DrawModel(0x1, 255);
					I::ModelRender->ForcedMaterialOverride(NULL);
				}
			}
		}
}

DrawModelExecuteFn oDrawModelExecute;
void __fastcall Hooks::DrawModelExecute(void* thisptr, int edx, IMatRenderContext* matctx, DrawModelState_t& state, ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld)
{
	if (pInfo.pModel)
	{
		C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
		if (LocalPlayer) {
			std::string modelName = I::ModelInfo->GetModelName(pInfo.pModel);
			if (g_Vars->Visuals.NoFlash)
				if (modelName.find("flash") != std::string::npos)
				{
					IMaterial* Flash = I::MaterialSystem->FindMaterial("effects\\flashbang", TEXTURE_GROUP_CLIENT_EFFECTS);
					IMaterial* FlashWhite = I::MaterialSystem->FindMaterial("effects\\flashbang_white", TEXTURE_GROUP_CLIENT_EFFECTS);
					Flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					FlashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					I::ModelRender->ForcedMaterialOverride(Flash);
					I::ModelRender->ForcedMaterialOverride(FlashWhite);
				}			
			if (g_Vars->Visuals.Chams.Enabled && g_Vars->Visuals.Chams.Kind == 1)
				if (modelName.find(strenc("models/player")) != std::string::npos)
				{
					PlayerInfo_t Inform;
					I::Engine->GetPlayerInfo(pInfo.entity_index, &Inform);
					C_BaseEntity* pModelEntity = I::EntityList->GetClientEntity(pInfo.entity_index);
					if (pModelEntity)
					{
						if (pModelEntity->IsValid())
						{
							if (pModelEntity->GetTeam() != LocalPlayer->GetTeam() || (pModelEntity->GetTeam() == LocalPlayer->GetTeam() && g_Vars->Visuals.Filter.Teammates))
							{
								if (g_Vars->Visuals.Chams.Ignorez)
								{
									I::RenderView->SetColorModulation(pModelEntity->GetTeam() == LocalPlayer->GetTeam() ? Color(int(g_Vars->Colors.TeamIgnorez[0] * 255.f), int(g_Vars->Colors.TeamIgnorez[1] * 255.f), int(g_Vars->Colors.TeamIgnorez[2] * 255.f)).Base() : Color(int(g_Vars->Colors.EnemyIgnorez[0] * 255.f), int(g_Vars->Colors.EnemyIgnorez[1] * 255.f), int(g_Vars->Colors.EnemyIgnorez[2] * 255.f)).Base());
									
									if (g_Vars->Visuals.Chams.Style == 0)
										I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_ignorez_classic);
									else if (g_Vars->Visuals.Chams.Style == 1)
										I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_ignorez_flat);
									else if (g_Vars->Visuals.Chams.Style == 2)
										I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_ignorez);
									
									oDrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
								}

								I::RenderView->SetColorModulation(pModelEntity->GetTeam() == LocalPlayer->GetTeam() ? Color(int(g_Vars->Colors.TeamVisible[0] * 255.f), int(g_Vars->Colors.TeamVisible[1] * 255.f), int(g_Vars->Colors.TeamVisible[2] * 255.f)).Base() : Color(int(g_Vars->Colors.EnemyVisible[0] * 255.f), int(g_Vars->Colors.EnemyVisible[1] * 255.f), int(g_Vars->Colors.EnemyVisible[2] * 255.f)).Base());
								if (g_Vars->Visuals.Chams.Style == 0)
									I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_classic);
								else if (g_Vars->Visuals.Chams.Style == 1)
									I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_flat);
								else if (g_Vars->Visuals.Chams.Style == 2)
									I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat);
							}			
						}
					}
				}

				if (modelName.find("arms") != std::string::npos && g_Vars->Visuals.Chams.Hands)
				{
					if (g_Vars->Visuals.Chams.HandsStyle == 0)
					{
						I::RenderView->SetColorModulation(Color(int(g_Vars->Colors.Hands[0] * 255.f), int(g_Vars->Colors.Hands[1] * 255.f), int(g_Vars->Colors.Hands[2] * 255.f)).Base());
						I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_classic);
					}
					else if (g_Vars->Visuals.Chams.HandsStyle == 1)
					{
						I::RenderView->SetColorModulation(Color(int(g_Vars->Colors.Hands[0] * 255.f), int(g_Vars->Colors.Hands[1] * 255.f), int(g_Vars->Colors.Hands[2] * 255.f)).Base());
						I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_flat);
					}
					else if (g_Vars->Visuals.Chams.HandsStyle == 2)
					{
						I::RenderView->SetColorModulation(Color(int(g_Vars->Colors.Hands[0] * 255.f), int(g_Vars->Colors.Hands[1] * 255.f), int(g_Vars->Colors.Hands[2] * 255.f)).Base());
						I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat);
					}
				}
				else if (modelName.find("weapon") != std::string::npos && g_Vars->Visuals.Chams.Weapons)
				{
					if (!(modelName.find("arms") != std::string::npos))
					{
						if (g_Vars->Visuals.Chams.WeaponsStyle == 0)
						{
							I::RenderView->SetColorModulation(Color(int(g_Vars->Colors.Weap[0] * 255.f), int(g_Vars->Colors.Weap[1] * 255.f), int(g_Vars->Colors.Weap[2] * 255.f)).Base());
							I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_classic);
						}
						else if (g_Vars->Visuals.Chams.WeaponsStyle == 1)
						{
							I::RenderView->SetColorModulation(Color(int(g_Vars->Colors.Weap[0] * 255.f), int(g_Vars->Colors.Weap[1] * 255.f), int(g_Vars->Colors.Weap[2] * 255.f)).Base());
							I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat_flat);
						}
						else if (g_Vars->Visuals.Chams.WeaponsStyle == 2)
						{
							I::RenderView->SetColorModulation(Color(int(g_Vars->Colors.Weap[0] * 255.f), int(g_Vars->Colors.Weap[1] * 255.f), int(g_Vars->Colors.Weap[2] * 255.f)).Base());
							I::ModelRender->ForcedMaterialOverride(ChamsStuff::chams_mat);
						}
					}
				}

			oDrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
			I::ModelRender->ForcedMaterialOverride(NULL);
		}
	}
	else
		oDrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
}