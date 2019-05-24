#pragma once

class Visuals {
public:
	void ESP();
	void ResetESP();
	void OnPlaySound(const Vector* pOrigin, int iEntIndex);
private:
	void DrawEntity();
	void DrawDropped();

	void dSkeleton(C_BaseEntity* Entity);
	void dBackTrack(int index);

	void AddSound(Vector vOrigin);
	void DrawSoundEsp();
	void SoundUpdate();

	void dOther();
}; extern Visuals* g_Visuals;