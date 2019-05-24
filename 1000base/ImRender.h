#pragma once

#include "ABytes.h"

enum StringFlags : unsigned
{
	CentredX = 0,
	CentredY = 1,
	Outline = 2,
	CentredXY = CentredX | CentredY,
};

class ImGuiRendering {
public:
	ImVec2 MainWindowSize, MainWindowPos;

	void __stdcall CreateObjects(IDirect3DDevice9* pDevice);
	void __stdcall InvalidateObjects();
	void __stdcall PreRender(IDirect3DDevice9* device);
	void __stdcall PostRender(IDirect3DDevice9* deivce);
	void __stdcall EndPresent(IDirect3DDevice9* device);
	void __stdcall SetupPresent(IDirect3DDevice9* device);

	void DrawRect(float x1, float y1, float x2, float y2, Color clr, float thickness);

	void DrawEspBox(Vector leftUpCorn, Vector rightDownCorn, Color clr, float width);
	void DrawCorner(Vector leftUpCorn, Vector rightUpCorn, Vector leftDownCorn, Vector rightDownCorn, Color clr, float width);
	void DrawLine(float x1, float y1, float x2, float y2, Color clr, float thickness);

	void DrawWave(Vector loc, float radius, Color clr, float thickness);
	void DrawFilledCircle(float x, float y, float radius, Color clr);
	void DrawRectFilled(float x1, float y1, float x2, float y2, Color clr);
	void DrawRectFilledMulti(float x1, float y1, float x2, float y2, Color clr1, Color clr2, Color clr3, Color clr4);
	void DrawString(ImFont* font, float font_size, int flag, float x, float y, Color color, bool with_box, bool Enemy, const char* message ...);
	void Draw3DCube(float scalar, QAngle angles, Vector middle_origin, Color outline);
private:
}; extern ImGuiRendering* g_ImRender;