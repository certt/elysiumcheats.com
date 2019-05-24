#include "Main.h"

GetViewModelFOVFn oGetViewModelFOV;
float __stdcall Hooks::GetViewModelFOV()
{
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	if (!LocalPlayer)
		return oGetViewModelFOV();

	if (!LocalPlayer->IsValid())
		return oGetViewModelFOV();

	if (g_Vars->Misc.MODEL_FOV != 120)
		return g_Vars->Misc.MODEL_FOV;
	else
		return oGetViewModelFOV();
}

OverrideViewFn oOverrideView;
void __stdcall Hooks::OverrideView(CViewSetup* vsView)
{
	if (g_Vars->Misc.FOV != 120 && I::Engine->IsInGame())
	{
		C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
		if (LocalPlayer)
			if (LocalPlayer->GetAlive())
				if (!LocalPlayer->IsScoped())
					vsView->fov = g_Vars->Misc.FOV;

	}

	g_Globals->FOV = vsView->fov;

	oOverrideView(vsView);
}