#pragma once

struct skinInfo
{
	int seed = -1;
	int paintkit;
	std::string tagName;
};

class CVars {
public:

	struct {
		bool Enabled;
		bool OnTeam;
		int DelayAfterKill;

		bool SmokeCheck;
		bool FlashCheck;

		float Smooth_Pistols;
		float Smooth_Rifles;
		float Smooth_SMG;
		float Smooth_Shotguns;
		float Smooth_Snipers;
		float FOV_Pistols;
		float FOV_Rifles;
		float FOV_SMG;
		float FOV_Shotguns;
		float FOV_Snipers;



		// pSilent settings
		bool Enabled_Pistols_S;
		bool Enabled_Rifles_S;
		bool Enabled_SMG_S;
		bool Enabled_Shotguns_S;
		bool Enabled_Snipers_S;

		float FOV_Pistols_S;
		float FOV_Rifles_S;
		float FOV_SMG_S;
		float FOV_Shotguns_S;
		float FOV_Snipers_S;



		float RCSx_Pistols;
		float RCSy_Pistols;
		float RCSx_Rifles;
		float RCSy_Rifles;
		float RCSx_SMG;
		float RCSy_SMG;

		int RCSafterX_Pistols;
		int RCSafterX_Rifles;
		int RCSafterX_SMG;

		bool Nearest_Pistols;
		bool Nearest_Rifles;
		bool Nearest_SMG;
		bool Nearest_Shotguns;
		bool Nearest_Snipers;

		int Bone_Pistols;
		int Bone_Rifles;
		int Bone_SMG;
		int Bone_Shotguns;
		int Bone_Snipers;
		int Selection_Weapon;

		bool BackTrack;
		bool BackTrackV;
		int BT_ticks;

		bool OnKey;
		int Key;
	} Aimbot;

	struct {
		bool Opened;
		int ShowedPage;
		int currentWeapon;
		char configname[128] = "default";

		char FontFolder[128] = "C:\\Windows\\Fonts\\";
		bool ChangeMenuFont;
		char MenuFont[128] = "Tahoma";
		bool ChangeESPFont;
		char ESPFont[128] = "Tahoma";
	} Menu;

	struct {
		bool Bhop;
		bool AutoAccept;
		bool AutoStrafe;
		bool Radar;
		bool RadarEnemyOnly;
		int RadarRange;
		bool SpectatorList;
		bool RankReview;

		bool LegitAA;
		bool Direction;
		float StrafeFirst = 450.0f, StrafeSecond = 450.0f;

		int Glove;
		int GloveSkin;

		int FOV = 90;
		int MODEL_FOV = 60;
		bool AutoPistol;
		bool SniperCross;
		bool ClanTagChanger;
		int TagChanger;
		char Tag[128] = "";
	} Misc;

	struct {
		bool Enabled;
		bool HPbar;
		bool ARMORbar;
		bool WeaponIC;
		bool Ammo;
		bool NickName;
		bool InfoBox;
		bool Box;
		int BoxStyle;
		bool Skeleton;
		float SkeletonSize;
		
		bool HPtext;
		bool ARMORtext;
		bool Defusing;

		bool DroppedWeap;
		bool DroppedC4;
		bool BombTimer;

		int WeaponStyle;
		bool InGameRadar;
		bool Hitmarker;
		bool HitmarkerSound;
		bool FOV;
		bool NoFlash;
		bool Hostage;
		bool GH;
		bool DrawGrenades;
		bool VisibleCheck;
		bool RecoilCS;

		struct {
			bool Teammates;
		} Filter;

		struct {
			bool Enabled;
			bool OnlyHidden;
			float Time;
		} Sound;

		struct
		{
			bool Enabled;
			int Alpha;
			bool GlowBloom;
		} Glow;

		struct {
			bool Hands, Weapons;
			bool Enabled;
			bool Ignorez;
			int Style, HandsStyle, WeaponsStyle;
			int Kind;
		} Chams;
	} Visuals;

	struct {
		float ESPtext[4];
		float BoxTeam[4];
		float BoxTeamV[4];
		float BoxEnemy[4];
		float BoxEnemyV[4];
		float GlowTeam[4];
		float GlowEnemy[4];
		float Skeleton[4];
		float Sound[4];
		float Direction[4];
		float InfoBoxT[4];
		float InfoBoxE[4];
		float TeamVisible[4];
		float EnemyVisible[4];
		float TeamIgnorez[4];
		float EnemyIgnorez[4];
		float MenuMain[4];
		float Hands[4];
		float Weap[4];
	} Colors;

	struct {
		bool Enabled;
		bool OnTeam;

		bool SmokeCheck;
		bool FlashCheck;

		bool OnKey;
		int Key;
		int Delay;

		bool Hitchance;
		int HitchanceAM;

		bool Head;
		bool Arms;
		bool Legs;
		bool Stomach;
		bool Chest;
	} Triggerbot;

	struct
	{
		bool Enabled;
		bool KnifeChanger;
		bool KnifeKillInfoFix;
		int knifemodel;
		int glove;
		int gloveskin;

		struct
		{
			bool LegitSpecial;
			bool pSilent;
			float pSilentFOV;
			float rcs_x;
			float rcs_y;
			float Smooth;
			float FOV;
			bool Nearest;
			int rcs_start;
			int bone;

			bool ChangerEnabled;
			int ChangerSkin;
			float Wear;
			int Seed;
			int SC;
			bool LiveSC;
		} W[524];
		bool SkinFilter;
		std::unordered_map<std::string, std::set<std::string>> weaponSkins;
		std::unordered_map<std::string, skinInfo> skinMap;
		std::unordered_map<std::string, std::string> skinNames;
		std::vector<std::string> weaponNames;
	} Skinchanger;

}; extern CVars* g_Vars;