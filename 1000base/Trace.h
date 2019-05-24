#pragma once

struct virtualmeshlist_t;

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY, // NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY, // NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS, // NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

struct Ray_t
{
	Ray_t()
	{ }

	VectorAligned m_Start;
	VectorAligned m_Delta;
	VectorAligned m_StartOffset;
	VectorAligned m_Extents;
	const matrix3x4_t* m_pWorldAxisTransform;
	bool m_IsRay;
	bool m_IsSwept;

	void Init(Vector vecStart, Vector vecEnd)
	{
		m_Delta = VectorAligned(vecEnd - vecStart);
		m_IsSwept = (m_Delta.LengthSqr() != 0);
		m_Extents.Zero();
		m_pWorldAxisTransform = NULL;
		m_IsRay = true;
		m_StartOffset.Zero();
		m_Start = vecStart;
	}
	void Init(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs)
	{
		m_Delta = end - start;

		m_pWorldAxisTransform = NULL;
		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents = maxs - mins;
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LengthSqr() < 1e-6);

		// Offset m_Start to be in the center of the box...
		m_StartOffset = maxs + mins;
		m_StartOffset *= 0.5f;
		m_Start = start + m_StartOffset;
		m_StartOffset *= -1.0f;
	}
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(C_BaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t GetTraceType()
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip;
};

class CTraceFilter : public ITraceFilter
{
public:
	virtual bool ShouldHitEntity(C_BaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	inline void SetIgnoreClass(char* Class)
	{
		ccIgnore = Class;
	}

	void* pSkip;
	char* ccIgnore = "";
};

class CTraceFilterSkipTwoEntities : public ITraceFilter
{
public:
	CTraceFilterSkipTwoEntities(void* pPassEnt1, void* pPassEnt2)
	{
		pPassEntity1 = pPassEnt1;
		pPassEntity2 = pPassEnt2;
	}

	virtual bool ShouldHitEntity(C_BaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pPassEntity1 || pEntityHandle == pPassEntity2);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void* pPassEntity1;
	void* pPassEntity2;
};

typedef bool(*ShouldHitFunc_t)(IHandleEntity* pHandleEntity, int contentsMask);

class CTraceFilterSimple : public CTraceFilter
{
public:
	// It does have a base, but we'll never network anything below here..
	CTraceFilterSimple(const IHandleEntity* passentity, int collisionGroup, ShouldHitFunc_t pExtraShouldHitCheckFn = NULL);
	virtual bool ShouldHitEntity(IHandleEntity* pHandleEntity, int contentsMask);

	virtual void SetPassEntity(const IHandleEntity* pPassEntity)
	{
		m_pPassEnt = pPassEntity;
	}

	virtual void SetCollisionGroup(int iCollisionGroup)
	{
		m_collisionGroup = iCollisionGroup;
	}

	const IHandleEntity* GetPassEntity(void)
	{
		return m_pPassEnt;
	}

private:
	const IHandleEntity* m_pPassEnt;
	int m_collisionGroup;
	ShouldHitFunc_t m_pExtraShouldHitCheckFunction;
};

class CBaseTrace
{
public:
	Vector startpos;
	Vector endpos;
	cplane_t plane;

	float fraction;

	int contents;
	unsigned short dispFlags;

	bool allsolid;
	bool startsolid;

	CBaseTrace()
	{}
};

struct csurface_t
{
	const char* name;
	short surfaceProps;
	unsigned short flags;
};

class CGameTrace : public CBaseTrace
{
public:
	bool DidHitWorld() const;
	bool DidHitNonWorldEntity() const;
	int GetEntityIndex() const;
	inline bool CGameTrace::DidHit() const {
		return fraction < 1 || allsolid || startsolid;
	}
	inline bool CGameTrace::IsVisible() const {
		return fraction > 0.97f;
	}

public:

	float fractionleftsolid;
	csurface_t surface;
	int hitgroup;
	short physicsbone;
	unsigned short worldSurfaceIndex;
	C_BaseEntity* m_pEnt;
	int hitbox;

	CGameTrace()
	{ }

private:
	CGameTrace(const CGameTrace& vOther);
};

typedef CGameTrace trace_t;

class ITraceListData
{
public:
	virtual ~ITraceListData()
	{}

	virtual void Reset() = 0;
	virtual bool IsEmpty() = 0;
	// CanTraceRay will return true if the current volume encloses the ray
	// NOTE: The leaflist trace will NOT check this.  Traces are intersected
	// against the culled volume exclusively.
	virtual bool CanTraceRay(const Ray_t& ray) = 0;
};

class IEntityEnumerator
{
public:
	// This gets called with each handle
	virtual bool EnumEntity(IHandleEntity* pHandleEntity) = 0;
};

struct BrushSideInfo_t
{
	Vector plane; // The plane of the brush side
	float planec;
	unsigned short bevel; // Bevel plane?
	unsigned short thin; // Thin?
};

class ICollideable
{
public:
	virtual void pad0();
	virtual const Vector& OBBMins() const;
	virtual const Vector& OBBMaxs() const;
};

enum DebugTraceCounterBehavior_t
{
	kTRACE_COUNTER_SET = 0,
	kTRACE_COUNTER_INC,
};

class IEngineTrace
{
public:
	// Returns the contents mask + entity at a particular world-space position
	virtual int GetPointContents(const Vector& vecAbsPosition, int contentsMask = MASK_ALL, IHandleEntity** ppEntity = NULL) = 0;

	// Returns the contents mask of the world only @ the world-space position (static props are ignored)
	virtual int GetPointContents_WorldOnly(const Vector& vecAbsPosition, int contentsMask = MASK_ALL) = 0;

	// Get the point contents, but only test the specific entity. This works
	// on static props and brush models.
	//
	// If the entity isn't a static prop or a brush model, it returns CONTENTS_EMPTY and sets
	// bFailed to true if bFailed is non-null.
	virtual int GetPointContents_Collideable(ICollideable* pCollide, const Vector& vecAbsPosition) = 0;

	// Traces a ray against a particular entity
	virtual void ClipRayToEntity(const Ray_t& ray, unsigned int fMask, IHandleEntity* pEnt, trace_t* pTrace) = 0;

	// Traces a ray against a particular entity
	virtual void ClipRayToCollideable(const Ray_t& ray, unsigned int fMask, ICollideable* pCollide, trace_t* pTrace) = 0;

	// A version that simply accepts a ray (can work as a traceline or tracehull)
	virtual void TraceRay(const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;

	// A version that sets up the leaf and entity lists and allows you to pass those in for collision.
	virtual void SetupLeafAndEntityListRay(const Ray_t& ray, ITraceListData* pTraceData) = 0;
	virtual void SetupLeafAndEntityListBox(const Vector& vecBoxMin, const Vector& vecBoxMax, ITraceListData* pTraceData) = 0;
	virtual void TraceRayAgainstLeafAndEntityList(const Ray_t& ray, ITraceListData* pTraceData, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;

	// A version that sweeps a collideable through the world
	// abs start + abs end represents the collision origins you want to sweep the collideable through
	// vecAngles represents the collision angles of the collideable during the sweep
	virtual void SweepCollideable(ICollideable* pCollide, const Vector& vecAbsStart, const Vector& vecAbsEnd,
		const QAngle& vecAngles, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace) = 0;

	// Enumerates over all entities along a ray
	// If triggers == true, it enumerates all triggers along a ray
	virtual void EnumerateEntities(const Ray_t& ray, bool triggers, IEntityEnumerator* pEnumerator) = 0;

	// Same thing, but enumerate entitys within a box
	virtual void EnumerateEntities(const Vector& vecAbsMins, const Vector& vecAbsMaxs, IEntityEnumerator* pEnumerator) = 0;

	// Convert a handle entity to a collideable.  Useful inside enumer
	virtual ICollideable* GetCollideable(IHandleEntity* pEntity) = 0;

	// HACKHACK: Temp for performance measurments
	virtual int GetStatByIndex(int index, bool bClear) = 0;

	//finds brushes in an AABB, prone to some false positives
	virtual void lolignorethisaswellrifk() = 0;

	//Creates a CPhysCollide out of all displacements wholly or partially contained in the specified AABB
	virtual void GetCollidableFromDisplacementsInAABB() = 0;

	// gets the number of displacements in the world
	virtual int GetNumDisplacements() = 0;

	// gets a specific diplacement mesh
	virtual void GetDisplacementMesh(int nIndex, virtualmeshlist_t* pMeshTriList) = 0;

	//retrieve brush planes and contents, returns true if data is being returned in the output pointers, false if the brush doesn't exist
	virtual bool lolignorethis() = 0;

	virtual bool PointOutsideWorld(const Vector& ptTest) = 0; //Tests a point to see if it's outside any playable area

															  // Walks bsp to find the leaf containing the specified point
	virtual int GetLeafContainingPoint(const Vector& ptTest) = 0;

	virtual ITraceListData* AllocTraceListData() = 0;
	virtual void FreeTraceListData(ITraceListData*) = 0;

	/// Used only in debugging: get/set/clear/increment the trace debug counter. See comment below for details.
	virtual int GetSetDebugTraceCounter(int value, DebugTraceCounterBehavior_t behavior) = 0;
};
