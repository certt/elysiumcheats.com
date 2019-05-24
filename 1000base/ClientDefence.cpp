#ifdef _DEBUG
#else
#include "Main.h"

cSecurity* g_Security = new cSecurity();

#define HOST /*elysiumcheats.com*/Xor<0x74,18,0x06A46E6E>("\x11\x19\x0F\x04\x11\x0C\x17\x18\x14\x18\x1F\x0B\xF3\xAF\xE1\xEC\xE9"+0x06A46E6E).s
#define PATH /*/*/Xor<0x74,2,0x94FE58D6>("\x5B"+0x94FE58D6).s
#define TEXT_KEY /*PtPg8c1Ge5KYiaDy3Qg73NBgLvLWxAWb*/Xor<0x62,33,0x41101FAD>("\x32\x17\x34\x02\x5E\x04\x59\x2E\x0F\x5E\x27\x34\x07\x0E\x34\x08\x41\x22\x13\x42\x45\x39\x3A\x1E\x36\x0D\x30\x2A\x06\x3E\xD7\xE3"+0x41101FAD).s
#define TEXT_IV /*RNuOq6zGR0FTLJ35*/Xor<0x7E,17,0x640474C2>("\x2C\x31\xF5\xCE\xF3\xB5\xFE\xC2\xD4\xB7\xCE\xDD\xC6\xC1\xBF\xB8"+0x640474C2).s

#define BAN_KEY /*3ir5QTKi0R2E4BBoId7EdFRXjZZZCx2w*/Xor<0x2A,33,0x283FDEA1>("\x19\x42\x5E\x18\x7F\x7B\x7B\x58\x02\x61\x06\x70\x02\x75\x7A\x56\x73\x5F\x0B\x78\x5A\x79\x12\x19\x28\x19\x1E\x1F\x05\x3F\x7A\x3E"+0x283FDEA1).s
#define BAN_IV /*S0IBFMKCg1LTqJ8W*/Xor<0x52,17,0xAF361FA7>("\x01\x63\x1D\x17\x10\x1A\x13\x1A\x3D\x6A\x10\x09\x2F\x15\x58\x36"+0xAF361FA7).s

#include <aes.h>
#include <modes.h>
#include <base64.h>
#include <iostream>
#include <windows.h>
#include <WinUser.h>
#include <WinBase.h>
#include <tchar.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"wininet.lib")
#pragma comment(lib, "Advapi32.lib")
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <WinInet.h>
#include <iomanip>
#include <cstdio>

std::string decrypt(const std::string& str_in, const std::string& key, const std::string& iv)
{
	std::string str_out;

	CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryption((byte*)key.c_str(), key.length(), (byte*)iv.c_str());

	CryptoPP::StringSource decryptor(str_in, true,
		new CryptoPP::Base64Decoder(
			new CryptoPP::StreamTransformationFilter(decryption,
				new CryptoPP::StringSink(str_out)
			)
		)
	);
	return str_out;
}

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


std::string GetUrlData(std::string url)
{
	VIRTUALIZER_EAGLE_BLACK_START
	std::string request_data = "";

	HINTERNET hIntSession = InternetOpenA("", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (!hIntSession)
	{
		return request_data;
	}

	HINTERNET hHttpSession = InternetConnectA(hIntSession, HOST, 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);

	if (!hHttpSession)
	{
		return request_data;
	}

	HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", url.c_str()
		, 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	if (!hHttpSession)
	{
		return request_data;
	}

	const char* szHeaders = "Content-Type: text/html\r\nUser-Agent: License";
	char szRequest[1024] = { 0 };

	if (!HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szRequest, strlen(szRequest)))
	{
		return request_data;
	}

	CHAR szBuffer[1024] = { 0 };
	DWORD dwRead = 0;

	while (InternetReadFile(hHttpRequest, szBuffer, sizeof(szBuffer) - 1, &dwRead) && dwRead)
	{
		request_data.append(szBuffer, dwRead);
	}

	InternetCloseHandle(hHttpRequest);
	InternetCloseHandle(hHttpSession);
	InternetCloseHandle(hIntSession);

	return request_data;
	VIRTUALIZER_EAGLE_BLACK_END
}

std::string base64_encode(char const* bytes_to_encode, unsigned int in_len)
{
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--)
	{
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i <4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;
}

std::string StringToHex(const std::string input)
{
	const char* lut = "0123456789ABCDEF";
	size_t len = input.length();
	std::string output = "";

	output.reserve(2 * len);

	for (size_t i = 0; i < len; i++)
	{
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}

	return output;
}

std::string GetHashText(const void * data, const size_t data_size)
{
	HCRYPTPROV hProv = NULL;

	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		return "";
	}

	BOOL hash_ok = FALSE;
	HCRYPTPROV hHash = NULL;

	hash_ok = CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash);

	if (!hash_ok)
	{
		CryptReleaseContext(hProv, 0);
		return "";
	}

	if (!CryptHashData(hHash, static_cast<const BYTE *>(data), data_size, 0))
	{
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return "";
	}

	DWORD cbHashSize = 0, dwCount = sizeof(DWORD);
	if (!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE *)&cbHashSize, &dwCount, 0))
	{
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return "";
	}

	std::vector<BYTE> buffer(cbHashSize);

	if (!CryptGetHashParam(hHash, HP_HASHVAL, reinterpret_cast<BYTE*>(&buffer[0]), &cbHashSize, 0))
	{
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		return "";
	}

	std::ostringstream oss;

	for (std::vector<BYTE>::const_iterator iter = buffer.begin(); iter != buffer.end(); ++iter)
	{
		oss.fill('0');
		oss.width(2);
		oss << std::hex << static_cast<const int>(*iter);
	}

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	return oss.str();
}

std::string GetHwUID()
{
	HW_PROFILE_INFOA hwProfileInfo;
	std::string szHwProfileGuid = "";

	if (GetCurrentHwProfileA(&hwProfileInfo) != NULL)
		szHwProfileGuid = hwProfileInfo.szHwProfileGuid;

	return szHwProfileGuid;
}

DWORD GetVolumeID()
{
	DWORD VolumeSerialNumber;

	BOOL GetVolumeInformationFlag = GetVolumeInformationA(
		"c:\\",
		0,
		0,
		&VolumeSerialNumber,
		0,
		0,
		0,
		0
	);

	if (GetVolumeInformationFlag)
		return VolumeSerialNumber;

	return 0;
}

std::string GetCompUserName(bool User)
{
	std::string CompUserName = "";

	char szCompName[MAX_COMPUTERNAME_LENGTH + 1];
	char szUserName[MAX_COMPUTERNAME_LENGTH + 1];

	DWORD dwCompSize = sizeof(szCompName);
	DWORD dwUserSize = sizeof(szUserName);

	if (GetComputerNameA(szCompName, &dwCompSize))
	{
		CompUserName = szCompName;

		if (User && GetUserNameA(szUserName, &dwUserSize))
		{
			CompUserName = szUserName;
		}
	}

	return CompUserName;
}

std::string GetSerialKey()
{
	std::string SerialKey = "61A345B5496B2";
	std::string CompName = GetCompUserName(false);
	std::string UserName = GetCompUserName(true);

	SerialKey.append(StringToHex(GetHwUID()));
	SerialKey.append("-");
	SerialKey.append(StringToHex(std::to_string(GetVolumeID())));
	SerialKey.append("-");
	SerialKey.append(StringToHex(CompName));
	SerialKey.append("-");
	SerialKey.append(StringToHex(UserName));

	return SerialKey;
}

std::string GetHashSerialKey()
{
	std::string SerialKey = GetSerialKey();
	const void* pData = SerialKey.c_str();
	size_t Size = SerialKey.size();
	std::string Hash = GetHashText(pData, Size);

	for (auto& c : Hash)
	{
		if (c >= 'a' && c <= 'f')
		{
			c = '4';
		}
		else if (c == 'b')
		{
			c = '5';
		}
		else if (c == 'c')
		{
			c = '6';
		}
		else if (c == 'd')
		{
			c = '7';
		}
		else if (c == 'e')
		{
			c = '8';
		}
		else if (c == 'f')
		{
			c = '9';
		}

		c = toupper(c);
	}

	return Hash;
}

std::string GetSerial()
{
	std::string Serial = "";
	std::string HashSerialKey = GetHashSerialKey();

	std::string Serial1 = HashSerialKey.substr(0, 4);
	std::string Serial2 = HashSerialKey.substr(4, 4);
	std::string Serial3 = HashSerialKey.substr(8, 4);
	std::string Serial4 = HashSerialKey.substr(12, 4);

	Serial += Serial1;
	Serial += '-';
	Serial += Serial2;
	Serial += '-';
	Serial += Serial3;
	Serial += '-';
	Serial += Serial4;

	return Serial;
}

bool cSecurity::Glob::License()
{
	VIRTUALIZER_EAGLE_BLACK_START
	std::string UrlRequest3 = PATH;
	UrlRequest3.append("ask.php?getsub=" + GetSerial());
	std::string MainState = GetUrlData(UrlRequest3);

	if (decrypt(MainState, TEXT_KEY, TEXT_IV) == "PbmdBiVsuZRBtI")
	{
		std::string UrlRequest8 = PATH;
		UrlRequest8.append("ask.php?log=" + GetSerial() + "&id=1");
		GetUrlData(UrlRequest8);
		return true;
	}
	return false;
	VIRTUALIZER_EAGLE_BLACK_END
}

bool cSecurity::Glob::IsBanned()
{
	VIRTUALIZER_EAGLE_BLACK_START
	std::string BannedReq = PATH;
	BannedReq.append("ask.php?isbanned=" + GetSerial());
	std::string Banned = GetUrlData(BannedReq);

	if (decrypt(Banned, BAN_KEY, BAN_IV) == "AOywtAbQDTIHiu")
		return true;
	
	return false;
	VIRTUALIZER_EAGLE_BLACK_END
}


void cSecurity::Glob::Ban()
{
	VIRTUALIZER_EAGLE_BLACK_START
	std::string UrlRequest7 = PATH;
	UrlRequest7.append("ask.php?banhwid=" + GetSerial());
	GetUrlData(UrlRequest7);
	VIRTUALIZER_EAGLE_BLACK_END
}

typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _LDR_MODULE_DUMMY_
{
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID BaseAddress;

	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	SHORT LoadCount;
	SHORT TlsIndex;
	LIST_ENTRY HashTableEntry;
	ULONG TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

typedef struct _PEB_LDR_DATA_DUMMY_
{
	ULONG Length;
	UCHAR Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID EntryInProgress;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct PEB_DUMMY_
{
	PVOID Dummy1;
	PVOID Dummy2;
	PVOID Dummy3;
	PPEB_LDR_DATA LDR_Data;
} PEB_DUMMY, *PPEB_DUMMY;

typedef struct _CLIENT_ID
{
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _RTL_DRIVE_LETTER_CURDIR
{
	USHORT Flags;
	USHORT Length;
	ULONG TimeStamp;
	UNICODE_STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS
{
	ULONG MaximumLength;
	ULONG Length;
	ULONG Flags;
	ULONG DebugFlags;
	PVOID ConsoleHandle;
	ULONG ConsoleFlags;
	HANDLE StdInputHandle;
	HANDLE StdOutputHandle;
	HANDLE StdErrorHandle;
	UNICODE_STRING CurrentDirectoryPath;
	HANDLE CurrentDirectoryHandle;
	UNICODE_STRING DllPath;
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
	PVOID Environment;
	ULONG StartingPositionLeft;
	ULONG StartingPositionTop;
	ULONG Width;
	ULONG Height;
	ULONG CharWidth;
	ULONG CharHeight;
	ULONG ConsoleTextAttributes;
	ULONG WindowFlags;
	ULONG ShowWindowFlags;
	UNICODE_STRING WindowTitle;
	UNICODE_STRING DesktopName;
	UNICODE_STRING ShellInfo;
	UNICODE_STRING RuntimeData;
	RTL_DRIVE_LETTER_CURDIR DLCurrentDirectory[0x20];
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef void(*PPEBLOCKROUTINE)(PVOID PebLock);

typedef struct _PEB_FREE_BLOCK
{
	_PEB_FREE_BLOCK* Next;
	DWORD Size;
} PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;

typedef struct _PEB
{
	BOOLEAN InheritedAddressSpace;
	BOOLEAN ReadImageFileExecOptions;
	BOOLEAN BeingDebugged;
	BOOLEAN Spare;
	HANDLE Mutant;
	PVOID ImageBaseAddress;
	PPEB_LDR_DATA LoaderData;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
	PVOID SubSystemData;
	PVOID ProcessHeap;
	PVOID FastPebLock;
	PPEBLOCKROUTINE FastPebLockRoutine;
	PPEBLOCKROUTINE FastPebUnlockRoutine;
	ULONG EnvironmentUpdateCount;
	PVOID* KernelCallbackTable;
	PVOID EventLogSection;
	PVOID EventLog;
	PPEB_FREE_BLOCK FreeList;
	ULONG TlsExpansionCounter;
	PVOID TlsBitmap;
	ULONG TlsBitmapBits[0x2];
	PVOID ReadOnlySharedMemoryBase;
	PVOID ReadOnlySharedMemoryHeap;
	PVOID* ReadOnlyStaticServerData;
	PVOID AnsiCodePageData;
	PVOID OemCodePageData;
	PVOID UnicodeCaseTableData;
	ULONG NumberOfProcessors;
	ULONG NtGlobalFlag;
	BYTE Spare2[0x4];
	LARGE_INTEGER CriticalSectionTimeout;
	ULONG HeapSegmentReserve;
	ULONG HeapSegmentCommit;
	ULONG HeapDeCommitTotalFreeThreshold;
	ULONG HeapDeCommitFreeBlockThreshold;
	ULONG NumberOfHeaps;
	ULONG MaximumNumberOfHeaps;
	PVOID** ProcessHeaps;
	PVOID GdiSharedHandleTable;
	PVOID ProcessStarterHelper;
	PVOID GdiDCAttributeList;
	PVOID LoaderLock;
	ULONG OSMajorVersion;
	ULONG OSMinorVersion;
	ULONG OSBuildNumber;
	ULONG OSPlatformId;
	ULONG ImageSubSystem;
	ULONG ImageSubSystemMajorVersion;
	ULONG ImageSubSystemMinorVersion;
	ULONG GdiHandleBuffer[0x22];
	ULONG PostProcessInitRoutine;
	ULONG TlsExpansionBitmap;
	BYTE TlsExpansionBitmapBits[0x80];
	ULONG SessionId;
} PEB, *PPEB;

typedef struct _TEB
{
	NT_TIB Tib;
	PVOID EnvironmentPointer;
	CLIENT_ID Cid;
	PVOID ActiveRpcInfo;
	PVOID ThreadLocalStoragePointer;
	PPEB Peb;
	ULONG LastErrorValue;
	ULONG CountOfOwnedCriticalSections;
	PVOID CsrClientThread;
	PVOID Win32ThreadInfo;
	ULONG Win32ClientInfo[0x1F];
	PVOID WOW32Reserved;
	ULONG CurrentLocale;
	ULONG FpSoftwareStatusRegister;
	PVOID SystemReserved1[0x36];
	PVOID Spare1;
	ULONG ExceptionCode;
	ULONG SpareBytes1[0x28];
	PVOID SystemReserved2[0xA];
	ULONG GdiRgn;
	ULONG GdiPen;
	ULONG GdiBrush;
	CLIENT_ID RealClientId;
	PVOID GdiCachedProcessHandle;
	ULONG GdiClientPID;
	ULONG GdiClientTID;
	PVOID GdiThreadLocaleInfo;
	PVOID UserReserved[5];
	PVOID GlDispatchTable[0x118];
	ULONG GlReserved1[0x1A];
	PVOID GlReserved2;
	PVOID GlSectionInfo;
	PVOID GlSection;
	PVOID GlTable;
	PVOID GlCurrentRC;
	PVOID GlContext;
	NTSTATUS LastStatusValue;
	UNICODE_STRING StaticUnicodeString;
	WCHAR StaticUnicodeBuffer[0x105];
	PVOID DeallocationStack;
	PVOID TlsSlots[0x40];
	LIST_ENTRY TlsLinks;
	PVOID Vdm;
	PVOID ReservedForNtRpc;
	PVOID DbgSsReserved[0x2];
	ULONG HardErrorDisabled;
	PVOID Instrumentation[0x10];
	PVOID WinSockData;
	ULONG GdiBatchCount;
	ULONG Spare2;
	ULONG Spare3;
	ULONG Spare4;
	PVOID ReservedForOle;
	ULONG WaitingOnLoaderLock;
	PVOID StackCommit;
	PVOID StackCommitMax;
	PVOID StackReserved;
} TEB, *PTEB;


bool Int2DCheck()
{
	__try
	{
		__asm
		{
			int 0x2d
			xor eax, eax
			add eax, 2
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}

	return true;
}

bool IsDbgPresentPrefixCheck()
{
	__try
	{
		__asm __emit 0xF3 // 0xF3 0x64 disassembles as PREFIX REP:
		__asm __emit 0x64
		__asm __emit 0xF1 // One byte INT 1
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}

	return true;
}

bool checkGlobalFlags()
{
	DWORD NtGlobalFlags;
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax + 68h]
		mov NtGlobalFlags, eax
	}

	if (NtGlobalFlags & 0x70)
		return true;

	return false;
}

PPEB_DUMMY __declspec(naked) GetPEB(void)
{
	_asm
	{
		mov eax, fs:[0x30];
		retn;
	}
}

DWORD cSecurity::HideMod(HMODULE mod)
{
	DWORD MBA;
	DWORD MBS;
	PTEB pTEB;
	PPEB_LDR_DATA pLDR;
	PLIST_ENTRY pM, pCM;
	PLDR_MODULE pMM;
	int M = 0, L = 0, I = 0, temp = 0;
	IMAGE_DOS_HEADER *DOSH = (IMAGE_DOS_HEADER*)mod;
	IMAGE_NT_HEADERS *NTH = NULL;
	DWORD OP;
	__asm
	{
		xor eax, eax;
		mov eax, fs:[0x18];
		mov pTEB, eax;
	}
	pLDR = pTEB->Peb->LoaderData;
	if (DOSH->e_magic != IMAGE_DOS_SIGNATURE) return 0;
	NTH = ((PIMAGE_NT_HEADERS)((DWORD)(DOSH)+(DWORD)(DOSH->e_lfanew)));
	if (NTH->Signature != IMAGE_NT_SIGNATURE) return 0;
	MBS = NTH->OptionalHeader.SizeOfImage;
	MBA = NTH->OptionalHeader.ImageBase;

	if (!pLDR) return 1;
	for (int m = 0; m <= 2; m++)
	{
		if (m == 0) pM = &(pLDR->InMemoryOrderModuleList);
		if (m == 1) pM = &(pLDR->InLoadOrderModuleList);
		if (m == 2) pM = &(pLDR->InInitializationOrderModuleList);
		for (pCM = pM->Flink; pCM != pM; pCM = pCM->Flink)
		{
			if (m == 0) pMM = CONTAINING_RECORD(pCM, LDR_MODULE, InMemoryOrderModuleList);
			if (m == 1) pMM = CONTAINING_RECORD(pCM, LDR_MODULE, InLoadOrderModuleList);
			if (m == 2) pMM = CONTAINING_RECORD(pCM, LDR_MODULE, InInitializationOrderModuleList);
			if ((DWORD)pMM->BaseAddress == MBA && (DWORD)pMM->SizeOfImage == MBS)
			{
				pCM->Blink->Flink = pCM->Flink;
				pCM->Flink->Blink = pCM->Blink;
			}
		}
	}
	VirtualProtect((LPVOID)DOSH, NTH->OptionalHeader.SizeOfHeaders, PAGE_EXECUTE_READWRITE, &OP);
	memset((LPVOID)DOSH, 0, NTH->OptionalHeader.SizeOfHeaders);
	VirtualProtect((LPVOID)DOSH, NTH->OptionalHeader.SizeOfHeaders, OP, &OP);
	return 3;
}


void cSecurity::HideModuleFromPEB(HINSTANCE hInstance)
{
	PPEB_DUMMY PEB = GetPEB();

	PLIST_ENTRY FirstEntryInLoadOrder = (PLIST_ENTRY)&PEB->LDR_Data->InLoadOrderModuleList;
	PLIST_ENTRY FirstEntryInMemoryOrder = (PLIST_ENTRY)&PEB->LDR_Data->InMemoryOrderModuleList;
	PLIST_ENTRY FirstEntryInInitOrder = (PLIST_ENTRY)&PEB->LDR_Data->InInitializationOrderModuleList;

	for (PLIST_ENTRY TempEntry = FirstEntryInLoadOrder->Flink; TempEntry != FirstEntryInLoadOrder; TempEntry = TempEntry->Flink)
	{
		PLDR_MODULE TempModule = (PLDR_MODULE)((DWORD)TempEntry - 0 * sizeof(LIST_ENTRY));
		if (TempModule->BaseAddress == hInstance)
		{
			TempEntry->Blink->Flink = TempEntry->Flink;
			TempEntry->Flink->Blink = TempEntry->Blink;
			break;
		}
	}

	for (PLIST_ENTRY TempEntry = FirstEntryInMemoryOrder->Flink; TempEntry != FirstEntryInMemoryOrder; TempEntry = TempEntry->Flink)
	{
		PLDR_MODULE TempModule = (PLDR_MODULE)((DWORD)TempEntry - 1 * sizeof(LIST_ENTRY));
		if (TempModule->BaseAddress == hInstance)
		{
			TempEntry->Blink->Flink = TempEntry->Flink;
			TempEntry->Flink->Blink = TempEntry->Blink;
			break;
		}
	}

	for (PLIST_ENTRY TempEntry = FirstEntryInInitOrder->Flink; TempEntry != FirstEntryInInitOrder; TempEntry = TempEntry->Flink)
	{
		PLDR_MODULE TempModule = (PLDR_MODULE)((DWORD)TempEntry - 2 * sizeof(LIST_ENTRY));
		if (TempModule->BaseAddress == hInstance)
		{
			TempEntry->Blink->Flink = TempEntry->Flink;
			TempEntry->Flink->Blink = TempEntry->Blink;
			break;
		}
	}
}
void cSecurity::RemovePeHeader(DWORD ModuleBase)
{
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)ModuleBase;
	PIMAGE_NT_HEADERS pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pDosHeader + (DWORD)pDosHeader->e_lfanew);

	if (pNTHeader->Signature != IMAGE_NT_SIGNATURE)
		return;

	if (pNTHeader->FileHeader.SizeOfOptionalHeader)
	{
		DWORD Protect;
		WORD Size = pNTHeader->FileHeader.SizeOfOptionalHeader;
		VirtualProtect((void*)ModuleBase, Size, PAGE_EXECUTE_READWRITE, &Protect);
		RtlZeroMemory((void*)ModuleBase, Size);
		VirtualProtect((void*)ModuleBase, Size, Protect, &Protect);
	}
}
void cSecurity::HideModule(HANDLE hModule)
{
	PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hModule;
	if (pDOSHeader->e_magic == IMAGE_DOS_SIGNATURE)
	{
		PIMAGE_NT_HEADERS pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pDOSHeader + (DWORD)pDOSHeader->e_lfanew);
		if (pNTHeader->Signature == IMAGE_NT_SIGNATURE)
		{
			DWORD dwOld, dwSize = pNTHeader->OptionalHeader.SizeOfHeaders;
			if (VirtualProtect((LPVOID)pDOSHeader, dwSize, PAGE_READWRITE, &dwOld))
			{
				memset((void*)pDOSHeader, 0, dwSize);
				VirtualProtect((LPVOID)pDOSHeader, dwSize, dwOld, &dwOld);
			}
		}
		_TEB *pTeb = nullptr;
		_asm
		{
			mov eax, fs:[0x18]
			mov pTeb, eax
		}
		PLIST_ENTRY pList = &pTeb->Peb->LoaderData->InLoadOrderModuleList;
		for (PLIST_ENTRY pEntry = pList->Flink; pEntry != pList; pEntry = pEntry->Flink)
		{
			PLDR_MODULE pModule = (PLDR_MODULE)pEntry;
			if (pModule->BaseAddress == hModule)
			{
				pEntry = &pModule->InLoadOrderModuleList; pEntry->Blink->Flink = pEntry->Flink; pEntry->Flink->Blink = pEntry->Blink;
				memset(pEntry, 0, sizeof(LIST_ENTRY));
				pEntry = &pModule->InMemoryOrderModuleList; pEntry->Blink->Flink = pEntry->Flink; pEntry->Flink->Blink = pEntry->Blink;
				memset(pEntry, 0, sizeof(LIST_ENTRY));
				pEntry = &pModule->InInitializationOrderModuleList; pEntry->Blink->Flink = pEntry->Flink; pEntry->Flink->Blink = pEntry->Blink;
				memset(pEntry, 0, sizeof(LIST_ENTRY));
				pEntry = &pModule->HashTableEntry; pEntry->Blink->Flink = pEntry->Flink; pEntry->Flink->Blink = pEntry->Blink;
				memset(pEntry, 0, sizeof(LIST_ENTRY));
				memset(pModule->FullDllName.Buffer, 0, pModule->FullDllName.Length);
				memset(pModule, 0, sizeof(LDR_MODULE));
				break;
			}
		}
	}
}
void cSecurity::HideModuleXta(HINSTANCE hModule)
{
	DWORD dwPEB_LDR_DATA = 0;

	_asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h]
			mov eax, [eax + 0Ch]
			mov dwPEB_LDR_DATA, eax
			mov esi, [eax + 0Ch]
			mov edx, [eax + 10h]

			LoopInLoadOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [eax + 18h]
			cmp ecx, hModule
			jne SkipA
			mov ebx, [eax]
			mov ecx, [eax + 4]
			mov[ecx], ebx
			mov[ebx + 4], ecx
			jmp InMemoryOrderModuleList
			SkipA :
		cmp edx, esi
			jne LoopInLoadOrderModuleList

			InMemoryOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 14h]
			mov edx, [eax + 18h]

			LoopInMemoryOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [eax + 10h]
			cmp ecx, hModule
			jne SkipB
			mov ebx, [eax]
			mov ecx, [eax + 4]
			mov[ecx], ebx
			mov[ebx + 4], ecx
			jmp InInitializationOrderModuleList
			SkipB :
		cmp edx, esi
			jne LoopInMemoryOrderModuleList

			InInitializationOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 1Ch]
			mov edx, [eax + 20h]

			LoopInInitializationOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [eax + 08h]
			cmp ecx, hModule
			jne SkipC
			mov ebx, [eax]
			mov ecx, [eax + 4]
			mov[ecx], ebx
			mov[ebx + 4], ecx
			jmp Finished
			SkipC :
		cmp edx, esi
			jne LoopInInitializationOrderModuleList

			Finished :
		popfd;
		popad;
	}
}

bool cSecurity::DestroyModuleHeader(HMODULE hModule)
{
	DWORD dwStartOffset = (DWORD)hModule;

	IMAGE_DOS_HEADER *pDosHeader = (PIMAGE_DOS_HEADER)dwStartOffset;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return false;

	IMAGE_NT_HEADERS *pNtHeader = (PIMAGE_NT_HEADERS)(dwStartOffset + pDosHeader->e_lfanew);
	if (pNtHeader->Signature != IMAGE_NT_SIGNATURE)
		return false;

	DWORD dwOldProtection = NULL;
	if (!VirtualProtect((PVOID)hModule, pNtHeader->OptionalHeader.SizeOfHeaders, PAGE_EXECUTE_READWRITE, &dwOldProtection))
		return false;

	ZeroMemory((PVOID)hModule, pNtHeader->OptionalHeader.SizeOfHeaders);
	VirtualProtect((PVOID)hModule, pNtHeader->OptionalHeader.SizeOfHeaders, dwOldProtection, &dwOldProtection);

	return true;
}
#endif