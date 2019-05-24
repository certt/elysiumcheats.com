#pragma once

#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin)

#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include <time.h>
#include <random>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <set>
#include <map>
#include <unordered_map>
#include <memory>
#include <thread>
#include <array>
#include <deque>
#include <intrin.h>
#include <atomic>
#include <mutex>
#include "Vector.h"
#include "xor.h"

#include <lmcons.h>
#include <vector>
#include <shlobj.h>
#include <shlwapi.h>
#include <chrono>

#pragma warning(disable : 4244)
#pragma warning(disable : 4227)
#pragma warning(disable : 4172)
#pragma warning(disable : 4307)
#pragma warning(disable : 4996)
#include "XorSTR.h"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "cs_strenc.h"
#include "imgui.h"
#include "imgui_dx9.h"
#include "VMatrix.h"
#include "Color.h"
#include "ImRender.h"
#include "Math.h"
#include "Vars.h"
#include "NetVarManager.h"
#include "Misc.h"
#include "Utils.h"
#include "Interfaces.h"
#include "Globals.h"
#include "VirtualizerSDK.h"

#include "IEntity.h"
#include "GlowManager.h"