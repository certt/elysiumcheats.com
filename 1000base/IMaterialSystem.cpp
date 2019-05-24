#include "Main.h"

IMaterial* IMaterialSystem::FindMaterial(char const* pMaterialName, const char* pTextureGroupName, bool complain, const char* pComplainPrefix)
{
	typedef IMaterial*(__thiscall* OriginalFn)(void*, char const* pMaterialName, const char* pTextureGroupName, bool complain, const char* pComplainPrefix);
	return g_Utils->get_vfunc< OriginalFn >(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
}

IMaterial* IMaterialSystem::GetMaterial(MaterialHandle_t h)
{
	typedef IMaterial*(__thiscall* GetMaterialFn)(void*, MaterialHandle_t);
	return g_Utils->get_vfunc<GetMaterialFn>(this, 89)(this, h);
}

MaterialHandle_t IMaterialSystem::FirstMaterial()
{
	typedef MaterialHandle_t(__thiscall* FirstMaterialFn)(void*);
	return g_Utils->get_vfunc<FirstMaterialFn>(this, 86)(this);
}

MaterialHandle_t IMaterialSystem::InvalidMaterial()
{
	typedef MaterialHandle_t(__thiscall* InvalidMaterialFn)(void*);
	return g_Utils->get_vfunc<InvalidMaterialFn>(this, 88)(this);
}

MaterialHandle_t IMaterialSystem::NextMaterial(MaterialHandle_t h)
{
	typedef MaterialHandle_t(__thiscall* NextMaterialFn)(void*, MaterialHandle_t);
	return g_Utils->get_vfunc<NextMaterialFn>(this, 87)(this, h);
}