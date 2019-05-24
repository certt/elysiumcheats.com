#include "Main.h"

IBaseClientDLL* I::Client = nullptr;
IVEngineClient* I::Engine = nullptr;
IClientEntityList* I::EntityList = nullptr;
IGlobalVars* I::Globals = nullptr;
IClientMode* I::ClientMode = nullptr;
IVModelInfo* I::ModelInfo = nullptr;
IEngineSound* I::EngineSound = nullptr;
IVRenderView* I::RenderView = nullptr;
IVModelRender* I::ModelRender = nullptr;
IMaterialSystem* I::MaterialSystem = nullptr;
IEngineTrace* I::EngineTrace = nullptr;
IGameEventManager2*	I::EventManager = nullptr;
ILocalize* I::Localize = nullptr;
ISurface* I::Surface = nullptr;

bool Interfaces::InitInterfaces()
{
	I::Client = g_Interfaces->get_interface<IBaseClientDLL*>("client_panorama.dll", "VClient018");
	I::Engine = g_Interfaces->get_interface<IVEngineClient*>("engine.dll", "VEngineClient014");
	I::EntityList = g_Interfaces->get_interface<IClientEntityList*>("client_panorama.dll", "VClientEntityList003");
	I::ModelInfo = g_Interfaces->get_interface<IVModelInfo*>("engine.dll", "VModelInfoClient004");
	I::EngineSound = g_Interfaces->get_interface<IEngineSound*>("engine.dll", "IEngineSoundClient003");
	I::RenderView = g_Interfaces->get_interface<IVRenderView*>("engine.dll", "VEngineRenderView014");
	I::EventManager = g_Interfaces->get_interface<IGameEventManager2*>("engine.dll", "GAMEEVENTSMANAGER002");
	I::ModelRender = g_Interfaces->get_interface<IVModelRender*>("engine.dll", "VEngineModel016");
	I::EngineTrace = g_Interfaces->get_interface<IEngineTrace*>("engine.dll", "EngineTraceClient004");
	I::MaterialSystem = g_Interfaces->get_interface<IMaterialSystem*>("materialsystem.dll", "VMaterialSystem080");
	I::Localize = g_Interfaces->get_interface<ILocalize*>("localize.dll", "Localize_001");
	I::Surface = g_Interfaces->get_interface<ISurface*>("vguimatsurface.dll", "VGUI_Surface031");

	I::ClientMode = **reinterpret_cast<IClientMode***> ((*reinterpret_cast<uintptr_t**>(I::Client))[10] + 0x5u);
	I::Globals = **reinterpret_cast<IGlobalVars***>((*reinterpret_cast<uintptr_t**>(I::Client))[0] + 0x1Bu);

	return true;
}