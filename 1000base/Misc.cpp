#include "Main.h"

Globals* g_Globals = new Globals();
Utils* g_Utils = new Utils();
Interfaces* g_Interfaces = new Interfaces();
ImGuiRendering* g_ImRender = new ImGuiRendering();
Visuals* g_Visuals = new Visuals();
CMenu* g_Menu = new CMenu();
CVars* g_Vars = new CVars();
lAimbot* g_Legit = new lAimbot();
lTrigger* g_Trigger = new lTrigger();
pChanger* g_Changer = new pChanger();
IClientRenderable* g_ClientRenderable;
playerMatrix playerStruct[64];