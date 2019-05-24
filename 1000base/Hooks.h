#pragma once

using EndSceneFn = long(__stdcall*)(IDirect3DDevice9* pDevice);
extern EndSceneFn oEndScene;

using ResetFn = long(__stdcall*)(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pp);
extern ResetFn oReset;

using CreateMoveFn = bool(__stdcall*)(float, CUserCmd*);
extern CreateMoveFn oCreateMove;

using FrameStageNotifyFn = void(__stdcall*)(ClientFrameStage_t);
extern FrameStageNotifyFn oFrameStageNotify;

using EmitSound1Fn = int(WINAPI*)(IRecipientFilter&, int, int, const char*, unsigned int, const char *, float, soundlevel_t, int, int, int, const Vector *, const Vector *, CUtlVector< Vector >*, bool, float, int, int);
extern EmitSound1Fn oEmitSound1;

using OverrideViewFn = void(__stdcall*)(CViewSetup*);
extern OverrideViewFn oOverrideView;

typedef float(__stdcall* GetViewModelFOVFn)();
extern GetViewModelFOVFn oGetViewModelFOV;

typedef void(__thiscall* LockCursorFn)(void*);
extern LockCursorFn oLockCursor;

using FireEventClientSideFn = bool(__thiscall*)(IGameEventManager2*, IGameEvent*);
extern FireEventClientSideFn oFireEventClientSide;

using PresentFn = long(__stdcall*)(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
extern PresentFn oPresent;

using DrawModelExecuteFn = void*(__thiscall*)(void*, IMatRenderContext* matctx, DrawModelState_t& state, ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld);
extern DrawModelExecuteFn oDrawModelExecute;

using SceneEndFn = void(__fastcall *)(void* thisptr);
extern SceneEndFn oSceneEnd;

namespace Hooks {
	// Ingame hooks
	extern void AnimationFixHook();
	extern void __stdcall hk_lockcursor();
	extern float __stdcall GetViewModelFOV();
	extern void __stdcall OverrideView(CViewSetup* vsView);
	extern void __fastcall SceneEnd(void* thisptr, void* edx);
	extern void __stdcall FrameStageNotify(ClientFrameStage_t stage);
	extern bool __stdcall CreateMove(float flInputSampleTime, CUserCmd* cmd);
	extern long __stdcall Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
	extern bool __fastcall hkFireEventClientSide(IGameEventManager2* thispt, void* edx, IGameEvent* pEvent);
	extern long __stdcall Present(IDirect3DDevice9* device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);
	extern void __fastcall DrawModelExecute(void* thisptr, int edx, IMatRenderContext* matctx, DrawModelState_t& state, ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld);
	extern int __stdcall hEmitSound1(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, soundlevel_t iSoundlevel, int nSeed, int iFlags, int iPitch, const Vector *pOrigin, const Vector *pDirection, CUtlVector< Vector >* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, int ghay1);

	// System hooks
	extern WNDPROC oldWindowProc;
	extern LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}