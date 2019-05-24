#include "Main.h"
#include "SkinParser.h"
#include <iostream>
#include <cctype>
#include <clocale>

char* GetConfigName(int weaponid)
{
	switch (weaponid)
	{
	case WEAPON_DEAGLE:
		return "deagle";
	case WEAPON_ELITE:
		return "elite";
	case WEAPON_FIVESEVEN:
		return "fiveseven";
	case WEAPON_GLOCK:
		return "glock18";
	case WEAPON_AK47:
		return "ak47";
	case WEAPON_AUG:
		return "aug";
	case WEAPON_AWP:
		return "awp";
	case WEAPON_FAMAS:
		return "famas";
	case WEAPON_G3SG1:
		return "g3sg1";
	case WEAPON_GALILAR:
		return "galil";
	case WEAPON_M249:
		return "m249";
	case WEAPON_M4A1:
		return "m4a4";
	case WEAPON_MAC10:
		return "mac10";
	case WEAPON_P90:
		return "p90";
	case WEAPON_UMP45:
		return "ump45";
	case WEAPON_XM1014:
		return "xm1014";
	case WEAPON_BIZON:
		return "bizon";
	case WEAPON_MAG7:
		return "mag7";
	case WEAPON_NEGEV:
		return "negev";
	case WEAPON_SAWEDOFF:
		return "sawedoff";
	case WEAPON_TEC9:
		return "tec9";
	case WEAPON_HKP2000:
		return "p2000";
	case WEAPON_MP7:
		return "mp7";
	case WEAPON_MP9:
		return "mp9";
	case WEAPON_NOVA:
		return "nova";
	case WEAPON_P250:
		return "p250";
	case WEAPON_SCAR20:
		return "scar20";
	case WEAPON_SG556:
		return "sg556";
	case WEAPON_SSG08:
		return "ssg08";
	case WEAPON_M4A1_SILENCER:
		return "m4a1s";
	case WEAPON_USP_SILENCER:
		return "usps";
	case WEAPON_CZ75A:
		return "cz75a";
	case WEAPON_REVOLVER:
		return "revolver";
	case WEAPON_BAYONET:
		return "knife_bayonet";
	case WEAPON_KNIFE_FLIP:
		return "knife_flip";
	case WEAPON_KNIFE_GUT:
		return "knife_gut";
	case WEAPON_KNIFE_KARAMBIT:
		return "knife_karambit";
	case WEAPON_KNIFE_M9_BAYONET:
		return "knife_m9";
	case WEAPON_KNIFE_TACTICAL:
		return "knife_huntsman";
	case WEAPON_KNIFE_FALCHION:
		return "knife_falchion";
	case WEAPON_KNIFE_BUTTERFLY:
		return "knife_butterfly";
	case WEAPON_KNIFE_PUSH:
		return "knife_bowie";
	case 520:
		return "knife_navaja";
	case 522:
		return "knife_stiletto";
	case 519:
		return "knife_ursus";
	case 533:
		return "knife_talon";
	case 23:
		return "mp5sd";
	default:
		return "";
	}
	return "";
}

void CMenu::ReadCFG()
{
	static char path[MAX_PATH];
	std::string folder, file;
	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\elysium\\%s.ini", g_Vars->Menu.configname);

		folder = std::string(path) + "\\elysium\\";
		file = std::string(path) + szCmd;
	}
	CreateDirectoryA(folder.c_str(), NULL);
	CIniReader reader(file.c_str());

	g_Vars->Aimbot.Enabled = reader.ReadBoolean("Aimbot", "Enable", false);
	g_Vars->Aimbot.BackTrack = reader.ReadBoolean("Aimbot", "BackTrack", false);
	g_Vars->Aimbot.BackTrackV = reader.ReadBoolean("Aimbot", "BackTrackV", false);
	g_Vars->Aimbot.OnTeam = reader.ReadBoolean("Aimbot", "OnTeam", false);	

	g_Vars->Aimbot.Enabled_Pistols_S = reader.ReadBoolean("Aimbot", "Enabled_Pistols_S", false);
	g_Vars->Aimbot.Enabled_Rifles_S = reader.ReadBoolean("Aimbot", "Enabled_Rifles_S", false);
	g_Vars->Aimbot.Enabled_SMG_S = reader.ReadBoolean("Aimbot", "Enabled_SMG_S", false);
	g_Vars->Aimbot.Enabled_Shotguns_S = reader.ReadBoolean("Aimbot", "Enabled_Shotguns_S", false);
	g_Vars->Aimbot.Enabled_Snipers_S = reader.ReadBoolean("Aimbot", "Enabled_Snipers_S", false);

	g_Vars->Aimbot.FlashCheck = reader.ReadFloat("Aimbot", "FlashCheck", false);
	g_Vars->Aimbot.SmokeCheck = reader.ReadFloat("Aimbot", "SmokeCheck", false);
	g_Vars->Triggerbot.FlashCheck = reader.ReadFloat("Triggerbot", "FlashCheck", false);
	g_Vars->Triggerbot.SmokeCheck = reader.ReadFloat("Triggerbot", "SmokeCheck", false);
	g_Vars->Misc.LegitAA = reader.ReadFloat("Misc", "LegitAA", false);
	g_Vars->Visuals.VisibleCheck = reader.ReadFloat("Visuals", "VisibleCheck", false);

	g_Vars->Aimbot.OnKey = reader.ReadBoolean("Aimbot", "OnKey", false);
	g_Vars->Aimbot.Key = reader.ReadInteger("Aimbot", "Key", 0);

	g_Vars->Visuals.Enabled = reader.ReadBoolean("Visuals", "Enable", false);
	g_Vars->Visuals.HPbar = reader.ReadBoolean("Visuals", "HPBar", false);
	g_Vars->Visuals.ARMORbar = reader.ReadBoolean("Visuals", "Armorbar", false);
	g_Vars->Visuals.WeaponIC = reader.ReadBoolean("Visuals", "Weapon", false);
	g_Vars->Visuals.WeaponStyle = reader.ReadInteger("Visuals", "WeaponStyle", false);
	g_Vars->Visuals.Ammo = reader.ReadBoolean("Visuals", "Ammo", false);
	g_Vars->Visuals.NickName = reader.ReadBoolean("Visuals", "Nickname", false);
	g_Vars->Visuals.Box = reader.ReadBoolean("Visuals", "Box", false);
	g_Vars->Visuals.BoxStyle = reader.ReadInteger("Visuals", "BoxStyle", false);
	g_Vars->Visuals.Skeleton = reader.ReadBoolean("Visuals", "Skeleton", false);
	g_Vars->Visuals.Hostage = reader.ReadBoolean("Visuals", "Hostage", false);
	g_Vars->Visuals.SkeletonSize = reader.ReadFloat("Visuals", "SkeletonSize", 1.f);
	g_Vars->Visuals.Defusing = reader.ReadBoolean("Visuals", "Defusing", false);
	g_Vars->Visuals.DroppedWeap = reader.ReadBoolean("Visuals", "DroppedWeap", false);
	g_Vars->Visuals.DroppedC4 = reader.ReadBoolean("Visuals", "DroppedC4", false);
	g_Vars->Visuals.BombTimer = reader.ReadBoolean("Visuals", "BombTimer", false);
	g_Vars->Visuals.Filter.Teammates = reader.ReadBoolean("PlayerFilter", "Teammates", false);
	g_Vars->Visuals.Sound.Enabled = reader.ReadBoolean("SoundEsp", "Enabled", false);
	g_Vars->Visuals.Sound.OnlyHidden = reader.ReadBoolean("SoundEsp", "OnlyHidden", false);
	g_Vars->Visuals.Sound.Time = reader.ReadFloat("Visuals", "Time", 800.f);
	g_Vars->Visuals.Glow.Alpha = reader.ReadInteger("Visuals", "GlowAlpha", 255);
	g_Vars->Visuals.Glow.Enabled = reader.ReadBoolean("Visuals", "GlowEnabled", false);
	g_Vars->Visuals.Glow.GlowBloom = reader.ReadBoolean("Visuals", "GlowBloom", false);
	g_Vars->Colors.BoxEnemy[0] = reader.ReadFloat("Colors", "BoxEnemy", 255.0f);
	g_Vars->Colors.BoxEnemy[1] = reader.ReadFloat("Colors", "BoxEnemy1", 255.0f);
	g_Vars->Colors.BoxEnemy[2] = reader.ReadFloat("Colors", "BoxEnemy2", 255.0f);
	g_Vars->Colors.BoxTeam[0] = reader.ReadFloat("Colors", "BoxTeam", 255.0f);
	g_Vars->Colors.BoxTeam[1] = reader.ReadFloat("Colors", "BoxTeam1", 255.0f);
	g_Vars->Colors.BoxTeam[2] = reader.ReadFloat("Colors", "BoxTeam2", 255.0f);
	g_Vars->Colors.BoxEnemyV[0] = reader.ReadFloat("Colors", "BoxEnemyV", 255.0f);
	g_Vars->Colors.BoxEnemyV[1] = reader.ReadFloat("Colors", "BoxEnemy1V", 255.0f);
	g_Vars->Colors.BoxEnemyV[2] = reader.ReadFloat("Colors", "BoxEnemy2V", 255.0f);
	g_Vars->Colors.BoxTeamV[0] = reader.ReadFloat("Colors", "BoxTeamV", 255.0f);
	g_Vars->Colors.BoxTeamV[1] = reader.ReadFloat("Colors", "BoxTeam1V", 255.0f);
	g_Vars->Colors.BoxTeamV[2] = reader.ReadFloat("Colors", "BoxTeam2V", 255.0f);
	g_Vars->Colors.Direction[0] = reader.ReadFloat("Colors", "Direction", 255.0f);
	g_Vars->Colors.Direction[1] = reader.ReadFloat("Colors", "Direction1", 255.0f);
	g_Vars->Colors.Direction[2] = reader.ReadFloat("Colors", "Direction2", 255.0f);
	g_Vars->Colors.ESPtext[0] = reader.ReadFloat("Colors", "ESPtext", 255.0f);
	g_Vars->Colors.ESPtext[1] = reader.ReadFloat("Colors", "ESPtext1", 255.0f);
	g_Vars->Colors.ESPtext[2] = reader.ReadFloat("Colors", "ESPtext2", 255.0f);
	g_Vars->Colors.GlowEnemy[0] = reader.ReadFloat("Colors", "GlowEnemy", 255.0f);
	g_Vars->Colors.GlowEnemy[1] = reader.ReadFloat("Colors", "GlowEnemy1", 255.0f);
	g_Vars->Colors.GlowEnemy[2] = reader.ReadFloat("Colors", "GlowEnemy2", 255.0f);
	g_Vars->Colors.GlowTeam[0] = reader.ReadFloat("Colors", "GlowTeam", 255.0f);
	g_Vars->Colors.GlowTeam[1] = reader.ReadFloat("Colors", "GlowTeam1", 255.0f);
	g_Vars->Colors.GlowTeam[2] = reader.ReadFloat("Colors", "GlowTeam2", 255.0f);
	g_Vars->Colors.Skeleton[0] = reader.ReadFloat("Colors", "Skeleton", 255.0f);
	g_Vars->Colors.Skeleton[1] = reader.ReadFloat("Colors", "Skeleton1", 255.0f);
	g_Vars->Colors.Skeleton[2] = reader.ReadFloat("Colors", "Skeleton2", 255.0f);
	g_Vars->Colors.Sound[0] = reader.ReadFloat("Colors", "Sound", 255.0f);
	g_Vars->Colors.Sound[1] = reader.ReadFloat("Colors", "Sound1", 255.0f);
	g_Vars->Colors.Sound[2] = reader.ReadFloat("Colors", "Sound2", 255.0f);
	g_Vars->Colors.TeamVisible[0] = reader.ReadFloat("Colors", "TeamVisible", 255.0f);
	g_Vars->Colors.TeamVisible[1] = reader.ReadFloat("Colors", "TeamVisible1", 255.0f);
	g_Vars->Colors.TeamVisible[2] = reader.ReadFloat("Colors", "TeamVisible2", 255.0f);
	g_Vars->Colors.TeamIgnorez[0] = reader.ReadFloat("Colors", "TeamIgnorez", 255.0f);
	g_Vars->Colors.TeamIgnorez[1] = reader.ReadFloat("Colors", "TeamIgnorez1", 255.0f);
	g_Vars->Colors.TeamIgnorez[2] = reader.ReadFloat("Colors", "TeamIgnorez2", 255.0f);
	g_Vars->Colors.EnemyVisible[0] = reader.ReadFloat("Colors", "EnemyVisible", 255.0f);
	g_Vars->Colors.EnemyVisible[1] = reader.ReadFloat("Colors", "EnemyVisible1", 255.0f);
	g_Vars->Colors.EnemyVisible[2] = reader.ReadFloat("Colors", "EnemyVisible2", 255.0f);
	g_Vars->Colors.EnemyIgnorez[0] = reader.ReadFloat("Colors", "EnemyIgnorez", 255.0f);
	g_Vars->Colors.EnemyIgnorez[1] = reader.ReadFloat("Colors", "EnemyIgnorez1", 255.0f);
	g_Vars->Colors.EnemyIgnorez[2] = reader.ReadFloat("Colors", "EnemyIgnorez2", 255.0f);
	g_Vars->Colors.InfoBoxE[0] = reader.ReadFloat("Colors", "InfoBoxE", 255.0f);
	g_Vars->Colors.InfoBoxE[1] = reader.ReadFloat("Colors", "InfoBoxE1", 255.0f);
	g_Vars->Colors.InfoBoxE[2] = reader.ReadFloat("Colors", "InfoBoxE2", 255.0f);
	g_Vars->Colors.InfoBoxT[0] = reader.ReadFloat("Colors", "InfoBoxT", 255.0f);
	g_Vars->Colors.InfoBoxT[1] = reader.ReadFloat("Colors", "InfoBoxT1", 255.0f);
	g_Vars->Colors.InfoBoxT[2] = reader.ReadFloat("Colors", "InfoBoxT2", 255.0f);
	g_Vars->Visuals.Chams.Enabled = reader.ReadBoolean("Visuals", "ChamsEnabled", false);
	g_Vars->Visuals.Chams.Ignorez = reader.ReadBoolean("Visuals", "ChamsIgnorez", false);
	g_Vars->Visuals.InfoBox = reader.ReadBoolean("Visuals", "InfoBox", false);
	g_Vars->Visuals.GH = reader.ReadBoolean("Visuals", "GH", false);
	g_Vars->Visuals.DrawGrenades = reader.ReadBoolean("Visuals", "DrawGrenades", false);
	g_Vars->Misc.FOV = reader.ReadInteger("Misc", "FOV", 90);
	g_Vars->Misc.MODEL_FOV = reader.ReadInteger("Misc", "MODEL_FOV", 60);
	g_Vars->Visuals.FOV = reader.ReadBoolean("Visuals", "FOV", false);
	g_Vars->Visuals.Hitmarker = reader.ReadBoolean("Visuals", "Hitmarker", false);
	g_Vars->Visuals.HitmarkerSound = reader.ReadBoolean("Visuals", "HitmarkerSound", false);
	g_Vars->Misc.AutoStrafe = reader.ReadBoolean("Misc", "AutoStrafe", false);
	g_Vars->Misc.Bhop = reader.ReadBoolean("Misc", "Bhop", false);
	g_Vars->Misc.StrafeFirst = reader.ReadFloat("Misc", "StrafeFirst", 450.0f);
	g_Vars->Misc.StrafeSecond = reader.ReadFloat("Misc", "StrafeSecond", 450.0f);
	g_Vars->Triggerbot.Enabled = reader.ReadBoolean("Triggerbot", "Enabled", false);
	g_Vars->Triggerbot.OnKey = reader.ReadBoolean("Triggerbot", "OnKey", false);
	g_Vars->Triggerbot.OnTeam = reader.ReadBoolean("Triggerbot", "OnTeam", false);
	g_Vars->Triggerbot.Head = reader.ReadBoolean("Triggerbot", "Head", false);
	g_Vars->Triggerbot.Stomach = reader.ReadBoolean("Triggerbot", "Stomach", false);
	g_Vars->Triggerbot.Arms = reader.ReadBoolean("Triggerbot", "Arms", false);
	g_Vars->Triggerbot.Legs = reader.ReadBoolean("Triggerbot", "Legs", false);
	g_Vars->Triggerbot.Chest = reader.ReadBoolean("Triggerbot", "Chest", false);
	g_Vars->Triggerbot.Delay = reader.ReadInteger("Triggerbot", "Delay", 100);
	g_Vars->Triggerbot.Key = reader.ReadInteger("Triggerbot", "Key", 0);
	g_Vars->Triggerbot.Hitchance = reader.ReadBoolean("Triggerbot", "Hitchance", false);
	g_Vars->Triggerbot.HitchanceAM = reader.ReadInteger("Triggerbot", "HitchanceAM", 0);
	
	for (int weaponid = 1; weaponid < 524; weaponid++)
	{
		char* section = GetConfigName(weaponid);
		if (strcmp(section, "") == 0)
			continue;

		g_Vars->Skinchanger.W[weaponid].Nearest = reader.ReadBoolean(section, "Nearest", false);
		g_Vars->Skinchanger.W[weaponid].pSilent = reader.ReadBoolean(section, "pSilent", false);

		g_Vars->Skinchanger.W[weaponid].FOV = reader.ReadFloat(section, "FOV", 0.0001f);
		g_Vars->Skinchanger.W[weaponid].pSilentFOV = reader.ReadFloat(section, "pSilentFOV", 0.0001f);
		g_Vars->Skinchanger.W[weaponid].Smooth = reader.ReadFloat(section, "Smooth", 0.0001f);
		g_Vars->Skinchanger.W[weaponid].rcs_x = reader.ReadFloat(section, "rcs_x", 0.0001f);
		g_Vars->Skinchanger.W[weaponid].rcs_y = reader.ReadFloat(section, "rcs_y", 0.0001f);

		g_Vars->Skinchanger.W[weaponid].bone = reader.ReadInteger(section, "bone", 0);
		g_Vars->Skinchanger.W[weaponid].rcs_start = reader.ReadInteger(section, "rcs_start", 0);

		g_Vars->Skinchanger.W[weaponid].ChangerEnabled = reader.ReadBoolean(section, "ChangerEnabled", false);
		g_Vars->Skinchanger.W[weaponid].LiveSC = reader.ReadBoolean(section, "LiveSC", false);
		g_Vars->Skinchanger.W[weaponid].ChangerSkin = reader.ReadInteger(section, "Skin", 0);
		g_Vars->Skinchanger.W[weaponid].SC = reader.ReadInteger(section, "SC", 0);
		g_Vars->Skinchanger.W[weaponid].Seed = reader.ReadInteger(section, "Seed", 0);
		g_Vars->Skinchanger.W[weaponid].Wear = reader.ReadFloat(section, "Wear", 0.0001f);
	}

	g_Vars->Skinchanger.knifemodel = reader.ReadInteger("SkinChanger", "knifemodel", 0);
	g_Vars->Skinchanger.KnifeKillInfoFix = reader.ReadBoolean("SkinChanger", "KnifeKillInfoFix", false);
	g_Vars->Skinchanger.KnifeChanger = reader.ReadBoolean("SkinChanger", "KnifeChanger", false);
	g_Vars->Colors.MenuMain[0] = reader.ReadFloat("Colors", "MenuMain", 1.00f);
	g_Vars->Colors.MenuMain[1] = reader.ReadFloat("Colors", "MenuMain1", 0.25f);
	g_Vars->Colors.MenuMain[2] = reader.ReadFloat("Colors", "MenuMain2", 0.0f);
	g_Vars->Misc.Radar = reader.ReadBoolean("Misc", "Radar", false);
	g_Vars->Misc.AutoAccept = reader.ReadBoolean("Misc", "AutoAccept", false);
	g_Vars->Misc.RadarEnemyOnly = reader.ReadBoolean("Misc", "RadarEnemyOnly", false);
	g_Vars->Misc.SpectatorList = reader.ReadBoolean("Misc", "SpectatorList", false);
	g_Vars->Misc.RadarRange = reader.ReadInteger("Misc", "RadarRange", 1);
	g_Vars->Misc.RankReview = reader.ReadBoolean("Misc", "RankReview", false);
	g_Vars->Visuals.Chams.Kind = reader.ReadInteger("Chams", "Kind", 0);
	char* folder1 = reader.ReadString("Misc", "FontFolder", "C:\\Windows\\Fonts\\");
	strcpy(g_Vars->Menu.FontFolder, folder1);
	char* menufont = reader.ReadString("Misc", "MenuFont", "Tahoma");
	strcpy(g_Vars->Menu.MenuFont, menufont);
	char* ESPfont = reader.ReadString("Misc", "ESPFont", "Tahoma");
	strcpy(g_Vars->Menu.ESPFont, ESPfont);
	g_Vars->Menu.ChangeESPFont = reader.ReadBoolean("Misc", "ChangeESPFont", false);
	g_Vars->Menu.ChangeMenuFont = reader.ReadBoolean("Misc", "ChangeMenuFont", false);
	g_Vars->Misc.Glove = reader.ReadInteger("Misc", "Glove", 0);
	g_Vars->Misc.GloveSkin = reader.ReadInteger("Misc", "GloveSkin", 0);

	g_Vars->Aimbot.DelayAfterKill = reader.ReadInteger("Aimbot", "DelayAfterKill", 0);
	g_Vars->Aimbot.BT_ticks = reader.ReadInteger("Aimbot", "BT_ticks", 1);
	g_Vars->Misc.ClanTagChanger = reader.ReadBoolean("Misc", "ClanTagChanger", false);
	g_Vars->Misc.TagChanger = reader.ReadInteger("Misc", "TagChanger", 0);
	char* clantag = reader.ReadString("Misc", "Tag", "");
	strcpy(g_Vars->Misc.Tag, clantag);

	g_Vars->Visuals.InGameRadar = reader.ReadBoolean("Visuals", "InGameRadar", false);
	g_Vars->Visuals.RecoilCS = reader.ReadBoolean("Visuals", "RecoilCS", false);
	g_Vars->Visuals.Chams.Hands = reader.ReadBoolean("Visuals", "Hands", false);
	g_Vars->Visuals.Chams.Weapons = reader.ReadBoolean("Visuals", "Weapons", false);

	g_Vars->Misc.AutoPistol = reader.ReadBoolean("Misc", "AutoPistol", false);
	g_Vars->Misc.SniperCross = reader.ReadBoolean("Misc", "SniperCross", false);

	g_Vars->Visuals.Chams.HandsStyle = reader.ReadInteger("Visuals", "HandsStyle", 0);
	g_Vars->Visuals.Chams.WeaponsStyle = reader.ReadInteger("Visuals", "WeaponsStyle", 0);

	g_Vars->Colors.Weap[0] = reader.ReadFloat("Colors", "Weap", 1.00f);
	g_Vars->Colors.Weap[1] = reader.ReadFloat("Colors", "Weap1", 1.00f);
	g_Vars->Colors.Weap[2] = reader.ReadFloat("Colors", "Weap2", 1.00f);

	g_Vars->Colors.Hands[0] = reader.ReadFloat("Colors", "Hands", 1.00f);
	g_Vars->Colors.Hands[1] = reader.ReadFloat("Colors", "Hands1", 1.00f);
	g_Vars->Colors.Hands[2] = reader.ReadFloat("Colors", "Hands2", 1.00f);
}

void SaveCFG()
{
	static char path[MAX_PATH];
	std::string folder, file;
	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\elysium\\%s.ini", g_Vars->Menu.configname);

		folder = std::string(path) + "\\elysium\\";
		file = std::string(path) + szCmd;
	}
	CreateDirectoryA(folder.c_str(), NULL);
	CIniWriter writer(file.c_str());

	writer.WriteBoolean("Aimbot", "Enable", g_Vars->Aimbot.Enabled);
	writer.WriteBoolean("Aimbot", "BackTrack", g_Vars->Aimbot.BackTrack);
	writer.WriteBoolean("Aimbot", "BackTrackV", g_Vars->Aimbot.BackTrackV);
	writer.WriteBoolean("Aimbot", "OnTeam", g_Vars->Aimbot.OnTeam);

	writer.WriteBoolean("Aimbot", "SmokeCheck", g_Vars->Aimbot.SmokeCheck);
	writer.WriteBoolean("Aimbot", "FlashCheck", g_Vars->Aimbot.FlashCheck);

	writer.WriteBoolean("Triggerbot", "SmokeCheck", g_Vars->Triggerbot.SmokeCheck);
	writer.WriteBoolean("Triggerbot", "FlashCheck", g_Vars->Triggerbot.FlashCheck);

	writer.WriteBoolean("Misc", "LegitAA", g_Vars->Misc.LegitAA);
	writer.WriteBoolean("Visuals", "VisibleCheck", g_Vars->Visuals.VisibleCheck);

	writer.WriteInteger("Aimbot", "Key", g_Vars->Aimbot.Key);
	writer.WriteBoolean("Aimbot", "OnKey", g_Vars->Aimbot.OnKey);

	writer.WriteBoolean("Visuals", "Enable", g_Vars->Visuals.Enabled);
	writer.WriteBoolean("Visuals", "HPBar", g_Vars->Visuals.HPbar);
	writer.WriteBoolean("Visuals", "Armorbar", g_Vars->Visuals.ARMORbar);
	writer.WriteBoolean("Visuals", "Weapon", g_Vars->Visuals.WeaponIC);
	writer.WriteInteger("Visuals", "WeaponStyle", g_Vars->Visuals.WeaponStyle);
	writer.WriteBoolean("Visuals", "Ammo", g_Vars->Visuals.Ammo);
	writer.WriteBoolean("Visuals", "Nickname", g_Vars->Visuals.NickName);
	writer.WriteBoolean("Visuals", "Box", g_Vars->Visuals.Box);
	writer.WriteInteger("Visuals", "BoxStyle", g_Vars->Visuals.BoxStyle);
	writer.WriteBoolean("Visuals", "Skeleton", g_Vars->Visuals.Skeleton);
	writer.WriteBoolean("Visuals", "Hostage", g_Vars->Visuals.Hostage);
	writer.WriteFloat("Visuals", "SkeletonSize", g_Vars->Visuals.SkeletonSize);
	writer.WriteBoolean("Visuals", "Defusing", g_Vars->Visuals.Defusing);
	writer.WriteBoolean("Visuals", "DroppedWeap", g_Vars->Visuals.DroppedWeap);
	writer.WriteBoolean("Visuals", "DroppedC4", g_Vars->Visuals.DroppedC4);
	writer.WriteBoolean("Visuals", "BombTimer", g_Vars->Visuals.BombTimer);
	writer.WriteBoolean("PlayerFilter", "Teammates", g_Vars->Visuals.Filter.Teammates);
	writer.WriteBoolean("SoundEsp", "Enabled", g_Vars->Visuals.Sound.Enabled);
	writer.WriteBoolean("SoundEsp", "OnlyHidden", g_Vars->Visuals.Sound.OnlyHidden);
	writer.WriteFloat("SoundEsp", "Time", g_Vars->Visuals.Sound.Time);
	writer.WriteBoolean("Visuals", "GlowEnabled", g_Vars->Visuals.Glow.Enabled);
	writer.WriteBoolean("Visuals", "GlowBloom", g_Vars->Visuals.Glow.GlowBloom);
	writer.WriteInteger("Visuals", "GlowAlpha", g_Vars->Visuals.Glow.Alpha);
	writer.WriteFloat("Colors", "BoxEnemy", g_Vars->Colors.BoxEnemy[0]);
	writer.WriteFloat("Colors", "BoxEnemy1", g_Vars->Colors.BoxEnemy[1]);
	writer.WriteFloat("Colors", "BoxEnemy2", g_Vars->Colors.BoxEnemy[2]);
	writer.WriteFloat("Colors", "BoxTeam", g_Vars->Colors.BoxTeam[0]);
	writer.WriteFloat("Colors", "BoxTeam1", g_Vars->Colors.BoxTeam[1]);
	writer.WriteFloat("Colors", "BoxTeam2", g_Vars->Colors.BoxTeam[2]);
	writer.WriteFloat("Colors", "BoxEnemyV", g_Vars->Colors.BoxEnemyV[0]);
	writer.WriteFloat("Colors", "BoxEnemy1V", g_Vars->Colors.BoxEnemyV[1]);
	writer.WriteFloat("Colors", "BoxEnemy2V", g_Vars->Colors.BoxEnemyV[2]);
	writer.WriteFloat("Colors", "BoxTeamV", g_Vars->Colors.BoxTeamV[0]);
	writer.WriteFloat("Colors", "BoxTeam1V", g_Vars->Colors.BoxTeamV[1]);
	writer.WriteFloat("Colors", "BoxTeam2V", g_Vars->Colors.BoxTeamV[2]);
	writer.WriteFloat("Colors", "Direction", g_Vars->Colors.Direction[0]);
	writer.WriteFloat("Colors", "Direction1", g_Vars->Colors.Direction[1]);
	writer.WriteFloat("Colors", "Direction2", g_Vars->Colors.Direction[2]);
	writer.WriteFloat("Colors", "ESPtext", g_Vars->Colors.ESPtext[0]);
	writer.WriteFloat("Colors", "ESPtext1", g_Vars->Colors.ESPtext[1]);
	writer.WriteFloat("Colors", "ESPtext2", g_Vars->Colors.ESPtext[2]);
	writer.WriteFloat("Colors", "GlowEnemy", g_Vars->Colors.GlowEnemy[0]);
	writer.WriteFloat("Colors", "GlowEnemy1", g_Vars->Colors.GlowEnemy[1]);
	writer.WriteFloat("Colors", "GlowEnemy2", g_Vars->Colors.GlowEnemy[2]);
	writer.WriteFloat("Colors", "GlowTeam", g_Vars->Colors.GlowTeam[0]);
	writer.WriteFloat("Colors", "GlowTeam1", g_Vars->Colors.GlowTeam[1]);
	writer.WriteFloat("Colors", "GlowTeam2", g_Vars->Colors.GlowTeam[2]);
	writer.WriteFloat("Colors", "Skeleton", g_Vars->Colors.Skeleton[0]);
	writer.WriteFloat("Colors", "Skeleton1", g_Vars->Colors.Skeleton[1]);
	writer.WriteFloat("Colors", "Skeleton2", g_Vars->Colors.Skeleton[2]);
	writer.WriteFloat("Colors", "Sound", g_Vars->Colors.Sound[0]);
	writer.WriteFloat("Colors", "Sound1", g_Vars->Colors.Sound[1]);
	writer.WriteFloat("Colors", "Sound2", g_Vars->Colors.Sound[2]);
	writer.WriteFloat("Colors", "TeamVisible", g_Vars->Colors.TeamVisible[0]);
	writer.WriteFloat("Colors", "TeamVisible1", g_Vars->Colors.TeamVisible[1]);
	writer.WriteFloat("Colors", "TeamVisible2", g_Vars->Colors.TeamVisible[2]);
	writer.WriteFloat("Colors", "TeamIgnorez", g_Vars->Colors.TeamIgnorez[0]);
	writer.WriteFloat("Colors", "TeamIgnorez1", g_Vars->Colors.TeamIgnorez[1]);
	writer.WriteFloat("Colors", "TeamIgnorez2", g_Vars->Colors.TeamIgnorez[2]);
	writer.WriteFloat("Colors", "EnemyVisible", g_Vars->Colors.EnemyVisible[0]);
	writer.WriteFloat("Colors", "EnemyVisible1", g_Vars->Colors.EnemyVisible[1]);
	writer.WriteFloat("Colors", "EnemyVisible2", g_Vars->Colors.EnemyVisible[2]);
	writer.WriteFloat("Colors", "EnemyIgnorez", g_Vars->Colors.EnemyIgnorez[0]);
	writer.WriteFloat("Colors", "EnemyIgnorez1", g_Vars->Colors.EnemyIgnorez[1]);
	writer.WriteFloat("Colors", "EnemyIgnorez2", g_Vars->Colors.EnemyIgnorez[2]);
	writer.WriteFloat("Colors", "InfoBoxE", g_Vars->Colors.InfoBoxE[0]);
	writer.WriteFloat("Colors", "InfoBoxE1", g_Vars->Colors.InfoBoxE[1]);
	writer.WriteFloat("Colors", "InfoBoxE2", g_Vars->Colors.InfoBoxE[2]);
	writer.WriteFloat("Colors", "InfoBoxT", g_Vars->Colors.InfoBoxT[0]);
	writer.WriteFloat("Colors", "InfoBoxT1", g_Vars->Colors.InfoBoxT[1]);
	writer.WriteFloat("Colors", "InfoBoxT2", g_Vars->Colors.InfoBoxT[2]);
	writer.WriteBoolean("Visuals", "ChamsEnabled", g_Vars->Visuals.Chams.Enabled);
	writer.WriteBoolean("Visuals", "ChamsIgnorez", g_Vars->Visuals.Chams.Ignorez);
	writer.WriteBoolean("Visuals", "InfoBox", g_Vars->Visuals.InfoBox);
	writer.WriteBoolean("Visuals", "GH", g_Vars->Visuals.GH);
	writer.WriteBoolean("Visuals", "DrawGrenades", g_Vars->Visuals.DrawGrenades);
	writer.WriteInteger("Misc", "FOV", g_Vars->Misc.FOV);
	writer.WriteInteger("Misc", "MODEL_FOV", g_Vars->Misc.MODEL_FOV);
	writer.WriteBoolean("Visuals", "FOV", g_Vars->Visuals.FOV);
	writer.WriteBoolean("Visuals", "Hitmarker", g_Vars->Visuals.Hitmarker);
	writer.WriteBoolean("Visuals", "HitmarkerSound", g_Vars->Visuals.HitmarkerSound);
	writer.WriteBoolean("Misc", "AutoStrafe", g_Vars->Misc.AutoStrafe);
	writer.WriteBoolean("Misc", "Bhop", g_Vars->Misc.Bhop);
	writer.WriteFloat("Misc", "StrafeFirst", g_Vars->Misc.StrafeFirst);
	writer.WriteFloat("Misc", "StrafeSecond", g_Vars->Misc.StrafeSecond);
	writer.WriteBoolean("Triggerbot", "Enabled", g_Vars->Triggerbot.Enabled);
	writer.WriteBoolean("Triggerbot", "OnKey", g_Vars->Triggerbot.OnKey);
	writer.WriteBoolean("Triggerbot", "OnTeam", g_Vars->Triggerbot.OnTeam);
	writer.WriteBoolean("Triggerbot", "Head", g_Vars->Triggerbot.Head);
	writer.WriteBoolean("Triggerbot", "Chest", g_Vars->Triggerbot.Chest);
	writer.WriteBoolean("Triggerbot", "Stomach", g_Vars->Triggerbot.Stomach);
	writer.WriteBoolean("Triggerbot", "Arms", g_Vars->Triggerbot.Arms);
	writer.WriteBoolean("Triggerbot", "Legs", g_Vars->Triggerbot.Legs);
	writer.WriteInteger("Triggerbot", "Delay", g_Vars->Triggerbot.Delay);
	writer.WriteInteger("Triggerbot", "Key", g_Vars->Triggerbot.Key);

	writer.WriteBoolean("Triggerbot", "Hitchance", g_Vars->Triggerbot.Hitchance);
	writer.WriteInteger("Triggerbot", "HitchanceAM", g_Vars->Triggerbot.HitchanceAM);

	for (int weaponid = 1; weaponid < 524; weaponid++)
	{
		char* section = GetConfigName(weaponid);
		if (strcmp(section, "") == 0)
			continue;

		writer.WriteBoolean(section, "pSilent", g_Vars->Skinchanger.W[weaponid].pSilent);
		writer.WriteBoolean(section, "Nearest", g_Vars->Skinchanger.W[weaponid].Nearest);
		writer.WriteBoolean(section, "LegitSpecial", g_Vars->Skinchanger.W[weaponid].LegitSpecial);

		writer.WriteFloat(section, "rcs_x", g_Vars->Skinchanger.W[weaponid].rcs_x);
		writer.WriteFloat(section, "rcs_y", g_Vars->Skinchanger.W[weaponid].rcs_y);
		writer.WriteFloat(section, "Smooth", g_Vars->Skinchanger.W[weaponid].Smooth);
		writer.WriteFloat(section, "FOV", g_Vars->Skinchanger.W[weaponid].FOV);
		writer.WriteFloat(section, "pSilentFOV", g_Vars->Skinchanger.W[weaponid].pSilentFOV);

		writer.WriteInteger(section, "bone", g_Vars->Skinchanger.W[weaponid].bone);
		writer.WriteInteger(section, "rcs_start", g_Vars->Skinchanger.W[weaponid].rcs_start);

		writer.WriteBoolean(section, "ChangerEnabled", g_Vars->Skinchanger.W[weaponid].ChangerEnabled);
		writer.WriteBoolean(section, "LiveSC", g_Vars->Skinchanger.W[weaponid].LiveSC);
		writer.WriteInteger(section, "Skin", g_Vars->Skinchanger.W[weaponid].ChangerSkin);
		writer.WriteInteger(section, "SC", g_Vars->Skinchanger.W[weaponid].SC);
		writer.WriteInteger(section, "Seed", g_Vars->Skinchanger.W[weaponid].Seed);
		writer.WriteFloat(section, "Wear", g_Vars->Skinchanger.W[weaponid].Wear);
	}

	writer.WriteInteger("SkinChanger", "knifemodel", g_Vars->Skinchanger.knifemodel);
	writer.WriteBoolean("SkinChanger", "KnifeKillInfoFix", g_Vars->Skinchanger.KnifeKillInfoFix);
	writer.WriteBoolean("SkinChanger", "KnifeChanger", g_Vars->Skinchanger.KnifeChanger);
	writer.WriteBoolean("Misc", "Radar", g_Vars->Misc.Radar);
	writer.WriteBoolean("Misc", "AutoAccept", g_Vars->Misc.AutoAccept);
	writer.WriteBoolean("Misc", "Radar enemy only", g_Vars->Misc.RadarEnemyOnly);
	writer.WriteBoolean("Misc", "SpectatorList", g_Vars->Misc.SpectatorList);
	writer.WriteInteger("Misc", "RadarRange", g_Vars->Misc.RadarRange);
	writer.WriteFloat("Colors", "MenuMain", g_Vars->Colors.MenuMain[0]);
	writer.WriteFloat("Colors", "MenuMain1", g_Vars->Colors.MenuMain[1]);
	writer.WriteFloat("Colors", "MenuMain2", g_Vars->Colors.MenuMain[2]);
	writer.WriteBoolean("Misc", "RankReview", g_Vars->Misc.RankReview);
	writer.WriteInteger("Chams", "Kind", g_Vars->Visuals.Chams.Kind);
	writer.WriteString("Misc", "FontFolder", g_Vars->Menu.FontFolder);
	writer.WriteString("Misc", "MenuFont", g_Vars->Menu.MenuFont);
	writer.WriteString("Misc", "ESPFont", g_Vars->Menu.ESPFont);
	writer.WriteBoolean("Misc", "ChangeESPFont", g_Vars->Menu.ChangeESPFont);
	writer.WriteBoolean("Misc", "ChangeMenuFont", g_Vars->Menu.ChangeMenuFont);
	writer.WriteInteger("Misc", "Glove", g_Vars->Misc.Glove);
	writer.WriteInteger("Misc", "GloveSkin", g_Vars->Misc.GloveSkin);

	writer.WriteInteger("Aimbot", "BT_ticks", g_Vars->Aimbot.BT_ticks);
	writer.WriteBoolean("Misc", "ClanTagChanger", g_Vars->Misc.ClanTagChanger);
	writer.WriteInteger("Misc", "TagChanger", g_Vars->Misc.TagChanger);
	writer.WriteString("Misc", "Tag", g_Vars->Misc.Tag);

	writer.WriteBoolean("Visuals", "InGameRadar", g_Vars->Visuals.InGameRadar);
	writer.WriteBoolean("Visuals", "RecoilCS", g_Vars->Visuals.RecoilCS);
	writer.WriteBoolean("Visuals", "Hands", g_Vars->Visuals.Chams.Hands);
	writer.WriteBoolean("Visuals", "Weapons", g_Vars->Visuals.Chams.Weapons);

	writer.WriteBoolean("Misc", "AutoPistol", g_Vars->Misc.AutoPistol);
	writer.WriteBoolean("Misc", "SniperCross", g_Vars->Misc.SniperCross);

	writer.WriteInteger("Visuals", "HandsStyle", g_Vars->Visuals.Chams.HandsStyle);
	writer.WriteInteger("Visuals", "WeaponsStyle", g_Vars->Visuals.Chams.WeaponsStyle);

	writer.WriteInteger("Aimbot", "DelayAfterKill", g_Vars->Aimbot.DelayAfterKill);

	writer.WriteFloat("Colors", "Weap", g_Vars->Colors.Weap[0]);
	writer.WriteFloat("Colors", "Weap1", g_Vars->Colors.Weap[1]);
	writer.WriteFloat("Colors", "Weap2", g_Vars->Colors.Weap[2]);

	writer.WriteFloat("Colors", "Hands", g_Vars->Colors.Hands[0]);
	writer.WriteFloat("Colors", "Hands1", g_Vars->Colors.Hands[1]);
	writer.WriteFloat("Colors", "Hands2", g_Vars->Colors.Hands[2]);
}

const char* Tabs[] =
{
	"Aimbot",
	"Trigger",
	"Visuals",
	"Changers",
	"Colors",
	"Misc"
};

int ParseSkins()
{
	valve_parser::Document doc;
	auto r = doc.Load(".\\csgo\\scripts\\items\\items_game.txt", valve_parser::ENCODING::UTF8);
	if (!r)
		return 1;

	valve_parser::Document english;
	r = english.Load(".\\csgo\\resource\\csgo_english.txt", valve_parser::ENCODING::UTF16_LE);
	if (!r)
		return 2;

	auto weaponSkinCombo = doc.BreadthFirstSearch("weapon_icons");
	if (!weaponSkinCombo || !weaponSkinCombo->ToObject())
		return 3;

	auto skinDataVec = doc.BreadthFirstSearchMultiple("paint_kits");
	if (!skinDataVec.size())
		return 4;

	auto PaintKitNames = english.BreadthFirstSearch("Tokens");
	if (!PaintKitNames || !PaintKitNames->ToObject())
		return 5;

	std::vector<std::string> weaponNames = {
		"deagle",
		"elite",
		"fiveseven",
		"glock",
		"ak47",
		"aug",
		"awp",
		"famas",
		"g3sg1",
		"galilar",
		"m249",
		"m4a1_silencer",
		"m4a1",
		"mac10",
		"p90",
		"ump45",
		"xm1014",
		"bizon",
		"mag7",
		"negev",
		"sawedoff",
		"tec9",
		"hkp2000",
		"mp7",
		"mp9",
		"nova",
		"p250",
		"scar20",
		"sg556",
		"ssg08",
		"usp_silencer",
		"cz75a",
		"revolver",
		"knife_m9_bayonet",
		"bayonet",
		"knife_flip",
		"knife_gut",
		"knife_karambit",
		"knife_tactical",
		"knife_falchion",
		"knife_survival_bowie",
		"knife_butterfly",
		"knife_push",
		"knife_ursus",
		"knife_gypsy_jackknife",
		"knife_stiletto",
		"knife_widowmaker"
	};

	for (auto child : weaponSkinCombo->children)
	{
		if (child->ToObject())
		{
			for (auto weapon : weaponNames)
			{
				auto skinName = child->ToObject()->GetKeyByName("icon_path")->ToKeyValue()->Value.toString();
				auto pos = skinName.find(weapon);

				if (pos != std::string::npos)
				{
					auto pos2 = skinName.find_last_of('_');
					g_Vars->Skinchanger.weaponSkins[weapon].insert(
						skinName.substr(pos + weapon.length() + 1,
							pos2 - pos - weapon.length() - 1)
					);
					break;
				}
			}
		}
	}


	for (auto skinData : skinDataVec)
	{
		if (skinData->ToObject())
		{
			for (auto skin : skinData->children)
			{
				if (skin->ToObject())
				{
					skinInfo si;
					si.paintkit = skin->ToObject()->name.toInt();

					auto skinName = skin->ToObject()->GetKeyByName("name")->ToKeyValue()->Value.toString();
					auto tagNode = skin->ToObject()->GetKeyByName("description_tag");
					if (tagNode)
					{
						std::string tag = tagNode->ToKeyValue()->Value.toString();
						tag = tag.substr(1, std::string::npos);
						std::transform(tag.begin(), tag.end(), tag.begin(), towlower);
						si.tagName = tag;
					}

					auto keyVal = skin->ToObject()->GetKeyByName("seed");
					if (keyVal != nullptr)
						si.seed = keyVal->ToKeyValue()->Value.toInt();

					g_Vars->Skinchanger.skinMap[skinName] = si;
				}
			}
		}
	}

	for (auto child : PaintKitNames->children)
	{
		if (child->ToKeyValue())
		{
			std::string key = child->ToKeyValue()->Key.toString();
			std::transform(key.begin(), key.end(), key.begin(), towlower);
			if (key.find("paintkit") != std::string::npos &&
				key.find("tag") != std::string::npos)
			{
				g_Vars->Skinchanger.skinNames[key] = child->ToKeyValue()->Value.toString();
			}
		}
	}

	return 0;
}

const char* weaponnames(int id)
{
	switch (id)
	{
	case 1:
		return "deagle";
	case 2:
		return "elite";
	case 3:
		return "fiveseven";
	case 4:
		return "glock";
	case 7:
		return "ak47";
	case 8:
		return "aug";
	case 9:
		return "awp";
	case 10:
		return "famas";
	case 11:
		return "g3sg1";
	case 13:
		return "galilar";
	case 14:
		return "m249";
	case 60:
		return "m4a1_silencer";
	case 16:
		return "m4a1";
	case 17:
		return "mac10";
	case 19:
		return "p90";
	case 23:
		return "mp7";
	case 24:
		return "ump45";
	case 25:
		return "xm1014";
	case 26:
		return "bizon";
	case 27:
		return "mag7";
	case 28:
		return "negev";
	case 29:
		return "sawedoff";
	case 30:
		return "tec9";
	case 32:
		return "hkp2000";
	case 33:
		return "mp7";
	case 34:
		return "mp9";
	case 35:
		return "nova";
	case 36:
		return "p250";
	case 38:
		return "scar20";
	case 39:
		return "sg556";
	case 40:
		return "ssg08";
	case 61:
		return "usp_silencer";
	case 63:
		return "cz75a";
	case 64:
		return "revolver";
	case 508:
		return "knife_m9_bayonet";
	case 500:
		return "bayonet";
	case 505:
		return "knife_flip";
	case 506:
		return "knife_gut";
	case 507:
		return "knife_karambit";
	case 509:
		return "knife_tactical";
	case 512:
		return "knife_falchion";
	case 514:
		return "knife_survival_bowie";
	case 515:
		return "knife_butterfly";
	case 516:
		return "knife_push";
	case 520:
		return "knife_gypsy_jackknife";
	case 522:
		return "knife_stiletto";
	case 519:
		return "knife_ursus";
	case 523:
		return "knife_widowmaker";
	default:
		return "";
	}
}

void CMenu::lAimbot() {
	int WeaponID = 0; char buf[255];
	if (I::Engine->IsInGame() && I::Engine->IsConnected())
	{
		C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
		if (LocalPlayer)
		{
			C_BaseCombatWeapon* Weapon = LocalPlayer->GetActiveWeapon();
			if (Weapon)
			{
				WeaponID = Weapon->GetItemDefinitionIndex();
				if (WeaponID != 0)
					sprintf_s(buf, "%s", Weapon->GetWeaponName().c_str());
			}
		}
	}


	ImGui::Columns(2, 0, false);
	if (WeaponID == 0)
	{
		ImGui::BeginGroupBox(charenc("error"), ImVec2(220, 35));
		{
			ImGui::Text(charenc("cant find any weapon :/"));
		}
		ImGui::EndGroupBox();
		ImGui::NextColumn();
	}
	else if (WeaponID != 0)
	{
		ImGui::BeginGroupBox(charenc("Settings##mm"), ImVec2(-1, 110));

		ImVec2 weaponNameSize = ImGui::CalcTextSize(buf);

		ImGui::Text(charenc("Current weapon is: ")); ImGui::SameLine(ImGui::GetWindowWidth() - weaponNameSize.x - 8.0f);  ImGui::Text(buf);
		ImGui::Text(charenc("Enable")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Enable"), &g_Vars->Aimbot.Enabled);
		ImGui::Text(charenc("On key")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##On key##l"), &g_Vars->Aimbot.OnKey);
		ImGui::Hotkey(charenc("Key##l"), &g_Vars->Aimbot.Key, ImVec2(-1, 25));
		ImGui::EndGroupBox();

		ImGui::BeginGroupBox(charenc("Mods"), ImVec2(-1, 60));
		ImGui::Text(charenc("BackTrack")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##BackTrack"), &g_Vars->Aimbot.BackTrack);
		ImGui::SliderInt(charenc("Ticks"), &g_Vars->Aimbot.BT_ticks, 1, 12);
		ImGui::EndGroupBox();

		ImGui::BeginGroupBox(charenc("Filters"), ImVec2(-1, 105));
		ImGui::Text(charenc("On teammates")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##On_team"), &g_Vars->Aimbot.OnTeam);
		ImGui::Text(charenc("Disable on smoke")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##SmokeCheck"), &g_Vars->Aimbot.SmokeCheck);
		ImGui::Text(charenc("Disable when flashed")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Fkl"), &g_Vars->Aimbot.FlashCheck);
		ImGui::SliderInt(charenc("Kill-delay"), &g_Vars->Aimbot.DelayAfterKill, 0, 350);
		ImGui::EndGroupBox();

		ImGui::NextColumn();

		ImGui::BeginGroupBox(charenc("pSilent aimbot"), ImVec2(-1, 60));
		ImGui::Text(charenc("Enable")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Enable"), &g_Vars->Skinchanger.W[WeaponID].pSilent);
		ImGui::SliderFloat(charenc("FOV"), &g_Vars->Skinchanger.W[WeaponID].pSilentFOV, 0.0f, 10.0f, "%.1f");
		ImGui::EndGroupBox();

		if(g_Vars->Skinchanger.W[WeaponID].Nearest)
		ImGui::BeginGroupBox(charenc("Aimbot settings"), ImVec2(-1, 160));
		else
			ImGui::BeginGroupBox(charenc("Aimbot settings"), ImVec2(-1, 180));
		ImGui::Text(charenc("Nearest")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Nearest"), &g_Vars->Skinchanger.W[WeaponID].Nearest);
		ImGui::SliderFloat(charenc("FOV"), &g_Vars->Skinchanger.W[WeaponID].FOV, 0.1f, 10.0, "%.1f");
		ImGui::SliderFloat(charenc("Smooth"), &g_Vars->Skinchanger.W[WeaponID].Smooth, 0.1f, 10.0f, "%.1f");
		ImGui::SliderFloat(charenc("RCS on X"), &g_Vars->Skinchanger.W[WeaponID].rcs_x, 0.0f, 100.0f, "%.1f");
		ImGui::SliderFloat(charenc("RCS on Y"), &g_Vars->Skinchanger.W[WeaponID].rcs_y, 0.0f, 100.0f, "%.1f");
		ImGui::SliderInt(charenc("RCS after X-shots"), &g_Vars->Skinchanger.W[WeaponID].rcs_start, 0, 10);
		if (!g_Vars->Skinchanger.W[WeaponID].Nearest)
			ImGui::SliderInt(charenc("Bone"), &g_Vars->Skinchanger.W[WeaponID].bone, 0, 8);
		ImGui::EndGroupBox();

	}
	ImGui::Columns(1);
}

void CMenu::Visuals() {
	if (VisualsSubTab == 0)
	{
		ImGui::Columns(2, 0, false);
		{
			ImGui::BeginGroupBox(charenc("ESP settings"), ImVec2(-1, 110));
			{
				ImGui::Text(charenc("Enable")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Enable"), &g_Vars->Visuals.Enabled);
				ImGui::Text(charenc("On teammates")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Onteammates"), &g_Vars->Visuals.Filter.Teammates);
				ImGui::Combo(charenc("##chams_kind##box"), &g_Vars->Visuals.Chams.Kind, "Default\0Classic\0\0", -1);
				ImGui::Text(charenc("VisibleCheck")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##VisibleCheck"), &g_Vars->Visuals.VisibleCheck);
			}
			ImGui::EndGroupBox();

			ImGui::BeginGroupBox(charenc("World ESP"), ImVec2(-1, 110));
			{
				ImGui::Text(charenc("C4")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##C4"), &g_Vars->Visuals.DroppedC4);
				ImGui::Text(charenc("Dropped weapons")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Dropped_weapons"), &g_Vars->Visuals.DroppedWeap);
				ImGui::Text(charenc("Bomb timer")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##BombTimer"), &g_Vars->Visuals.BombTimer);
				ImGui::Text(charenc("Hostages")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Hostages"), &g_Vars->Visuals.Hostage);
			}
			ImGui::EndGroupBox();
		}
		ImGui::NextColumn();
		{
			ImGui::BeginGroupBox(charenc("Player ESP"), ImVec2(-1, 278));
			{
				ImGui::Text(charenc("InfoBar")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##InfoBar"), &g_Vars->Visuals.InfoBox);
				ImGui::Text(charenc("Box")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Box"), &g_Vars->Visuals.Box);
				ImGui::Text(charenc("Health")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Health"), &g_Vars->Visuals.HPbar);
				ImGui::Text(charenc("Armor")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Armor"), &g_Vars->Visuals.ARMORbar);
				ImGui::Text(charenc("Nickname")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Nickname"), &g_Vars->Visuals.NickName);
				ImGui::Text(charenc("Defusing")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Defusing"), &g_Vars->Visuals.Defusing);
				ImGui::Text(charenc("Weapon")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Weapon"), &g_Vars->Visuals.WeaponIC);
				ImGui::Combo(charenc("##styleweap"), &g_Vars->Visuals.WeaponStyle, "Icons\0Text\0\0", -1);
				ImGui::Text(charenc("Ammo")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Ammo"), &g_Vars->Visuals.Ammo);
				ImGui::Text(charenc("Skeleton")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Skeleton"), &g_Vars->Visuals.Skeleton);
				ImGui::SliderFloat(charenc("Thickness"), &g_Vars->Visuals.SkeletonSize, 0.1f, 3.5f, "%.1f");
			}
			ImGui::EndGroupBox();
		}
		ImGui::Columns(1);
	}
	else if (VisualsSubTab == 1)
	{
		ImGui::Columns(2, 0, false);
		{
			ImGui::BeginGroupBox(charenc("Glow"), ImVec2(-1, 85));
			{
				ImGui::Text(charenc("Enable")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Enable_glow"), &g_Vars->Visuals.Glow.Enabled);
				ImGui::Text(charenc("Bloom")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Glow_bloom"), &g_Vars->Visuals.Glow.GlowBloom);
				ImGui::SliderInt(charenc("Alpha"), &g_Vars->Visuals.Glow.Alpha, 1.0f, 255);
			}
			ImGui::EndGroupBox();

			ImGui::BeginGroupBox(charenc("Chams"), ImVec2(-1, 180));
			{
				ImGui::Text(charenc("Enable")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Enable"), &g_Vars->Visuals.Chams.Enabled);
				ImGui::Combo(charenc("##chams_kind##boxd"), &g_Vars->Visuals.Chams.Style, "Classic\0Flat\0Metallic\0\0", -1);
				ImGui::Text(charenc("Hands")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Hands"), &g_Vars->Visuals.Chams.Hands);
				ImGui::Combo(charenc("##hands_s##boxd"), &g_Vars->Visuals.Chams.HandsStyle, "Classic\0Flat\0Metallic\0\0", -1);
				ImGui::Text(charenc("Weapons")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Weapons"), &g_Vars->Visuals.Chams.Weapons);
				ImGui::Combo(charenc("##WeaponsStyle##boxd"), &g_Vars->Visuals.Chams.WeaponsStyle, "Classic\0Flat\0Metallic\0\0", -1);
				ImGui::Text(charenc("Chams XQZ")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Chams XQZ"), &g_Vars->Visuals.Chams.Ignorez);
			}
			ImGui::EndGroupBox();
		}
		ImGui::NextColumn();
		{
			ImGui::BeginGroupBox(charenc("Other ESP"), ImVec2(-1, 301));
			{
				ImGui::Text(charenc("Draw FOV")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##DrawFOV"), &g_Vars->Visuals.FOV);
				ImGui::Text(charenc("Draw backtrack")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Draw_BackTrack"), &g_Vars->Aimbot.BackTrackV);
				ImGui::Text(charenc("Hitmarker")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Hitmarkergh3"), &g_Vars->Visuals.Hitmarker);
				ImGui::Text(charenc("No flash")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##NoFlash"), &g_Vars->Visuals.NoFlash);
				ImGui::Text(charenc("Recoil crosshair")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##RecoilCS"), &g_Vars->Visuals.RecoilCS);
				ImGui::Text(charenc("In-game radar")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##InGameRadar"), &g_Vars->Visuals.InGameRadar);
				ImGui::Text(charenc("Radar")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Radar"), &g_Vars->Misc.Radar);
				ImGui::Text(charenc("Radar enemy only")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##RadarEnemyOnly"), &g_Vars->Misc.RadarEnemyOnly);
				ImGui::Text(charenc("Grenade helper")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Granade_helper"), &g_Vars->Visuals.GH);
				ImGui::Text(charenc("Grenades")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##DrawGrenades"), &g_Vars->Visuals.DrawGrenades);
				ImGui::SliderInt(charenc("FOV"), &g_Vars->Misc.FOV, 0, 180);
				ImGui::SliderInt(charenc("Model view"), &g_Vars->Misc.MODEL_FOV, 0, 180);
			}
			ImGui::EndGroupBox();
		}
		ImGui::Columns(1);
	}

	ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 74.0f);
	ImGui::SetCursorPosY(335.0f);


	ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 0.40f);
	ImGui::GetWindowDrawList()->AddRect(ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth() - 75.0f, ImGui::GetWindowPos().y + 334.0f), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth() - 43.0f, ImGui::GetWindowPos().y + 356.0f), ImGui::GetColorU32(ImGuiCol_Border));
	if (ImGui::Button(charenc("##left"), ImVec2(30.f, 20.0f)))
		VisualsSubTab = 0;



	ImGui::SameLine();
	ImGui::GetWindowDrawList()->AddRect(ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth() - 37.0f, ImGui::GetWindowPos().y + 334.0f), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth() - 5.0f, ImGui::GetWindowPos().y + 356.0f), ImGui::GetColorU32(ImGuiCol_Border));
	if (ImGui::Button(charenc("##right"), ImVec2(30.f, 20.0f)))
		VisualsSubTab = 1;
	ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 0.80f);

	if (VisualsSubTab == 1)
	{
		ImGui::GetWindowDrawList()->AddText(ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth() - 69.0f, ImGui::GetWindowPos().y + 334.0f), 18.0f, ImGui::GetColorU32(ImVec4(1.00f, 1.00f, 1.00f, 0.80f)), "<<");
		ImGui::GetWindowDrawList()->AddText(ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth() - 30.0f, ImGui::GetWindowPos().y + 334.0f), 18.0f, ImGui::GetColorU32(ImGuiCol_CheckMark), ">>");

	}
	else if (VisualsSubTab == 0)
	{
		ImGui::GetWindowDrawList()->AddText(ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth() - 69.0f, ImGui::GetWindowPos().y + 334.0f), 18.0f, ImGui::GetColorU32(ImGuiCol_CheckMark), "<<");
		ImGui::GetWindowDrawList()->AddText(ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth() - 30.0f, ImGui::GetWindowPos().y + 334.0f), 18.0f, ImGui::GetColorU32(ImVec4(1.00f, 1.00f, 1.00f, 0.80f)), ">>");
	}

	ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.12f, 0.11f, 0.11f, 1.00f);
}

bool IsUtility(ItemDefinitionIndexx index)
{
	switch (index)
	{
	case ItemDefinitionIndexx::ITEM_NONE:
	case ItemDefinitionIndexx::WEAPON_C4:
	case ItemDefinitionIndexx::WEAPON_FLASH:
	case ItemDefinitionIndexx::WEAPON_HE:
	case ItemDefinitionIndexx::WEAPON_INC:
	case ItemDefinitionIndexx::WEAPON_MOLOTOV:
	case ItemDefinitionIndexx::WEAPON_SMOKE:
	case ItemDefinitionIndexx::WEAPON_DECOY:
	case ItemDefinitionIndexx::WEAPON_TASER:
	case ItemDefinitionIndexx::WEAPON_KNIFE_T:
	case ItemDefinitionIndexx::WEAPON_KNIFE_CT:
	case ItemDefinitionIndexx::GLOVE_T_SIDE:
	case ItemDefinitionIndexx::GLOVE_CT_SIDE:
	case ItemDefinitionIndexx::GLOVE_SPORTY:
	case ItemDefinitionIndexx::GLOVE_SLICK:
	case ItemDefinitionIndexx::GLOVE_LEATHER_WRAP:
	case ItemDefinitionIndexx::GLOVE_STUDDED_BLOODHOUND:
	case ItemDefinitionIndexx::GLOVE_MOTORCYCLE:
	case ItemDefinitionIndexx::GLOVE_SPECIALIST:
	case ItemDefinitionIndexx::GLOVE_HYDRA:
		return true;
	default:
		return false;
	}
}

void CMenu::initializeskins()
{
	static bool once = false;

	if (!once)
	{
		ParseSkins();
		once = true;
	}
}

bool Contains(const std::string &word, const std::string &sentence) {
	if (word == "" || sentence == "")
		return true;

	return sentence.find(word) != std::string::npos;
}

std::string ToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), (int(*)(int))std::tolower);

	return str;
}

struct hud_weapons_t {
	std::int32_t* get_weapon_count() {
		return reinterpret_cast<std::int32_t*>(std::uintptr_t(this) + 0x80);
	}
};

template<class T>
static T* FindHudElement(const char* name)
{
	static auto pThis = *reinterpret_cast<DWORD**>(g_Utils->FindPatternIDA("client_panorama.dll", "B9 ? ? ? ? E8 ? ? ? ? 85 C0 0F 84 ? ? ? ? 8D 58") + 1);
	static auto find_hud_element = reinterpret_cast<DWORD(__thiscall*)(void*, const char*)>(g_Utils->FindPatternIDA("client_panorama.dll", "55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39 77 28"));
	return (T*)find_hud_element(pThis, name);
}

void FullUpdate2()
{
	static auto clear_hud_weapon_icon_fn =
		reinterpret_cast<std::int32_t(__thiscall*)(void*, std::int32_t)>(
			g_Utils->FindPatternIDA("client_panorama.dll", "55 8B EC 51 53 56 8B 75 08 8B D9 57 6B FE 2C"));
	auto element = FindHudElement<std::uintptr_t*>("CCSGO_HudWeaponSelection");
	auto hud_weapons = reinterpret_cast<hud_weapons_t*>(std::uintptr_t(element) - 0xA0);
	if (hud_weapons == nullptr)
		return;

	if (!*hud_weapons->get_weapon_count())
		return;
	for (std::int32_t i = 0; i < *hud_weapons->get_weapon_count(); i++)
		i = clear_hud_weapon_icon_fn(hud_weapons, i);
	typedef void(*ForceUpdate) (void);
	ForceUpdate FullUpdate = (ForceUpdate)g_Utils->FindPatternIDA("engine.dll", "A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85");
	FullUpdate();
}

int SafeWeaponID()
{
	C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
	if (!LocalPlayer || LocalPlayer == NULL || LocalPlayer == nullptr)
		return 0;
	C_BaseCombatWeapon*weap = LocalPlayer->GetActiveWeapon();
	if (!weap || weap == NULL || weap == nullptr)
		return 0;

	return weap->GetItemDefinitionIndex();
}

const char* knifeModels[] =
{
	"Bayonet",
	"Flip",
	"Gut",
	"Karambit",
	"M9 bayonet",
	"Huntsman",
	"Falchion",
	"Bowie",
	"Butterfly",
	"Dagger",
	"Navaja",
	"Stiletto",
	"Ursus",
	"Talon"
};
int SkinsSubTab;
void CMenu::Skins() {
	static char filterWeapons[32];
	static char filterSkins[32];

		int WeaponID = 0; char buf[255] = "";
		if (I::Engine->IsInGame() && I::Engine->IsConnected())
		{
			C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
			if (LocalPlayer)
			{
				C_BaseCombatWeapon* Weapon = LocalPlayer->GetActiveWeapon();

				if (Weapon) {
					WeaponID = Weapon->GetItemDefinitionIndex();
					if (WeaponID != 0)
						sprintf_s(buf, "Enable for %s", Weapon->GetWeaponName().c_str());
				}
			}
		}

		ImGui::Columns(2, NULL, false);
		{
			ImGui::BeginGroupBox(charenc("Skinchanger"), ImVec2(-1.0f, 287.0f));
			{
				if (SafeWeaponID() == 0)
					ImGui::Text(charenc("Cant find weapon.."));
				else
				{
					ImGui::Text(buf); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##:thinking:2"), &g_Vars->Skinchanger.W[SafeWeaponID()].ChangerEnabled);
				}
				ImGui::Text(charenc("Live StatTrak")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Live StatThhrak"), &g_Vars->Skinchanger.W[SafeWeaponID()].LiveSC);
				ImGui::PushItemWidth(-1);
				ImGui::Text(charenc("Search:")); ImGui::SameLine(); ImGui::InputText(("##FILTERSKINS2"), filterSkins, ARRAYSIZE(filterSkins));
				ImGui::PopItemWidth();
				std::string skinName = weaponnames(SafeWeaponID());
				ImGui::ListBoxHeader(("##SKINS3"), ImVec2(-1, 125));
				std::string skinStr = "";
				int curItem = -1;
				int s = 0;
				for (auto skin : g_Vars->Skinchanger.weaponSkins[skinName])
				{
					int pk = g_Vars->Skinchanger.skinMap[skin].paintkit;
					if (pk == g_Vars->Skinchanger.W[SafeWeaponID()].ChangerSkin)
						curItem = s;
					bool selected = g_Vars->Skinchanger.W[SafeWeaponID()].ChangerSkin == pk;

					skinStr = g_Vars->Skinchanger.skinNames[g_Vars->Skinchanger.skinMap[skin].tagName].c_str();
					skinStr += " | ";
					skinStr += std::to_string(g_Vars->Skinchanger.skinMap[skin].paintkit);
					if (!Contains(ToLower(std::string(filterSkins)), ToLower(skinStr)))
						continue;
					if (ImGui::Selectable(skinStr.c_str(), selected))
					{
						pk = g_Vars->Skinchanger.skinMap[skin].paintkit;
						g_Vars->Skinchanger.W[SafeWeaponID()].ChangerSkin = pk;
						break;
					}
					s++;
				}
				ImGui::ListBoxFooter();
				ImGui::SliderFloat(charenc("Wear"), &g_Vars->Skinchanger.W[SafeWeaponID()].Wear, 0.0f, 1.0f);
				ImGui::InputInt(charenc("ST"), &g_Vars->Skinchanger.W[SafeWeaponID()].SC);
				ImGui::InputInt(charenc("Seed"), &g_Vars->Skinchanger.W[SafeWeaponID()].Seed);
			}
			ImGui::EndGroupBox();
			ImGui::NextColumn();
			ImGui::BeginGroupBox(charenc("Knife & Glove"), ImVec2(-1.0f, 198.0f));
			{
				ImGui::Text(charenc("KnifeChanger")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##KnifeChanger"), &g_Vars->Skinchanger.KnifeChanger); 
				ImGui::Text(charenc("Advanced knife changer")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##bet_knife"), &g_Vars->Skinchanger.KnifeKillInfoFix);
				ImGui::Combo(charenc("Knife"), &g_Vars->Skinchanger.knifemodel, knifeModels, ARRAYSIZE(knifeModels));
				ImGui::NewLine();
				ImGui::Combo(charenc("Glove"), &g_Vars->Misc.Glove, charenc("No Glove\0\rBloodhound\0\rSport\0\rDriver\0\rWraps\0\rMoto\0\rSpecialist\0\rHydra\0\0"));
				const char* gstr;
				if (g_Vars->Misc.Glove == 1)
				{
					gstr = "Charred\0\rSnakebite\0\rBronzed\0\rGuerilla\0\0";
				}
				else if (g_Vars->Misc.Glove == 2)
				{
					gstr = "Hedge Maze\0\rPandoras Box\0\rSuperconductor\0\rArid\0\Vice\0\Omega\0\Amphibious\0\Bronze Morph\0";
				}
				else if (g_Vars->Misc.Glove == 3)
				{
					gstr = "Lunar Weave\0\rConvoy\0\rCrimson Weave\0\rDiamondback\0\Overtake\0\Racing Green\0\King Snake\0\Imperial Plaid\0";
				}
				else if (g_Vars->Misc.Glove == 4)
				{
					gstr = "Leather\0\rSpruce DDPAT\0\rSlaughter\0\rBadlands\0\Cobalt Skulls\0\Overprint\0\Duct Tape\0\Arboreal\0";
				}
				else if (g_Vars->Misc.Glove == 5)
				{
					gstr = "Eclipse\0\rSpearmint\0\rBoom!\0\rCool Mint\0\Turtle\0\Transport\0\Polygon\0\POW!\0";
				}
				else if (g_Vars->Misc.Glove == 6)
				{
					gstr = "Forest DDPAT\0\rCrimson Kimono\0\rEmerald Web\0\rFoundation\0\Crimson Web\0\Buckshot\0\Fade\0\Mogul\0";
				}
				else if (g_Vars->Misc.Glove == 7)
				{
					gstr = "Case Hardened\0\rRattler\0\rMangrove\0\rEmerald\0\0";
				}
				else
				{
					gstr = "";
				}

				if (!g_Vars->Misc.Glove == 0)
					ImGui::Combo(charenc("##2"), &g_Vars->Misc.GloveSkin, gstr);

				if (ImGui::Button(charenc("Apply settings"), ImVec2(-1, 40)))
					FullUpdate2();
			}
			ImGui::EndGroupBox();
		}
		ImGui::Columns(1);
}

void CMenu::Colors() {

	ImGui::BeginGroupBox(charenc("Colors"), ImVec2(-1.0f, 180.0f));

	ImGui::Columns(3, NULL, false);
	ImGui::ColorEdit3(charenc("Box enemy"), g_Vars->Colors.BoxEnemy, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("Box enemy visible"), g_Vars->Colors.BoxEnemyV, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("InfoBox enemy"), g_Vars->Colors.InfoBoxE, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("InfoBox team"), g_Vars->Colors.InfoBoxT, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);

	ImGui::ColorEdit3(charenc("Box teammate"), g_Vars->Colors.BoxTeam, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("Box teammate visible"), g_Vars->Colors.BoxTeamV, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("Direction"), g_Vars->Colors.Direction, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::NextColumn();
	ImGui::ColorEdit3(charenc("Glow enemy"), g_Vars->Colors.GlowEnemy, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("Chams team visible"), g_Vars->Colors.TeamVisible, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("Chams team hidden"), g_Vars->Colors.TeamIgnorez, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("ESP text"), g_Vars->Colors.ESPtext, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("Skeleton"), g_Vars->Colors.Skeleton, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("Weapons"), g_Vars->Colors.Weap, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::Checkbox(charenc("Change ESP font"), &g_Vars->Menu.ChangeESPFont);
	ImGui::NextColumn();
	ImGui::ColorEdit3(charenc("SoundESP"), g_Vars->Colors.Sound, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("Glow team"), g_Vars->Colors.GlowTeam, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("Chams enemy visible"), g_Vars->Colors.EnemyVisible, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("Chams enemy hidden"), g_Vars->Colors.EnemyIgnorez, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("Menu main color"), g_Vars->Colors.MenuMain, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::ColorEdit3(charenc("Hands"), g_Vars->Colors.Hands, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoSidePreview);
	ImGui::Checkbox(charenc("Change MENU font"), &g_Vars->Menu.ChangeMenuFont);
	ImGui::Columns(1);

	ImGui::EndGroupBox();
	ImGui::BeginGroupBox(charenc("Custom fonts"), ImVec2(-1.0f, 90.0f));
	ImGui::SetCursorPosY(10.f);
	ImGui::InputText(charenc("Windows font folder##fontfolder"), g_Vars->Menu.FontFolder, 128); 
	ImGui::InputText(charenc("ESP font##fontname"), g_Vars->Menu.ESPFont, 128);
	ImGui::InputText(charenc("Menu font##fontname"), g_Vars->Menu.MenuFont, 128);
	ImGui::EndGroupBox();
}

void CMenu::Misc() {

	ImGui::Columns(2, 0, false);

	ImGui::BeginGroupBox(charenc("First part##misc"), ImVec2(-1.f, 184.f));

	ImGui::Text(charenc("Bunny hop")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Bhop"), &g_Vars->Misc.Bhop);
	ImGui::Text(charenc("Auto strafe")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##AutoStrafe"), &g_Vars->Misc.AutoStrafe);
	ImGui::SliderFloat(charenc("Left"), &g_Vars->Misc.StrafeFirst, 0.0f, 450.0f, "%.0f");
	ImGui::SliderFloat(charenc("Right"), &g_Vars->Misc.StrafeSecond, 0.0f, 450.0f, "%.0f");
	ImGui::Text(charenc("Spectator list")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##SpectatorList"), &g_Vars->Misc.SpectatorList);
	ImGui::Text(charenc("Auto accept")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##AutoAccept"), &g_Vars->Misc.AutoAccept);
	ImGui::Text(charenc("Rank review")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##RankReview"), &g_Vars->Misc.RankReview);

	ImGui::EndGroupBox();

	ImGui::NextColumn();


	if(g_Vars->Misc.TagChanger == 2 || g_Vars->Misc.TagChanger == 3)
		ImGui::BeginGroupBox(charenc("Second part##misc"), ImVec2(-1.f, 158.f));
	else
		ImGui::BeginGroupBox(charenc("Second part##misc2"), ImVec2(-1.f, 135.f));

	ImGui::Text(charenc("Auto pistol")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##AutoPistol"), &g_Vars->Misc.AutoPistol);
	ImGui::Text(charenc("Sniper crosshair")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##SniperCross"), &g_Vars->Misc.SniperCross);
	ImGui::Text(charenc("Clan tag changer")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##ClanTagChanger"), &g_Vars->Misc.ClanTagChanger);
	ImGui::Text(charenc("Legit AA [freezed]")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##LegitAA"), &g_Vars->Misc.LegitAA);
	ImGui::Combo(charenc("##TagChanger"), &g_Vars->Misc.TagChanger, "Elysium static\0Elysium animated\0Custom\0Custom animated\0\0", -1);
	if (g_Vars->Misc.TagChanger == 2)
	{
		ImGui::InputText(charenc("##Tag"), g_Vars->Misc.Tag, 128);
		ImGui::SameLine();
		if (ImGui::Button(charenc("Apply")))
			g_Globals->DoCustomAnimUpdt = true;
	}
	else if (g_Vars->Misc.TagChanger == 3)
	{
		ImGui::InputText(charenc("##Tag2"), g_Vars->Misc.Tag, 128);
		ImGui::SameLine();
		if (ImGui::Button(charenc("Apply")))
			g_Globals->DoCustomAnimUpdt = true;
	}

	ImGui::EndGroupBox();

	ImGui::BeginGroupBox(charenc("Config system"), ImVec2(-1.0f, 38.f));
	ImGui::SetCursorPosY(10.f);
	ImGui::InputText(charenc("##CFG-name"), g_Vars->Menu.configname, 128); ImGui::SameLine();
	if (ImGui::Button(charenc("Save"))) SaveCFG(); ImGui::SameLine();
	if (ImGui::Button(charenc("Load"))) ReadCFG();

	ImGui::EndGroupBox();

	ImGui::Columns(1);
}

void CMenu::lTriggerbot() {
	ImGui::Columns(2, 0, false);
	ImGui::BeginGroupBox(charenc("Settings##trigger"), ImVec2(-1.f, 90.f));
	ImGui::Text(charenc("Enable")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Enable"), &g_Vars->Triggerbot.Enabled);
	ImGui::Text(charenc("On key")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##On_key"), &g_Vars->Triggerbot.OnKey);
	ImGui::Hotkey(charenc("Key"), &g_Vars->Triggerbot.Key, ImVec2(-1, 25));
	ImGui::EndGroupBox();
	ImGui::BeginGroupBox(charenc("Filters##trigger"), ImVec2(-1.f, 160.f));
	ImGui::Text(charenc("On teammates")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##On_team"), &g_Vars->Triggerbot.OnTeam);
	ImGui::Text(charenc("Disable on smoke")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##SmokeCheck"), &g_Vars->Triggerbot.SmokeCheck);
	ImGui::Text(charenc("Disable when flashed")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Fkl"), &g_Vars->Triggerbot.FlashCheck);
	ImGui::SliderInt(charenc("Delay (ms)"), &g_Vars->Triggerbot.Delay, 1, 1000);
	ImGui::Text(charenc("Hitchance")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Hitchance"), &g_Vars->Triggerbot.Hitchance);
	ImGui::SliderInt(charenc("Hitchance amount"), &g_Vars->Triggerbot.HitchanceAM, 1, 100);
	ImGui::EndGroupBox();
	ImGui::NextColumn();
	ImGui::BeginGroupBox(charenc("Target##trigger"), ImVec2(-1.f, 132.f));
	ImGui::Text(charenc("On head")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Head"), &g_Vars->Triggerbot.Head);
	ImGui::Text(charenc("On chest")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Chest"), &g_Vars->Triggerbot.Chest);
	ImGui::Text(charenc("On stomach")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Stomach"), &g_Vars->Triggerbot.Stomach);
	ImGui::Text(charenc("On arms")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Arms"), &g_Vars->Triggerbot.Arms);
	ImGui::Text(charenc("On legs")); ImGui::SameLine(ImGui::GetWindowWidth() - 30); ImGui::Checkbox(charenc("##Legs"), &g_Vars->Triggerbot.Legs);
	ImGui::EndGroupBox();
	ImGui::Columns(1);
}

void CMenu::DoTab() {
	switch (g_Vars->Menu.ShowedPage)
	{
	case 0:
		lAimbot();
		break;
	case 1:
		lTriggerbot();
		break;
	case 2:
		Visuals();
		break;
	case 3:
		Skins();
		break;
	case 4:
		Colors();
		break;
	case 5:
		Misc();
		break;
	}
}

void CMenu::Menu() {

	if (g_Vars->Misc.Radar)
		DrawRader();

	ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	if (g_Vars->Misc.SpectatorList)
		DrawSL();

	ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.12f, 0.11f, 0.11f, 1.00f);
	if (g_Vars->Menu.Opened)
	{
		ImGui::PushFont(g_Globals->MENU_FONT);
		ImVec2 oldPadding = ImGui::GetStyle().WindowPadding;
		ImVec2 oldSpacing = ImGui::GetStyle().ItemSpacing;
		ImVec2 oldDisplaySafeAreaPadding = ImGui::GetStyle().DisplaySafeAreaPadding;
		ImGui::GetStyle().DisplaySafeAreaPadding = ImVec2(0, 0);
		ImGui::GetStyle().WindowPadding = ImVec2(0, 0);
		ImGui::GetStyle().ItemSpacing = ImVec2(0, 0);
		ImGui::Begin(charenc("##h5g5gf54"), NULL, ImVec2(800, 420), -1.0f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		{
			ImGui::BeginGroup(); {
				for (int i = 0; i < ARRAYSIZE(Tabs); i++) {
					ImGui::SameLine();
					if (ImGui::Tab(Tabs[i], ImVec2(133.3f, 30), (g_Vars->Menu.ShowedPage == i), i))
						g_Vars->Menu.ShowedPage = i;
				}
			} ImGui::EndGroup();
			ImGui::GetStyle().WindowPadding = oldPadding;
			ImGui::GetStyle().ItemSpacing = oldSpacing;
			ImGui::GetStyle().DisplaySafeAreaPadding = oldDisplaySafeAreaPadding;

			ImGui::BeginChild(charenc("g45g55##main_framegg2"), ImVec2(-1, 360), true);
			DoTab();
			ImGui::EndChild();
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + 390.0f), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x - 1.0f, ImGui::GetWindowPos().y + 420.0f), ImGui::GetColorU32(ImGuiCol_MainColor));
			ImGui::GetWindowDrawList()->AddLine(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + 388.0f), ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + 420.0f), ImGui::GetColorU32(ImGuiCol_Border));
			ImGui::GetWindowDrawList()->AddLine(ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x - 2.0f, ImGui::GetWindowPos().y + 388.0f), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x - 2.0f, ImGui::GetWindowPos().y + 420.0f), ImGui::GetColorU32(ImGuiCol_Border));
			ImGui::GetWindowDrawList()->AddLine(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + 419.0f), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x - 2.0f, ImGui::GetWindowPos().y + 419.0f), ImGui::GetColorU32(ImGuiCol_Border));
			ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 0.40f);
			ImGui::Text(""); char* HeckName = "ElysiumProject, build 2.4.0";
			ImVec2 HeckNameSize = ImGui::CalcTextSize(HeckName);  ImGui::SameLine(ImGui::GetWindowWidth() - HeckNameSize.x - 10.0f); ImGui::Text(HeckName);
			ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.12f, 0.11f, 0.11f, 1.00f);
		} ImGui::End(); ImGui::PopFont();
	}

}

Vector2D RotatePoint(Vector EntityPos, Vector LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool* viewCheck)
{
	float r_1, r_2;
	float x_1, y_1;

	r_1 = -(EntityPos.y - LocalPlayerPos.y);
	r_2 = EntityPos.x - LocalPlayerPos.x;
	float Yaw = angle - 90.0f;

	float yawToRadian = Yaw * (float)(M_PI / 180.0F);
	x_1 = (float)(r_2 * (float)cos((double)(yawToRadian)) - r_1 * sin((double)(yawToRadian))) / 20;
	y_1 = (float)(r_2 * (float)sin((double)(yawToRadian)) + r_1 * cos((double)(yawToRadian))) / 20;

	*viewCheck = y_1 < 0;

	x_1 *= zoom;
	y_1 *= zoom;

	int sizX = sizeX / 2;
	int sizY = sizeY / 2;

	x_1 += sizX;
	y_1 += sizY;

	if (x_1 < 5)
		x_1 = 5;

	if (x_1 > sizeX - 5)
		x_1 = sizeX - 5;

	if (y_1 < 5)
		y_1 = 5;

	if (y_1 > sizeY - 5)
		y_1 = sizeY - 5;

	x_1 += posX;
	y_1 += posY;

	return Vector2D(x_1, y_1);
}

void CMenu::DrawRader()
{
	ImGui::Begin(charenc("##h5g5gf54gdh_radar"), NULL, ImVec2(170, 160), -1.0f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	{
		ImVec2 siz = ImGui::GetWindowSize();
		ImVec2 pos = ImGui::GetWindowPos();
		ImDrawList* DrawList = ImGui::GetWindowDrawList();




		if (I::Engine->IsInGame() && I::Engine->IsConnected() && !I::Engine->IsTakingScreenshot())
		{
			C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
			if (LocalPlayer)
			{
				Vector LocalPos = LocalPlayer->GetEyePosition();
				QAngle ang;
				I::Engine->GetViewAngles(ang);
				for (int i = 0; i < I::Globals->maxClients; i++)
				{
					C_BaseEntity* pBaseEntity = I::EntityList->GetClientEntity(i);

					if (!pBaseEntity)
						continue;

					if (!pBaseEntity->IsValid())
						continue;

					if (pBaseEntity == LocalPlayer)
						continue;

					PlayerInfo_t pInfo;
					I::Engine->GetPlayerInfo(i, &pInfo);

					C_BaseEntity* observerTarget = I::EntityList->GetClientEntityFromHandle(LocalPlayer->GetObserverTargetHandle());
					bool bIsEnemy = (LocalPlayer->GetTeam() != pBaseEntity->GetTeam() || pBaseEntity == observerTarget) ? true : false;

					if (g_Vars->Misc.RadarEnemyOnly && !bIsEnemy)
						continue;

					bool viewCheck = false;
					Vector2D EntityPos = RotatePoint(pBaseEntity->GetOrigin(), LocalPos, pos.x, pos.y, siz.x, siz.y, ang.y, 1, &viewCheck);
					ImU32 clr = (bIsEnemy ? Color::Red() : Color::LightBlue()).GetU32();
					int s = 2;
					DrawList->AddCircleFilled(ImVec2(EntityPos.x, EntityPos.y), 3.5, Color::Black().GetU32());
					DrawList->AddCircleFilled(ImVec2(EntityPos.x, EntityPos.y), 3, clr);
				}
			}
		}

		DrawList->AddLine(ImVec2(pos.x + (siz.x / 2), pos.y + 0), ImVec2(pos.x + (siz.x / 2), pos.y + siz.y), Color::Black().GetU32(), 1.5f);
		DrawList->AddLine(ImVec2(pos.x + 0, pos.y + (siz.y / 2)), ImVec2(pos.x + siz.x, pos.y + (siz.y / 2)), Color::Black().GetU32(), 1.5f);
		
		ImGui::GetWindowDrawList()->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x + siz.x, pos.y), Color::Black().GetU32(), 1.5f);
		ImGui::GetWindowDrawList()->AddLine(ImVec2(pos.x, pos.y + siz.y - 1.0f), ImVec2(pos.x + siz.x, pos.y + siz.y - 1.0f), Color::Black().GetU32(), 1.5f);

		ImGui::GetWindowDrawList()->AddLine(ImVec2(pos.x + 3.5f, pos.y), ImVec2(pos.x + 3.5f, pos.y + siz.y), Color::Black().GetU32(), 1.5f);
		ImGui::GetWindowDrawList()->AddLine(ImVec2(pos.x + siz.x - 5.0f, pos.y), ImVec2(pos.x + siz.x - 5.0f, pos.y + siz.y), Color::Black().GetU32(), 1.5f);

	} ImGui::End();



	/*ImGui::Begin(charenc("Radar"), &g_Vars->Misc.Radar, ImVec2(200, 200), 1.0F, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	{
		ImVec2 siz = ImGui::GetWindowSize();
		ImVec2 pos = ImGui::GetWindowPos();

		ImDrawList* DrawList = ImGui::GetWindowDrawList();

		if (I::Engine->IsInGame() && I::Engine->IsConnected() && !I::Engine->IsTakingScreenshot())
		{
			C_BaseEntity* LocalPlayer = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
			if (LocalPlayer)
			{
				Vector LocalPos = LocalPlayer->GetEyePosition();
				QAngle ang;
				I::Engine->GetViewAngles(ang);
				for (int i = 0; i < I::Globals->maxClients; i++)
				{
					C_BaseEntity* pBaseEntity = I::EntityList->GetClientEntity(i);

					if (!pBaseEntity)
						continue;

					if (!pBaseEntity->IsValid())
						continue;

					if (pBaseEntity == LocalPlayer)
						continue;

					PlayerInfo_t pInfo;
					I::Engine->GetPlayerInfo(i, &pInfo);

					C_BaseEntity* observerTarget = I::EntityList->GetClientEntityFromHandle(LocalPlayer->GetObserverTargetHandle());
					bool bIsEnemy = (LocalPlayer->GetTeam() != pBaseEntity->GetTeam() || pBaseEntity == observerTarget) ? true : false;

					if (g_Vars->Misc.RadarEnemyOnly && !bIsEnemy)
						continue;

					bool viewCheck = false;
					Vector2D EntityPos = RotatePoint(pBaseEntity->GetOrigin(), LocalPos, pos.x, pos.y, siz.x, siz.y, ang.y, 1, &viewCheck);
					ImU32 clr = (bIsEnemy ? Color::Red() : Color::LightBlue()).GetU32();
					int s = 2;
					DrawList->AddCircleFilled(ImVec2(EntityPos.x, EntityPos.y), 3.5, Color::Black().GetU32());
					DrawList->AddCircleFilled(ImVec2(EntityPos.x, EntityPos.y), 3, clr);
				}
			}
		}

		//DrawList->AddRect(ImVec2(pos.x - 6, pos.y - 6), ImVec2(pos.x + siz.x + 6, pos.y + siz.y + 6), Color::Black().GetU32(), 0.0F, -1, 1.5f);
		//DrawList->AddRect(ImVec2(pos.x - 2, pos.y - 2), ImVec2(pos.x + siz.x + 2, pos.y + siz.y + 2), Color::Black().GetU32(), 0.0F, -1, 1);
		//DrawList->AddRect(ImVec2(pos.x - 2, pos.y - 2), ImVec2(pos.x + siz.x + 2, pos.y + siz.y + 2), Color::Black().GetU32(), 0.0F, -1, 2);
		//DrawList->AddRect(ImVec2(pos.x - 2, pos.y - 2), ImVec2(pos.x + siz.x + 2, pos.y + siz.y + 2), Color::Black().GetU32(), 0.0F, -1, 1.1f);


		DrawList->AddRect(ImVec2(pos.x, pos.y), ImVec2(pos.x + siz.x, pos.y + siz.y), Color::Black().GetU32(), 0.0F, -1, 5.0f);
		DrawList->AddLine(ImVec2(pos.x + (siz.x / 2), pos.y + 0), ImVec2(pos.x + (siz.x / 2), pos.y + siz.y), Color::Black().GetU32(), 1.5f);
		DrawList->AddLine(ImVec2(pos.x + 0, pos.y + (siz.y / 2)), ImVec2(pos.x + siz.x, pos.y + (siz.y / 2)), Color::Black().GetU32(), 1.5f);
		//DrawList->AddCircleFilled(ImVec2(pos.x + (siz.x / 2), pos.y + (siz.y / 2)), 2.5f, Color::Black().GetU32());
	}
	ImGui::End();*/
}

std::list<int> GetObservervators(int playerId)
{
	std::list<int> list;

	if (!I::Engine->IsInGame())
		return list;

	C_BaseEntity* player = I::EntityList->GetClientEntity(playerId);
	if (!player)
		return list;

	if (!player->GetAlive())
	{
		C_BaseEntity* observerTarget = I::EntityList->GetClientEntityFromHandle(player->GetObserverTargetHandle());
		if (!observerTarget)
			return list;

		player = observerTarget;
	}

	for (int i = 1; i < I::Engine->GetMaxClients(); i++)
	{
		C_BaseEntity* pPlayer = I::EntityList->GetClientEntity(i);
		if (!pPlayer)
			continue;

		if (pPlayer->IsDormant() || pPlayer->GetAlive())
			continue;

		C_BaseEntity* target = I::EntityList->GetClientEntityFromHandle(pPlayer->GetObserverTargetHandle());

		if (!target)
			continue;

		if (player != target)
			continue;

		list.push_back(i);
	}

	return list;
}

void CMenu::DrawSL()
{
	if (I::Engine->IsInGame() && I::Engine->IsConnected() && !I::Engine->IsTakingScreenshot())
	{
		ImGui::Begin(charenc("##h5g5gf54gdh_SL"), NULL, ImVec2(300, 300), -1.0f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
		{
			ImVec2 siz = ImGui::GetWindowSize();
			ImVec2 pos = ImGui::GetWindowPos();

			ImGui::GetWindowDrawList()->AddLine(ImVec2(pos.x, pos.y), ImVec2(pos.x + siz.x, pos.y), Color::Black().GetU32(), 1.5f);
			ImGui::GetWindowDrawList()->AddLine(ImVec2(pos.x, pos.y + siz.y - 1.0f), ImVec2(pos.x + siz.x, pos.y + siz.y - 1.0f), Color::Black().GetU32(), 1.5f);

			ImGui::GetWindowDrawList()->AddLine(ImVec2(pos.x + 3.5f, pos.y), ImVec2(pos.x + 3.5f, pos.y + siz.y), Color::Black().GetU32(), 1.5f);
			ImGui::GetWindowDrawList()->AddLine(ImVec2(pos.x + siz.x - 5.0f, pos.y), ImVec2(pos.x + siz.x - 5.0f, pos.y + siz.y), Color::Black().GetU32(), 1.5f);

		//ImGui::Begin(charenc("SpectatorList:##ghay"), &g_Vars->Misc.SpectatorList, ImVec2(300, 300), 1.0f, ImGuiWindowFlags_NoScrollbar);
		//{
			for (int playerId : GetObservervators(I::Engine->GetLocalPlayer()))
			{
				C_BaseEntity* player = I::EntityList->GetClientEntity(playerId);

				if (!player)
					continue;

				PlayerInfo_t entityInformation;
				I::Engine->GetPlayerInfo(playerId, &entityInformation);
				char buf[255]; sprintf_s(buf, u8"%s", entityInformation.szName);
				ImGui::Text(charenc(u8" > %s"), buf);
			}
		}
		ImGui::End();
	}
}