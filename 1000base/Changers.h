#pragma once

class pChanger {
public:
	void SkinChanger();
	void GloveChanger();
private:
	int GetModelIndex_glove();
	int GetItemDefIndex_glove();
	int GetSkin_glove(int gloveIndex, int skinIndex);

	int GetModelIndex_knife();
	int GetItemDefIndex_knife();
}; extern pChanger* g_Changer;