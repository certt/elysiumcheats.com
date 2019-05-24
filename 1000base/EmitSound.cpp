#include "Main.h"

void SetLocalPlayerReady()
{
	static auto SetLocalPlayerReadyFn = reinterpret_cast<bool(__stdcall*)(const char*)>(g_Utils->FindPatternIDA("client_panorama.dll", "55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12"));
	if (SetLocalPlayerReadyFn)
		SetLocalPlayerReadyFn("");
}

EmitSound1Fn oEmitSound1;
int WINAPI Hooks::hEmitSound1(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample,
	float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags = 0, int iPitch = PITCH_NORM,
	const Vector *pOrigin = NULL, const Vector *pDirection = NULL, CUtlVector< Vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1, int unklown = NULL)
{
	if (g_Vars->Misc.AutoAccept && !strcmp(pSoundEntry, "UIPanorama.popup_accept_match_beep"))
		SetLocalPlayerReady();

	int ret = oEmitSound1(filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample,
		flVolume, iSoundlevel, nSeed, iFlags, iPitch,
		pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity, unklown);

	return ret;
}