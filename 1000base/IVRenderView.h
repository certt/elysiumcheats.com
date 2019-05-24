#pragma once

#define MAX_AREA_STATE_BYTES		32
#define MAX_AREA_PORTAL_STATE_BYTES 24

class IRefCounted
{
public:
	virtual int AddRef() = 0;
	virtual int Release() = 0;
};

class IWorldRenderList : public IRefCounted
{};

struct VisibleFogVolumeInfo_t
{
	int m_nVisibleFogVolume;
	int m_nVisibleFogVolumeLeaf;
	bool m_bEyeInFogVolume;
	float m_flDistanceToWater;
	float m_flWaterHeight;
	IMaterial* m_pFogVolumeMaterial;
};

typedef unsigned short LeafIndex_t;

enum
{
	INVALID_LEAF_INDEX = (LeafIndex_t)~0
};

typedef __int16 int16;
typedef unsigned __int16 uint16;

struct WorldListLeafData_t
{
	LeafIndex_t leafIndex;
	int16 waterData;
	uint16 firstTranslucentSurface;
	uint16 translucentSurfaceCount;
};

struct WorldListInfo_t
{
	int m_ViewFogVolume;
	int m_LeafCount;
	bool m_bHasWater;
	WorldListLeafData_t* m_pLeafDataList;
};

struct VisOverrideData_t
{
	Vector m_vecVisOrigin;
	float m_fDistToAreaPortalTolerance;
};

struct BrushVertex_t
{
	Vector m_Pos;
	Vector m_Normal;
	Vector m_TangentS;
	Vector m_TangentT;
	Vector2D m_TexCoord;
	Vector2D m_LightmapCoord;

private:
	BrushVertex_t(const BrushVertex_t& src);
};

class IBrushSurface
{
public:
	virtual void ComputeTextureCoordinate(Vector const& worldPos, Vector2D& texCoord) = 0;
	virtual void ComputeLightmapCoordinate(Vector const& worldPos, Vector2D& lightmapCoord) = 0;
	virtual int GetVertexCount() const = 0;
	virtual void GetVertexData(BrushVertex_t* pVerts) = 0;
	virtual IMaterial* GetMaterial() = 0;
};

class IBrushRenderer
{
public:
	virtual bool RenderBrushModelSurface(C_BaseEntity* pBaseEntity, IBrushSurface* pBrushSurface) = 0;
};

struct colorVec
{
	unsigned r, g, b, a;
};

class IVRenderView
{
public:
	virtual void DrawBrushModel(C_BaseEntity* baseentity, model_t* model, const Vector& origin, const QAngle& angles, bool sort) = 0;
	virtual void DrawIdentityBrushModel(IWorldRenderList* pList, model_t* model) = 0;
	virtual void TouchLight(struct dlight_t* light) = 0;
	virtual void Draw3DDebugOverlays(void) = 0;
	virtual void SetBlend(float blend) = 0;
	virtual float GetBlend(void) = 0;
	virtual void SetColorModulation(float const* blend) = 0;
	virtual void GetColorModulation(float* blend) = 0;
	virtual void SceneBegin(void) = 0;
	virtual void SceneEnd(void) = 0;
	virtual void GetVisibleFogVolume(const Vector& eyePoint, VisibleFogVolumeInfo_t* pInfo) = 0;
	virtual IWorldRenderList* CreateWorldList() = 0;
	virtual void BuildWorldLists(IWorldRenderList* pList, WorldListInfo_t* pInfo, int iForceFViewLeaf, const VisOverrideData_t* pVisData = NULL, bool bShadowDepth = false, float* pReflectionWaterHeight = NULL) = 0;
	virtual void DrawWorldLists(IWorldRenderList* pList, unsigned long flags, float waterZAdjust) = 0;
	virtual int GetNumIndicesForWorldLists(IWorldRenderList* pList, unsigned long nFlags) = 0;
	virtual void DrawTopView(bool enable) = 0;
	virtual void TopViewBounds(Vector2D const& mins, Vector2D const& maxs) = 0;
	virtual void DrawLights(void) = 0;
	virtual void DrawMaskEntities(void) = 0;
	virtual void DrawTranslucentSurfaces(IWorldRenderList* pList, int* pSortList, int sortCount, unsigned long flags) = 0;
	virtual void DrawLineFile(void) = 0;
	virtual void DrawLightmaps(IWorldRenderList* pList, int pageId) = 0;
	virtual void ViewSetupVis(bool novis, int numorigins, const Vector origin[]) = 0;
	virtual bool AreAnyLeavesVisible(int* leafList, int nLeaves) = 0;
	virtual void VguiPaint(void) = 0;
	virtual void ViewDrawFade(byte* color, IMaterial* pMaterial) = 0;
	virtual void OLD_SetProjectionMatrix(float fov, float zNear, float zFar) = 0;
	virtual colorVec GetLightAtPoint(Vector& pos) = 0;
	virtual int GetViewEntity(void) = 0;
	virtual bool IsViewEntity(int entindex) = 0;
	virtual float GetFieldOfView(void) = 0;
	virtual unsigned char** GetAreaBits(void) = 0;
	virtual void SetFogVolumeState(int nVisibleFogVolume, bool bUseHeightFog) = 0;
	virtual void InstallBrushSurfaceRenderer(IBrushRenderer* pBrushRenderer) = 0;
	virtual void DrawBrushModelShadow(IClientRenderable* pRenderable) = 0;
	virtual bool LeafContainsTranslucentSurfaces(IWorldRenderList* pList, int sortIndex, unsigned long flags) = 0;
	virtual bool DoesBoxIntersectWaterVolume(const Vector& mins, const Vector& maxs, int leafWaterDataID) = 0;
	virtual void SetAreaState(unsigned char chAreaBits[MAX_AREA_STATE_BYTES], unsigned char chAreaPortalBits[MAX_AREA_PORTAL_STATE_BYTES]) = 0;
	virtual void VGui_Paint(int mode) = 0;
};
