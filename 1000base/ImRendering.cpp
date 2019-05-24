#include "Main.h"

ImDrawData _drawData;
ImDrawList* _drawList;
DWORD dwOld_D3DRS_SRGBWRITEENABLE;
DWORD dwOld_D3DRS_COLORWRITEENABLE;

void __stdcall ImGuiRendering::CreateObjects(IDirect3DDevice9* pDevice)
{
	_drawList = new ImDrawList();
	ImGui_ImplDX9_CreateDeviceObjects();
}

void __stdcall ImGuiRendering::InvalidateObjects()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	if (_drawList)
		delete _drawList;
	_drawList = nullptr;
}

void ImGuiStyle_setup()
{
	VIRTUALIZER_EAGLE_BLACK_START
	if (I::Engine->GetEngineBuildNumber() != 13672)
		exit(GetTickCount());
	VIRTUALIZER_EAGLE_BLACK_END
}

void __stdcall ImGuiRendering::SetupPresent(IDirect3DDevice9* device)
{
	g_Menu->initializeskins();
	Hooks::AnimationFixHook();
	g_Menu->ReadCFG();
	ImGui_ImplDX9_Init(g_Globals->CSGOWindow, device);

	std::string ESPfont, MENUfont;
	ESPfont = std::string(g_Vars->Menu.FontFolder) + std::string(g_Vars->Menu.ESPFont) + strenc(".ttf");
	MENUfont = std::string(g_Vars->Menu.FontFolder) + std::string(g_Vars->Menu.MenuFont) + strenc(".ttf");

	if(g_Vars->Menu.ChangeESPFont)
		g_Globals->ESP_MAIN = ImGui::GetIO().Fonts->AddFontFromFileTTF(ESPfont.c_str(), 18.0f);
	else
		g_Globals->ESP_MAIN = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(_compressed_data_base85, 18.0f);

	if (g_Vars->Menu.ChangeMenuFont)
	{
		g_Globals->MENU_FONT = ImGui::GetIO().Fonts->AddFontFromFileTTF(MENUfont.c_str(), 18.0f);
		g_Globals->MENU_FONT_TABS = ImGui::GetIO().Fonts->AddFontFromFileTTF(MENUfont.c_str(), 24.0f);
		g_Globals->MENU_FONT_SUBTABS = ImGui::GetIO().Fonts->AddFontFromFileTTF(MENUfont.c_str(), 21.0f);
	}
	else
	{
		g_Globals->MENU_FONT = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(robotico, 18.0f);
		g_Globals->MENU_FONT_TABS = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(robotico, 24.0f);
		g_Globals->MENU_FONT_SUBTABS = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(robotico, 21.0f);
	}

	g_Globals->WEAP_ICON = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(icon_font, 32.0f);

	g_ImRender->CreateObjects(device);
	VIRTUALIZER_EAGLE_BLACK_START
	
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(0.12f, 0.11f, 0.11f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.12f, 0.11f, 0.11f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.26f, 0.81f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.26f, 0.81f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.26f, 0.81f, 0.58f, 1.00f);
	ImGuiStyle_setup();
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.27f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.80f, 0.27f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.80f, 0.27f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.59f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.17f, 0.17f, 0.17f, 0.59f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.02f, 0.60f, 0.22f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.17f, 0.17f, 0.17f, 0.59f);
	style.Colors[ImGuiCol_MainColor] = ImVec4(0.80f, 0.27f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ComboSelectedText] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

	style.WindowRounding = 0.f;
	style.FramePadding = ImVec2(4, 1);
	style.ScrollbarSize = 10.f;
	style.ScrollbarRounding = 0.f;
	style.GrabMinSize = 5.f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.25f);

	g_Globals->RenderInit = true;
	VIRTUALIZER_EAGLE_BLACK_END
}

void __stdcall ImGuiRendering::EndPresent(IDirect3DDevice9* pDevice)
{
	ImGui::Render();
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, dwOld_D3DRS_SRGBWRITEENABLE);
}

void __stdcall ImGuiRendering::PreRender(IDirect3DDevice9* device)
{
	if (!g_Globals->RenderInit)
		SetupPresent(device);

	device->GetRenderState(D3DRS_SRGBWRITEENABLE, &dwOld_D3DRS_SRGBWRITEENABLE);
	device->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	device->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	device->SetSamplerState(NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	device->SetSamplerState(NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	device->SetSamplerState(NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
	device->SetSamplerState(NULL, D3DSAMP_SRGBTEXTURE, NULL);
	ImGui::GetIO().MouseDrawCursor = g_Vars->Menu.Opened;
	ImGui_ImplDX9_NewFrame();

	_drawData.Valid = false;
	_drawList->Clear();
	_drawList->PushClipRectFullScreen();
}

void __stdcall ImGuiRendering::PostRender(IDirect3DDevice9* device)
{
	if (!_drawList->VtxBuffer.empty()) {
		_drawData.Valid = true;
		_drawData.CmdLists = &_drawList;
		_drawData.CmdListsCount = 1;
		_drawData.TotalVtxCount = _drawList->VtxBuffer.Size;
		_drawData.TotalIdxCount = _drawList->IdxBuffer.Size;
	}

	ImGui_ImplDX9_RenderDrawLists(&_drawData);
}

void ImGuiRendering::DrawRectFilled(float x1, float y1, float x2, float y2, Color clr)
{
	_drawList->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), clr.GetU32());
}

void ImGuiRendering::DrawRectFilledMulti(float x1, float y1, float x2, float y2, Color clr1, Color clr2, Color clr3, Color clr4)
{
	_drawList->AddRectFilledMultiColor(ImVec2(x1, y1), ImVec2(x2, y2), clr1.GetU32(), clr2.GetU32(), clr3.GetU32(), clr4.GetU32());
}

void ImGuiRendering::DrawString(ImFont* font, float font_size, int flag, float x, float y, Color color, bool with_box, bool Enemy, const char* message ...)
{
	char output[1024] = {};
	va_list args;
	va_start(args, message);
	vsprintf_s(output, message, args);
	va_end(args);
	_drawList->PushTextureID(font->ContainerAtlas->TexID);
	ImGui::PushFont(font);
	auto coord = ImVec2(x, y);
	auto size = font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, output);

	if (flag == 1 || flag == 2)
		coord.x -= size.x / 2;

	if (with_box)
	{
		DrawRectFilled(coord.x - 5.0f, coord.y - 1.0f, coord.x + size.x + 5.0f, coord.y + size.y + 2.0f, Color(45, 45, 45, 120));
		DrawLine(coord.x - 5.0f, coord.y - 1.0f, coord.x + size.x + 5.0f, coord.y - 1.0f, Enemy ? Color(int(g_Vars->Colors.InfoBoxE[0] * 255.f), int(g_Vars->Colors.InfoBoxE[1] * 255.f), int(g_Vars->Colors.InfoBoxE[2] * 255.f)) : Color(int(g_Vars->Colors.InfoBoxT[0] * 255.f), int(g_Vars->Colors.InfoBoxT[1] * 255.f), int(g_Vars->Colors.InfoBoxT[2] * 255.f)), 1.5f);
	}

	if (flag == 2)
		_drawList->AddText(coord, font_size + 0.75f, Color::Black().GetU32(), output);
	if (flag == 1)
	{
		auto coord_out = ImVec2{ coord.x + 1.f, coord.y + 1.f };
		_drawList->AddText(coord_out, font_size, ImColor{ 0.f, 0.f, 0.f, 1.f }, output);
	}
	_drawList->AddText(coord, font_size, color.GetU32(), output);
	ImGui::PopFont();
}

void SinCos(float a, float* s, float*c)
{
	*s = sin(a);
	*c = cos(a);
}

void AngleVectors(const QAngle &angles, Vector& forward, Vector& right, Vector& up)
{
	float sr, sp, sy, cr, cp, cy;

	SinCos(DEG2RAD(angles[1]), &sy, &cy);
	SinCos(DEG2RAD(angles[0]), &sp, &cp);
	SinCos(DEG2RAD(angles[2]), &sr, &cr);

	forward.x = (cp * cy);
	forward.y = (cp * sy);
	forward.z = (-sp);
	right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
	right.y = (-1 * sr * sp * sy + -1 * cr *  cy);
	right.z = (-1 * sr * cp);
	up.x = (cr * sp * cy + -sr * -sy);
	up.y = (cr * sp * sy + -sr * cy);
	up.z = (cr * cp);
}

void ImGuiRendering::Draw3DCube(float scalar, QAngle angles, Vector middle_origin, Color outline)
{
	Vector forward, right, up;
	AngleVectors(angles, forward, right, up);

	Vector points[8];
	points[0] = middle_origin - (right * scalar) + (up * scalar) - (forward * scalar); // BLT
	points[1] = middle_origin + (right * scalar) + (up * scalar) - (forward * scalar); // BRT
	points[2] = middle_origin - (right * scalar) - (up * scalar) - (forward * scalar); // BLB
	points[3] = middle_origin + (right * scalar) - (up * scalar) - (forward * scalar); // BRB

	points[4] = middle_origin - (right * scalar) + (up * scalar) + (forward * scalar); // FLT
	points[5] = middle_origin + (right * scalar) + (up * scalar) + (forward * scalar); // FRT
	points[6] = middle_origin - (right * scalar) - (up * scalar) + (forward * scalar); // FLB
	points[7] = middle_origin + (right * scalar) - (up * scalar) + (forward * scalar); // FRB

	Vector points_screen[8];
	for (int i = 0; i < 8; i++)
		if (!g_Utils->WorldToScreen(points[i], points_screen[i]))
			return;

	//g_Surface->DrawSetColor(outline);

	// Back frame
	DrawLine(points_screen[0].x, points_screen[0].y, points_screen[1].x, points_screen[1].y, outline.GetU32(), 1.5f);
	DrawLine(points_screen[0].x, points_screen[0].y, points_screen[2].x, points_screen[2].y, outline.GetU32(), 1.5f);
	DrawLine(points_screen[3].x, points_screen[3].y, points_screen[1].x, points_screen[1].y, outline.GetU32(), 1.5f);
	DrawLine(points_screen[3].x, points_screen[3].y, points_screen[2].x, points_screen[2].y, outline.GetU32(), 1.5f);

	// Frame connector
	DrawLine(points_screen[0].x, points_screen[0].y, points_screen[4].x, points_screen[4].y, outline.GetU32(), 1.5f);
	DrawLine(points_screen[1].x, points_screen[1].y, points_screen[5].x, points_screen[5].y, outline.GetU32(), 1.5f);
	DrawLine(points_screen[2].x, points_screen[2].y, points_screen[6].x, points_screen[6].y, outline.GetU32(), 1.5f);
	DrawLine(points_screen[3].x, points_screen[3].y, points_screen[7].x, points_screen[7].y, outline.GetU32(), 1.5f);

	// Front frame
	DrawLine(points_screen[4].x, points_screen[4].y, points_screen[5].x, points_screen[5].y, outline.GetU32(), 1.5f);
	DrawLine(points_screen[4].x, points_screen[4].y, points_screen[6].x, points_screen[6].y, outline.GetU32(), 1.5f);
	DrawLine(points_screen[7].x, points_screen[7].y, points_screen[5].x, points_screen[5].y, outline.GetU32(), 1.5f);
	DrawLine(points_screen[7].x, points_screen[7].y, points_screen[6].x, points_screen[6].y, outline.GetU32(), 1.5f);
}

void ImGuiRendering::DrawRect(float x1, float y1, float x2, float y2, Color clr, float thickness)
{
	_drawList->AddRect(ImVec2(x1, y1), ImVec2(x2, y2), clr.GetU32(), 0.0F, -1, thickness);
}

void ImGuiRendering::DrawEspBox(Vector leftUpCorn, Vector rightDownCorn, Color clr, float width)
{
	_drawList->AddRect(ImVec2(leftUpCorn.x - 0.5f, leftUpCorn.y - 0.5f), ImVec2(rightDownCorn.x - 0.5f, rightDownCorn.y - 0.5f), Color::Black().GetU32(), 1.0F, -1, 2.5f);
	_drawList->AddRect(ImVec2(leftUpCorn.x, leftUpCorn.y), ImVec2(rightDownCorn.x, rightDownCorn.y), clr.GetU32(), 1.0F, -1, 2.0f);
}

void ImGuiRendering::DrawCorner(Vector leftUpCorn, Vector rightUpCorn, Vector leftDownCorn, Vector rightDownCorn, Color clr, float width)
{
	int edge = (rightUpCorn.x - leftUpCorn.x) / 3;

	_drawList->AddLine(ImVec2(rightUpCorn.x, rightUpCorn.y), ImVec2(rightUpCorn.x, rightUpCorn.y + edge), clr.GetU32(), width);
	_drawList->AddLine(ImVec2(rightUpCorn.x, rightUpCorn.y), ImVec2(rightUpCorn.x - edge, rightUpCorn.y), clr.GetU32(), width);
	_drawList->AddLine(ImVec2(leftUpCorn.x, leftUpCorn.y), ImVec2(leftUpCorn.x, leftUpCorn.y + edge), clr.GetU32(), width);
	_drawList->AddLine(ImVec2(leftUpCorn.x, leftUpCorn.y), ImVec2(leftUpCorn.x + edge, leftUpCorn.y), clr.GetU32(), width);
	_drawList->AddLine(ImVec2(rightDownCorn.x, rightDownCorn.y), ImVec2(rightDownCorn.x, rightDownCorn.y - edge), clr.GetU32(), width);
	_drawList->AddLine(ImVec2(rightDownCorn.x, rightDownCorn.y), ImVec2(rightDownCorn.x - edge, rightDownCorn.y), clr.GetU32(), width);
	_drawList->AddLine(ImVec2(leftDownCorn.x, leftDownCorn.y), ImVec2(leftDownCorn.x, leftDownCorn.y - edge), clr.GetU32(), width);
	_drawList->AddLine(ImVec2(leftDownCorn.x, leftDownCorn.y), ImVec2(leftDownCorn.x + edge, leftDownCorn.y), clr.GetU32(), width);
}

void ImGuiRendering::DrawLine(float x1, float y1, float x2, float y2, Color clr, float thickness = 1.0f)
{
	_drawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), clr.GetU32(), thickness);
}

void ImGuiRendering::DrawFilledCircle(float x, float y, float radius, Color clr)
{
	_drawList->AddCircleFilled(ImVec2(x, y), radius, clr.GetU32(), 64);
}

void ImGuiRendering::DrawWave(Vector loc, float radius, Color color, float thickness)
{
	static float Step = M_PI * 3.0f / 40.0f;
	Vector prev;
	for (float lat = 0; lat <= M_PI * 3.0f; lat += Step)
	{
		float sin1 = sin(lat);
		float cos1 = cos(lat);
		float sin3 = sin(0.0f);
		float cos3 = cos(0.0f);

		Vector point1;
		point1 = Vector(sin1 * cos3, cos1, sin1 * sin3) * radius;
		Vector point3 = loc;
		Vector Out;
		point3 += point1;

		if (g_Utils->WorldToScreen(point3, Out))
		{
			if (lat > 0.000)
				DrawLine(prev.x, prev.y, Out.x, Out.y, color, thickness);
		}
		prev = Out;
	}
}