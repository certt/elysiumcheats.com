#pragma once

#include "CHandle.h"
#include "IClientNetworkable.h"
#include "IBaseClientDLL.h"
#include "IVEngineClient.h"
#include "IVModelInfo.h"
#include "IEngineSound.h"
#include "IVRenderView.h"

#include "IMaterial.h"
#include "IMaterialSystem.h"
#include "IVModelRender.h"
#include "Trace.h"
#include "IGameEvent.h"
#include "ICvar.h"

namespace I {
	extern IBaseClientDLL* Client;
	extern IVEngineClient* Engine;
	extern IVModelInfo* ModelInfo;
	extern IClientEntityList* EntityList;
	extern IGlobalVars* Globals;
	extern IClientMode* ClientMode;
	extern IEngineSound* EngineSound;
	extern ILocalize* Localize;
	extern IVRenderView* RenderView;
	extern IVModelRender* ModelRender;
	extern IMaterialSystem* MaterialSystem;
	extern IEngineTrace* EngineTrace;
	extern IGameEventManager2* EventManager;
	extern ISurface* Surface;
}

class Interfaces {
public:
	template <typename t = void*>
	t get_interface(const char* module_name, const char* interface_name) {
		using original_fn = void*(*)(const char*, int*);
		original_fn create_interface = (original_fn)GetProcAddress(GetModuleHandleA(module_name), "CreateInterface");
		return reinterpret_cast< t >(create_interface(interface_name, nullptr));
	}
	
	bool InitInterfaces();

private:
}; extern Interfaces* g_Interfaces;