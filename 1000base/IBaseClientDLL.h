#pragma once

class C_BaseEntity;
class IPanel;
class CViewSetup
{
public:
	__int32   x;
	__int32   x_old;
	__int32   y;
	__int32   y_old;
	__int32   width;
	__int32   width_old;
	__int32   height;
	__int32   height_old;
	char      pad_0x0020[0x90];
	float     fov;
	float     viewmodel_fov;
	Vector    origin;
	Vector    angles;
	char      pad_0x00D0[0x7C];
};

class IBaseClientDLL
{
public:
	ClientClass * GetAllClasses()
	{
		typedef ClientClass* (__thiscall* GetAllClassesFn)(void*);
		return g_Utils->get_vfunc<GetAllClassesFn>(this, 8)(this);
	}
};

class IGlobalVars
{
public:
	float     realtime;
	int       framecount;
	float     absoluteframetime;
	float     absoluteframestarttimestddev;
	float     curtime;
	float     frametime;
	int       maxClients;
	int       tickcount;
	float     intervalPerTick;
	float     interpolationAmount;
	int       simTicksThisFrame;
	int       networkProtocol;
	void*     pSaveData;
	bool      bClient;
	bool      bRemoteClient;

private:
	int       nTimestampNetworkingBase;
	int       nTimestampRandomizeWindow;
};

inline int UtlMemory_CalcNewAllocationCount(int nAllocationCount, int nGrowSize, int nNewSize, int nBytesItem)
{
	if (nGrowSize)
		nAllocationCount = ((1 + ((nNewSize - 1) / nGrowSize)) * nGrowSize);
	else
	{
		if (!nAllocationCount)
			nAllocationCount = (31 + nBytesItem) / nBytesItem;

		while (nAllocationCount < nNewSize)
			nAllocationCount *= 2;
	}

	return nAllocationCount;
}

template< class T, class I = int >
class CUtlMemory
{
public:
	T & operator[](I i)
	{
		return m_pMemory[i];
	}

	T* Base()
	{
		return m_pMemory;
	}

	int NumAllocated() const
	{
		return m_nAllocationCount;
	}

	void Grow(int num = 1)
	{
		if (IsExternallyAllocated())
			return;

		int nAllocationRequested = m_nAllocationCount + num;
		int nNewAllocationCount = UtlMemory_CalcNewAllocationCount(m_nAllocationCount, m_nGrowSize, nAllocationRequested, sizeof(T));

		if ((int)(I)nNewAllocationCount < nAllocationRequested)
		{
			if ((int)(I)nNewAllocationCount == 0 && (int)(I)(nNewAllocationCount - 1) >= nAllocationRequested)
				--nNewAllocationCount;
			else
			{
				if ((int)(I)nAllocationRequested != nAllocationRequested)
					return;

				while ((int)(I)nNewAllocationCount < nAllocationRequested)
					nNewAllocationCount = (nNewAllocationCount + nAllocationRequested) / 2;
			}
		}

		m_nAllocationCount = nNewAllocationCount;

		if (m_pMemory)
			m_pMemory = (T*)g_pMemAlloc->Realloc(m_pMemory, m_nAllocationCount * sizeof(T));
		else
			m_pMemory = (T*)g_pMemAlloc->Alloc(m_nAllocationCount * sizeof(T));
	}

	bool IsExternallyAllocated() const
	{
		return m_nGrowSize < 0;
	}

protected:
	T * m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};

template <class T>
inline T* Construct(T* pMemory)
{
	return ::new(pMemory) T;
}

template <class T>
inline void Destruct(T* pMemory)
{
	pMemory->~T();
}

template< class T, class A = CUtlMemory<T> >
class CUtlVector
{
	typedef A CAllocator;
public:
	T & operator[](int i)
	{
		return m_Memory[i];
	}

	T& Element(int i)
	{
		return m_Memory[i];
	}

	T* Base()
	{
		return m_Memory.Base();
	}

	int Count() const
	{
		return m_Size;
	}

	void RemoveAll()
	{
		for (int i = m_Size; --i >= 0; )
			Destruct(&Element(i));

		m_Size = 0;
	}

	int AddToTail()
	{
		return InsertBefore(m_Size);
	}

	int InsertBefore(int elem)
	{
		GrowVector();
		ShiftElementsRight(elem);
		Construct(&Element(elem));

		return elem;
	}

protected:
	void GrowVector(int num = 1)
	{
		if (m_Size + num > m_Memory.NumAllocated())
			m_Memory.Grow(m_Size + num - m_Memory.NumAllocated());

		m_Size += num;
		ResetDbgInfo();
	}

	void ShiftElementsRight(int elem, int num = 1)
	{
		int numToMove = m_Size - elem - num;
		if ((numToMove > 0) && (num > 0))
			memmove(&Element(elem + num), &Element(elem), numToMove * sizeof(T));
	}

	CAllocator m_Memory;
	int m_Size;

	T* m_pElements;

	inline void ResetDbgInfo()
	{
		m_pElements = Base();
	}
};


class IClientMode
{
public:
	virtual             ~IClientMode() {}
	virtual int         ClientModeCSNormal(void *) = 0;
	virtual void        Init() = 0;
	virtual void        InitViewport() = 0;
	virtual void        Shutdown() = 0;
	virtual void        Enable() = 0;
	virtual void        Disable() = 0;
	virtual void        Layout() = 0;
	virtual IPanel*     GetViewport() = 0;
	virtual void*       GetViewportAnimationController() = 0;
	virtual void        ProcessInput(bool bActive) = 0;
	virtual bool        ShouldDrawDetailObjects() = 0;
	virtual bool        ShouldDrawEntity(C_BaseEntity *pEnt) = 0;
	virtual bool        ShouldDrawLocalPlayer(C_BaseEntity *pPlayer) = 0;
	virtual bool        ShouldDrawParticles() = 0;
	virtual bool        ShouldDrawFog(void) = 0;
	virtual void        OverrideView(CViewSetup *pSetup) = 0; // 19
	virtual int         KeyInput(int down, int keynum, const char *pszCurrentBinding) = 0; // 20
	virtual void        StartMessageMode(int iMessageModeType) = 0; //21
	virtual IPanel*     GetMessagePanel() = 0; //22
	virtual void        OverrideMouseInput(float *x, float *y) = 0; //23
	virtual bool        CreateMove(float flSampleFrametime, void* pCmd) = 0; // 24
	virtual void        LevelInit(const char *newmap) = 0;
	virtual void        LevelShutdown(void) = 0;
};