#pragma once

class IMaterialSystem
{
public:
	IMaterial* FindMaterial(char const* pMaterialName, const char* pTextureGroupName, bool complain = true, const char* pComplainPrefix = NULL);
	MaterialHandle_t FirstMaterial();
	MaterialHandle_t InvalidMaterial();
	MaterialHandle_t NextMaterial(MaterialHandle_t h);
	IMaterial* GetMaterial(MaterialHandle_t h);
};
