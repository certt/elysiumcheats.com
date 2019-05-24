#pragma once

class IGameEvent
{
public:
	template <typename T>
	T CallVFunc(void *vTable, int iIndex) {
		return (*(T**)vTable)[iIndex];
	}
	const char* GetName() {
		return CallVFunc<const char*(__thiscall *)(void*)>(this, 1)(this);
	}

	int GetInt(const char* szKeyName, int nDefault = 0) {
		return CallVFunc<int(__thiscall *)(void*, const char*, int)>(this, 6)(this, szKeyName, nDefault);
	}

	const char* GetString(const char* szKeyName) {
		return CallVFunc<const char*(__thiscall *)(void*, const char*, int)>(this, 9)(this, szKeyName, 0);
	}

	void SetString(const char* szKeyName, const char* szValue) {
		return CallVFunc<void(__thiscall *)(void*, const char*, const char*)>(this, 16)(this, szKeyName, szValue);
	}
};

class IGameEventListener2
{
public:
	virtual ~IGameEventListener2() { };
	virtual void FireGameEvent(IGameEvent* event) = 0;
	virtual int GetEventDebugID() = 0;
};

class IGameEventManager2
{
public:
	virtual ~IGameEventManager2(void) { };
	virtual int LoadEventsFromFile(const char* filename) = 0;
	virtual void Reset() = 0;
	virtual bool AddListener(IGameEventListener2* listener, const char* name, bool serverside) = 0;
	virtual bool FindListener(IGameEventListener2* listener, const char* name) = 0;
	virtual void RemoveListener(IGameEventListener2* listener) = 0;
	virtual void AddListenerGlobal(IGameEventListener2* listener, bool serverside) = 0;
	virtual IGameEvent* CreateEvent(const char* name, bool force = false, int* cookie = nullptr) = 0;
	virtual bool FireEvent(IGameEvent* event, bool bDontBroadcast = false) = 0;
	virtual bool FireEventClientSide(IGameEvent* event) = 0;
	virtual IGameEvent* DuplicateEvent(IGameEvent* event) = 0;
	virtual void FreeEvent(IGameEvent* event) = 0;
	virtual KeyValues* GetEventDataTypes(IGameEvent* event) = 0;
};