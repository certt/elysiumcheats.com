#include "Main.h"
#include "SkinParser.h"
#define POINTERCHK( pointer ) ( pointer  && pointer !=0  && HIWORD( pointer ) )
void Utils::InitHooks()
{
	// Get adress
	static DWORD dwPresent = Utils::FindPatternIDA("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 DB") + 0x2;
	static DWORD dwReset = Utils::FindPatternIDA("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 FF 78 18") + 0x2;
	g_Globals->GlowManager = *(DWORD*)(Utils::FindPatternIDA("client_panorama.dll", "0F 11 05 ?? ?? ?? ?? 83 C8 01 C7 05 ?? ?? ?? ?? 00 00 00 00") + 3);

	// Vars
	std::unique_ptr<CVMTHookManager> Client;
	std::unique_ptr<CVMTHookManager> Surface;
	std::unique_ptr<CVMTHookManager> RenderView;
	std::unique_ptr<CVMTHookManager> ClientMode;
	std::unique_ptr<CVMTHookManager> EngineSound;
	std::unique_ptr<CVMTHookManager> ModelRender;
	std::unique_ptr<CVMTHookManager> EventManager;

	// Setup
	Client = std::make_unique<CVMTHookManager>(I::Client);
	Surface = std::make_unique<CVMTHookManager>(I::Surface);
	RenderView = std::make_unique<CVMTHookManager>(I::RenderView);
	ClientMode = std::make_unique<CVMTHookManager>(I::ClientMode);
	ModelRender = std::make_unique<CVMTHookManager>(I::ModelRender);
	EngineSound = std::make_unique<CVMTHookManager>(I::EngineSound);
	EventManager = std::make_unique<CVMTHookManager>(I::EventManager);

	oPresent = (PresentFn)((new CVMTHookManager((PDWORD*)dwPresent))->dwHookMethod((DWORD)&Hooks::Present, 0));
	oReset = (ResetFn)((new CVMTHookManager((PDWORD*)dwReset))->dwHookMethod((DWORD)&Hooks::Reset, 0));

	oSceneEnd = (SceneEndFn)RenderView->dwHookMethod((DWORD)Hooks::SceneEnd, 9);
	oCreateMove = (CreateMoveFn)ClientMode->dwHookMethod((DWORD)Hooks::CreateMove, 24);
	oLockCursor = (LockCursorFn)Surface->dwHookMethod((DWORD)Hooks::hk_lockcursor, 67);
	oEmitSound1 = (EmitSound1Fn)EngineSound->dwHookMethod((DWORD)Hooks::hEmitSound1, 5);
	oOverrideView = (OverrideViewFn)ClientMode->dwHookMethod((DWORD)Hooks::OverrideView, 18);
	oFrameStageNotify = (FrameStageNotifyFn)Client->dwHookMethod((DWORD)Hooks::FrameStageNotify, 37);
	oGetViewModelFOV = (GetViewModelFOVFn)ClientMode->dwHookMethod((DWORD)Hooks::GetViewModelFOV, 35);
	oDrawModelExecute = (DrawModelExecuteFn)ModelRender->dwHookMethod((DWORD)Hooks::DrawModelExecute, 21);
	oFireEventClientSide = (FireEventClientSideFn)EventManager->dwHookMethod((DWORD)Hooks::hkFireEventClientSide, 9);

	/*if (d3d9)
	{
		oEndScene = (EndSceneFn)(d3d9->dwHookMethod((DWORD)&Hooks::EndScene, 42));
		oReset = (ResetFn)(d3d9->dwHookMethod((DWORD)&Hooks::Reset, 16));
	}*/

	/*std::unique_ptr<CVMTHookManager> Client;
	std::unique_ptr<CVMTHookManager> ClientMode;
	std::unique_ptr<CVMTHookManager> EngineSound;
	std::unique_ptr<CVMTHookManager> RenderView;
	std::unique_ptr<CVMTHookManager> EventManager;
	std::unique_ptr<CVMTHookManager> ModelRender;
	std::unique_ptr<CVMTHookManager> Surface;
	std::unique_ptr<CVMTHookManager> d3d9;
	Surface = std::make_unique<CVMTHookManager>(I::Surface);
	ModelRender = std::make_unique<CVMTHookManager>(I::ModelRender);
	RenderView = std::make_unique<CVMTHookManager>(I::RenderView);
	ClientMode = std::make_unique<CVMTHookManager>(I::ClientMode);
	Client = std::make_unique<CVMTHookManager>(I::Client);
	EngineSound = std::make_unique<CVMTHookManager>(I::EngineSound);
	EventManager = std::make_unique<CVMTHookManager>(I::EventManager);
	DWORD d3d9Device = **(DWORD**)(Utils::FindPatternIDA("shaderapidx9.dll", "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C") + 0x1);
	d3d9 = std::make_unique<CVMTHookManager>((DWORD**)d3d9Device);
	g_Globals->GlowManager = *(DWORD*)(Utils::FindPatternIDA("client_panorama.dll", "0F 11 05 ?? ?? ?? ?? 83 C8 01 C7 05 ?? ?? ?? ?? 00 00 00 00") + 3);
	g_Menu->initializeskins();*/

	/*oFireEventClientSide = (FireEventClientSideFn)EventManager->dwHookMethod((DWORD)Hooks::hkFireEventClientSide, 9);
	oFrameStageNotify = (FrameStageNotifyFn)Client->dwHookMethod((DWORD)Hooks::FrameStageNotify, 37);
	oSceneEnd = (SceneEndFn)RenderView->dwHookMethod((DWORD)Hooks::SceneEnd, 9);
	oLockCursor = (LockCursorFn)Surface->dwHookMethod((DWORD)Hooks::hk_lockcursor, 67);
	oEmitSound1 = (EmitSound1Fn)EngineSound->dwHookMethod((DWORD)Hooks::hEmitSound1, 5);
	oCreateMove = (CreateMoveFn)ClientMode->dwHookMethod((DWORD)Hooks::CreateMove, 24);
	oDrawModelExecute = (DrawModelExecuteFn)ModelRender->dwHookMethod((DWORD)Hooks::DrawModelExecute, 21);
	oEndScene = (EndSceneFn)(d3d9->dwHookMethod((DWORD)&Hooks::EndScene, 42));
	oReset = (ResetFn)(d3d9->dwHookMethod((DWORD)&Hooks::Reset, 16));
	oOverrideView = (OverrideViewFn)ClientMode->dwHookMethod((DWORD)Hooks::OverrideView, 18);
	oGetViewModelFOV = (GetViewModelFOVFn)ClientMode->dwHookMethod((DWORD)Hooks::GetViewModelFOV, 35);*/
}

float Utils::GetDistance(Vector EntityOrigin, C_BaseEntity* LocalPlayer)
{
	if (!LocalPlayer || LocalPlayer == NULL || LocalPlayer == nullptr)
		return 0.0f;

	float distance = EntityOrigin.DistTo(LocalPlayer->GetOrigin());

	return distance;
}

void Utils::SetClantag(const char* tag)
{
	static auto fnClantagChanged = (int(__fastcall*)(const char*, const char*))g_Utils->FindPatternIDA("engine.dll", "53 56 57 8B DA 8B F9 FF 15");

	fnClantagChanged(tag, tag);
}

bool Utils::WorldToScreen(const Vector &origin, Vector &screen)
{
	const auto screenTransform = [&origin, &screen]() -> bool
	{
		static std::uintptr_t pViewMatrix;
		if (!pViewMatrix)
		{
			pViewMatrix = static_cast<std::uintptr_t>(g_Utils->FindPatternIDA("client_panorama.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9"));
			pViewMatrix += 3;
			pViewMatrix = *reinterpret_cast<std::uintptr_t*>(pViewMatrix);
			pViewMatrix += 176;
		}

		const VMatrix& w2sMatrix = *reinterpret_cast<VMatrix*>(pViewMatrix);
		screen.x = w2sMatrix.m[0][0] * origin.x + w2sMatrix.m[0][1] * origin.y + w2sMatrix.m[0][2] * origin.z + w2sMatrix.m[0][3];
		screen.y = w2sMatrix.m[1][0] * origin.x + w2sMatrix.m[1][1] * origin.y + w2sMatrix.m[1][2] * origin.z + w2sMatrix.m[1][3];
		screen.z = 0.0f;

		float w = w2sMatrix.m[3][0] * origin.x + w2sMatrix.m[3][1] * origin.y + w2sMatrix.m[3][2] * origin.z + w2sMatrix.m[3][3];

		if (w < 0.001f)
		{
			screen.x *= 100000;
			screen.y *= 100000;
			return true;
		}

		float invw = 1.f / w;
		screen.x *= invw;
		screen.y *= invw;

		return false;
	};

	if (!screenTransform())
	{
		int iScreenWidth, iScreenHeight;
		I::Engine->GetScreenSize(iScreenWidth, iScreenHeight);

		screen.x = (iScreenWidth * 0.5f) + (screen.x * iScreenWidth) * 0.5f;
		screen.y = (iScreenHeight * 0.5f) - (screen.y * iScreenHeight) * 0.5f;

		return true;
	}
	return false;
}
DWORD Utils::FindPatternIDA(std::string moduleName, std::string pattern)
{
	const char* pat = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo;
	K32GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2;
		}
		else
		{
			pat = pattern.c_str();
			firstMatch = 0;
		}
	}

	return NULL;
}