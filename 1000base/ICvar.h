#pragma once

using CreateInterfaceFn = void* (*)(const char*, int*);

template <class T>
T* CaptureInterface(const char* szModule, const char* szName)
{
	return reinterpret_cast<T*>(platform::CaptureInterface(szModule, szName));
}

#pragma once

class ConVar
{
public:
	float GetFloat();
	int GetInt();

	void SetValue(const char *value);
	void SetValue(float value);
	void SetValue(int value);
	void SetValue(Color value);
	void InternalSetString(const char* str);
	char* GetName();
	char* GetDefault();

	char pad_0x0000[0x4]; //0x0000
	ConVar* pNext; //0x0004 
	__int32 bRegistered; //0x0008 
	char* pszName; //0x000C 
	char* pszHelpString; //0x0010 
	__int32 nFlags; //0x0014 
	char pad_0x0018[0x4]; //0x0018
	ConVar* pParent; //0x001C 
	char* pszDefaultValue; //0x0020 
	char* strString; //0x0024 
	__int32 StringLength; //0x0028 
	float fValue; //0x002C 
	__int32 nValue; //0x0030 
	__int32 bHasMin; //0x0034 
	float fMinVal; //0x0038 
	__int32 bHasMax; //0x003C 
	float fMaxVal; //0x0040 
	void* fnChangeCallback; //0x0044 
};//Size=0x0048

class SpoofedConvar {
public:
	SpoofedConvar();
	SpoofedConvar(const char* szCVar);
	SpoofedConvar(ConVar* pCVar);

	~SpoofedConvar();

	bool           IsSpoofed();
	void           Spoof();

	void           SetFlags(int flags);
	int            GetFlags();

	void           SetBool(bool bValue);
	void           SetInt(int iValue);
	void           SetFloat(float flValue);
	void           SetString(const char* szValue);

private:
	ConVar * m_pOriginalCVar = nullptr;
	ConVar* m_pDummyCVar = nullptr;

	char m_szDummyName[128];
	char m_szDummyValue[128];
	char m_szOriginalName[128];
	char m_szOriginalValue[128];
	int m_iOriginalFlags;
};

enum InitReturnVal_t
{
	INIT_FAILED = 0,
	INIT_OK,

	INIT_LAST_VAL,
};

enum AppSystemTier_t
{
	APP_SYSTEM_TIER0 = 0,
	APP_SYSTEM_TIER1,
	APP_SYSTEM_TIER2,
	APP_SYSTEM_TIER3,

	APP_SYSTEM_TIER_OTHER,
};

struct AppSystemInfo_t;

class IAppSystem
{
public:
	virtual void func0() = 0;
	virtual void func1() = 0;
	virtual void func2() = 0;
	virtual void func3() = 0;
	virtual void func4() = 0;
	virtual void func5() = 0;
	virtual void func6() = 0;
	virtual void func7() = 0;
	virtual void func8() = 0;
	virtual void func9() = 0;
};

struct CVarDLLIdentifier_t;

class ICVar : public IAppSystem
{
public:
	virtual void			func10() = 0;
	virtual void			RegisterConCommand(ConVar *pCommandBase) = 0;
	virtual void			UnregisterConCommand(ConVar *pCommandBase) = 0;
	virtual void			func13() = 0;
	virtual ConVar			*FindVar(const char *var_name) = 0;
	virtual void			func15() = 0;
	virtual void			func16() = 0;
	virtual void			func17() = 0;
	virtual void			func18() = 0;
	virtual void			func19() = 0;
	virtual void			func20() = 0;
};

using LocalizeStringIndex_t = unsigned;

class ILocalizeTextQuery
{
public:
	virtual int ComputeTextWidth(const wchar_t* pString) = 0;
};

class ILocalizationChangeCallback
{
public:
	virtual void OnLocalizationChanged() = 0;
};

class ILocalize : public IAppSystem
{
public:
	virtual bool					AddFile(const char* fileName, const char* pPathID = nullptr, bool bIncludeFallbackSearchPaths = false) = 0;
	virtual void					RemoveAll() = 0;
	virtual wchar_t*				Find(const char* tokenName) = 0;
	virtual const wchar_t*			FindSafe(const char* tokenName) = 0;
	virtual int						ConvertANSIToUnicode(const char* ansi, wchar_t* unicode, int unicodeBufferSizeInBytes) = 0;
	virtual int						ConvertUnicodeToANSI(const wchar_t* unicode, char* ansi, int ansiBufferSize) = 0;
	virtual LocalizeStringIndex_t	FindIndex(const char* tokenName) = 0;
	virtual void					ConstructString(wchar_t* unicodeOuput, int unicodeBufferSizeInBytes, const wchar_t* formatString, int numFormatParameters, ...) = 0;
	virtual const char*				GetNameByIndex(LocalizeStringIndex_t index) = 0;
	virtual wchar_t*				GetValueByIndex(LocalizeStringIndex_t index) = 0;
};
