#include "Main.h"

void IVModelRender::ForcedMaterialOverride(IMaterial* mat)
{
	typedef void(__thiscall *OrigFn)(void*, IMaterial*, int, int);
	g_Utils->get_vfunc<OrigFn>(this, 1)(this, mat, 0, 0);
}

void IVModelRender::DrawModelExecute(void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	typedef void(__thiscall* OriginalFn)(void*, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld);
	return g_Utils->get_vfunc<OriginalFn>(this, 21)(this, ctx, state, pInfo, pCustomBoneToWorld);
}