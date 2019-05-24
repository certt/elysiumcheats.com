#pragma once

class lAimbot {
public:
	void Run(CUserCmd* pCmd);
	void legitBackTrack(CUserCmd* cmd);
	float FOV, pSilentFOV;
private:
	void DoAimbot(CUserCmd* pCmd);
	void DoRCS(CUserCmd* pCmd);
	void SetupSettings();
	QAngle CurveSmooth(QAngle& viewangles, QAngle target, float factor);
	int ClosestBone(C_BaseEntity *Entity, CUserCmd* cmd);
	void FindTarget(CUserCmd* pCmd);
	float GetFov(const QAngle& viewAngle, const QAngle& aimAngle);

	inline Vector angle_vector(QAngle meme)
	{
		auto sy = sin(meme.y / 180.f * static_cast<float>(3.141592654f));
		auto cy = cos(meme.y / 180.f * static_cast<float>(3.141592654f));
		auto sp = sin(meme.x / 180.f * static_cast<float>(3.141592654f));
		auto cp = cos(meme.x / 180.f* static_cast<float>(3.141592654f));

		return Vector(cp*cy, cp*sy, -sp);
	}

	inline float distance_point_to_line(Vector Point, Vector LineOrigin, Vector Dir)
	{
		auto PointDir = Point - LineOrigin;
		auto TempOffset = PointDir.Dot(Dir) / (Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
		if (TempOffset < 0.000001f)
			return FLT_MAX;

		auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);
		return (Point - PerpendicularPoint).Length();
	}

}; extern lAimbot* g_Legit;

struct backtrackData
{
	float simtime;
	Vector hitboxPos;
}; extern backtrackData headPositions[64][12];