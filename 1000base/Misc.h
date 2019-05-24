#pragma once

const float OUTLINE_WIDTH = 3;
const float LINE_WIDTH = 1;

typedef void* (*CreateInterfaceFn) (const char *pName, int *pReturnCode);
typedef void (*pfnDemoCustomDataCallback) (unsigned char *pData, size_t iSize);
typedef unsigned short ModelInstanceHandle_t;
typedef unsigned short MaterialHandle_t;
typedef __int16					int16;
typedef unsigned __int16		uint16;
typedef __int32					int32;
typedef unsigned __int32		uint32;
typedef __int64					int64;
typedef unsigned __int64		uint64;
typedef float matrix3x4[3][4];

#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					"Morph Targets"

typedef struct PlayerInfo_s
{
	__int64         unknown;            //0x0000 
	union
	{
		__int64       steamID64;          //0x0008 - SteamID64
		struct
		{
			__int32     xuidLow;
			__int32     xuidHigh;
		};
	};
	char            szName[128];        //0x0010 - Player Name
	int             userId;             //0x0090 - Unique Server Identifier
	char            szSteamID[20];      //0x0094 - STEAM_X:Y:Z
	char            pad_0x00A8[0x10];   //0x00A8
	unsigned long   iSteamID;           //0x00B8 - SteamID 
	char            szFriendsName[128];
	bool            fakeplayer;
	bool            ishltv;
	unsigned int    customFiles[4];
	unsigned char   filesDownloaded;
} PlayerInfo_t;

enum EntityFlags : int
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_WATERJUMP = (1 << 2),
	FL_ONTRAIN = (1 << 3),
	FL_INRAIN = (1 << 4),
	FL_FROZEN = (1 << 5),
	FL_ATCONTROLS = (1 << 6),
	FL_CLIENT = (1 << 7),
	FL_FAKECLIENT = (1 << 8)
};

#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4	
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10

enum PlayerControls_t
{
	IN_ATTACK = (1 << 0),
	IN_JUMP = (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_CANCEL = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_ATTACK2 = (1 << 11),
	IN_RUN = (1 << 12),
	IN_RELOAD = (1 << 13),
	IN_ALT1 = (1 << 14),
	IN_ALT2 = (1 << 15),
	IN_SCORE = (1 << 16),
	IN_SPEED = (1 << 17),
	IN_WALK = (1 << 18),
	IN_ZOOM = (1 << 19),
	IN_WEAPON1 = (1 << 20),
	IN_WEAPON2 = (1 << 21),
	IN_BULLRUSH = (1 << 22),
	IN_GRENADE1 = (1 << 23),
	IN_GRENADE2 = (1 << 24),
	IN_ATTACK3 = (1 << 25),
};

class CUserCmd
{
public:
	virtual ~CUserCmd() {};
	int       command_number;     // For matching server and client commands for debugging
	int       tick_count;         // The tick the client created this command
	QAngle    viewangles;         // Player instantaneous view angles.
	Vector    aimdirection;       // 
	float     forwardmove;        // Forward velocity
	float     sidemove;           // Sideways velocity
	float     upmove;             // Upward velocity
	int       buttons;            // Attack button states
	byte      impulse;            // Impulse command issued.
	int       weaponselect;       // Current weapon id
	int       weaponsubtype;      // 
	int       random_seed;        // For shared random functions
	short     mousedx;            // Mouse accum in x from create move
	short     mousedy;            // Mouse accum in y from create move
	bool      hasbeenpredicted;   // Client only, tracks whether we've predicted this command at least once
	char      pad_0x4C[0x18];
};

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

enum class ItemDefinitionIndexx : int
{
	ITEM_NONE = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_DUALS = 2,
	WEAPON_FIVE7 = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALIL = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_P2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG553 = 39,
	WEAPON_SCOUT = 40,
	WEAPON_KNIFE_T = 42,
	WEAPON_FLASH = 43,
	WEAPON_HE = 44,
	WEAPON_SMOKE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INC = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_CT = 59,
	WEAPON_M4A1S = 60,
	WEAPON_USPS = 61,
	WEAPON_CZ75 = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9BAYONET = 508,
	WEAPON_KNIFE_HUNTSMAN = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_DAGGER = 516,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_HYDRA = 5035,
	WEAPON_MAX
};

struct DefItem_t
{
	DefItem_t(const char* displayName,
		const char* entityName,
		const char* entityModel,
		const char* killIcon = nullptr)
	{
		this->displayName = displayName;
		this->entityName = entityName;
		this->entityModel = entityModel;
		this->killIcon = killIcon;
	}

	const char* displayName = nullptr;
	const char* entityName = nullptr;
	const char* entityModel = nullptr;
	const char* killIcon = nullptr;
};

const std::map<ItemDefinitionIndexx, DefItem_t> ItemDefinitionIndexMap = {
	{ ItemDefinitionIndexx::ITEM_NONE,{ "<-Default->", "DEFAULT", "", "" } },
{ ItemDefinitionIndexx::WEAPON_DEAGLE,{ "#SFUI_WPNHUD_DesertEagle", "WEAPON_DEAGLE", "models/weapons/v_pist_deagle.mdl", "deagle" } },
{ ItemDefinitionIndexx::WEAPON_DUALS,{ "#SFUI_WPNHUD_Elites", "WEAPON_DUALS", "models/weapons/v_pist_elite.mdl", "elite" } },
{ ItemDefinitionIndexx::WEAPON_FIVE7,{ "#SFUI_WPNHUD_FiveSeven", "WEAPON_FIVESEVEN", "models/weapons/v_pist_fiveseven.mdl", "fiveseven" } },
{ ItemDefinitionIndexx::WEAPON_GLOCK,{ "#SFUI_WPNHUD_Glock18", "WEAPON_GLOCK", "models/weapons/v_pist_glock18.mdl", "glock" } },
{ ItemDefinitionIndexx::WEAPON_AK47,{ "#SFUI_WPNHUD_AK47", "WEAPON_AK47", "models/weapons/v_rif_ak47.mdl", "ak47" } },
{ ItemDefinitionIndexx::WEAPON_AUG,{ "#SFUI_WPNHUD_Aug", "WEAPON_AUG", "models/weapons/v_rif_aug.mdl", "aug" } },
{ ItemDefinitionIndexx::WEAPON_AWP,{ "#SFUI_WPNHUD_AWP", "WEAPON_AWP", "models/weapons/v_snip_awp.mdl", "awp" } },
{ ItemDefinitionIndexx::WEAPON_FAMAS,{ "#SFUI_WPNHUD_Famas", "WEAPON_FAMAS", "models/weapons/v_rif_famas.mdl", "famas" } },
{ ItemDefinitionIndexx::WEAPON_G3SG1,{ "#SFUI_WPNHUD_G3SG1", "WEAPON_G3SG1", "models/weapons/v_snip_g3sg1.mdl", "g3sg1" } },
{ ItemDefinitionIndexx::WEAPON_GALIL,{ "#SFUI_WPNHUD_GalilAR", "WEAPON_GALIL", "models/weapons/v_rif_galilar.mdl", "galilar" } },
{ ItemDefinitionIndexx::WEAPON_M249,{ "#SFUI_WPNHUD_M249", "WEAPON_M249", "models/weapons/v_mach_m249para.mdl", "m249" } },
{ ItemDefinitionIndexx::WEAPON_M4A1,{ "#SFUI_WPNHUD_M4A1", "WEAPON_M4A1", "models/weapons/v_rif_m4a1.mdl", "m4a1" } },
{ ItemDefinitionIndexx::WEAPON_MAC10,{ "#SFUI_WPNHUD_MAC10", "WEAPON_MAC10", "models/weapons/v_smg_mac10.mdl", "mac10" } },
{ ItemDefinitionIndexx::WEAPON_P90,{ "#SFUI_WPNHUD_P90", "WEAPON_P90", "models/weapons/v_smg_p90.mdl", "p90" } },
{ ItemDefinitionIndexx::WEAPON_UMP45,{ "#SFUI_WPNHUD_UMP45", "WEAPON_UMP45", "models/weapons/v_smg_ump45.mdl", "ump45" } },
{ ItemDefinitionIndexx::WEAPON_XM1014,{ "#SFUI_WPNHUD_xm1014", "WEAPON_XM1014", "models/weapons/v_shot_xm1014.mdl", "xm1014" } },
{ ItemDefinitionIndexx::WEAPON_BIZON,{ "#SFUI_WPNHUD_Bizon", "WEAPON_BIZON", "models/weapons/v_smg_bizon.mdl", "bizon" } },
{ ItemDefinitionIndexx::WEAPON_MAG7,{ "#SFUI_WPNHUD_Mag7", "WEAPON_MAG7", "models/weapons/v_shot_mag7.mdl", "mag7" } },
{ ItemDefinitionIndexx::WEAPON_NEGEV,{ "#SFUI_WPNHUD_Negev", "WEAPON_NEGEV", "models/weapons/v_mach_negev.mdl", "negev" } },
{ ItemDefinitionIndexx::WEAPON_SAWEDOFF,{ "#SFUI_WPNHUD_Sawedoff", "WEAPON_SAWEDOFF", "models/weapons/v_shot_sawedoff.mdl", "sawedoff" } },
{ ItemDefinitionIndexx::WEAPON_TEC9,{ "#SFUI_WPNHUD_Tec9", "WEAPON_TEC9", "models/weapons/v_pist_tec9.mdl", "tec9" } },
{ ItemDefinitionIndexx::WEAPON_TASER,{ "#SFUI_WPNHUD_Taser", "WEAPON_ZEUS", "models/weapons/v_eq_taser.mdl", "taser" } },
{ ItemDefinitionIndexx::WEAPON_P2000,{ "#SFUI_WPNHUD_HKP2000", "WEAPON_P2000", "models/weapons/v_pist_hkp2000.mdl", "hkp2000" } },
{ ItemDefinitionIndexx::WEAPON_MP7,{ "#SFUI_WPNHUD_MP7", "WEAPON_MP7", "models/weapons/v_smg_mp7.mdl", "mp7" } },
{ ItemDefinitionIndexx::WEAPON_MP9,{ "#SFUI_WPNHUD_MP9", "WEAPON_MP9", "models/weapons/v_smg_mp9.mdl", "mp9" } },
{ ItemDefinitionIndexx::WEAPON_NOVA,{ "#SFUI_WPNHUD_Nova", "WEAPON_NOVA", "models/weapons/v_shot_nova.mdl", "nova" } },
{ ItemDefinitionIndexx::WEAPON_P250,{ "#SFUI_WPNHUD_P250", "WEAPON_P250", "models/weapons/v_pist_p250.mdl", "p250" } },
{ ItemDefinitionIndexx::WEAPON_SCAR20,{ "#SFUI_WPNHUD_SCAR20", "WEAPON_SCAR20", "models/weapons/v_snip_scar20.mdl", "scar20" } },
{ ItemDefinitionIndexx::WEAPON_SG553,{ "#SFUI_WPNHUD_SG556", "WEAPON_SG553", "models/weapons/v_rif_sg556.mdl", "sg556" } },
{ ItemDefinitionIndexx::WEAPON_SCOUT,{ "#SFUI_WPNHUD_SSG08", "WEAPON_SCOUT", "models/weapons/v_snip_ssg08.mdl", "ssg08" } },
{ ItemDefinitionIndexx::WEAPON_KNIFE_CT,{ "#SFUI_WPNHUD_Knife", "WEAPON_KNIFE", "models/weapons/v_knife_default_ct.mdl", "knife_default_ct" } },
{ ItemDefinitionIndexx::WEAPON_FLASH,{ "#SFUI_WPNHUD_FLASHBANG", "WEAPON_FLASHBANG", "models/weapons/v_eq_flashbang.mdl", "flashbang" } },
{ ItemDefinitionIndexx::WEAPON_HE,{ "#SFUI_WPNHUD_HE_Grenade", "WEAPON_HEGRENADE", "models/weapons/v_eq_fraggrenade.mdl", "hegrenade" } },
{ ItemDefinitionIndexx::WEAPON_SMOKE,{ "#SFUI_WPNHUD_Smoke_Grenade", "WEAPON_SMOKEGRENADE", "models/weapons/v_eq_smokegrenade.mdl", "smokegrenade" } },
{ ItemDefinitionIndexx::WEAPON_MOLOTOV,{ "#SFUI_WPNHUD_MOLOTOV", "WEAPON_MOLOTOV", "models/weapons/v_eq_molotov.mdl", "inferno" } },
{ ItemDefinitionIndexx::WEAPON_DECOY,{ "#SFUI_WPNHUD_DECOY", "WEAPON_DECOY", "models/weapons/v_eq_decoy.mdl", "decoy" } },
{ ItemDefinitionIndexx::WEAPON_INC,{ "#SFUI_WPNHUD_IncGrenade", "WEAPON_INCGRENADE", "models/weapons/v_eq_incendiarygrenade.mdl", "inferno" } },
{ ItemDefinitionIndexx::WEAPON_C4,{ "#SFUI_WPNHUD_C4", "WEAPON_C4", "models/weapons/v_ied.mdl" } },
{ ItemDefinitionIndexx::WEAPON_KNIFE_T,{ "#SFUI_WPNHUD_Knife", "WEAPON_KNIFE_T", "models/weapons/v_knife_default_t.mdl", "knife_t" } },
{ ItemDefinitionIndexx::WEAPON_M4A1S,{ "#SFUI_WPNHUD_M4_SILENCER", "WEAPON_M4A1S", "models/weapons/v_rif_m4a1_s.mdl", "m4a1_silencer" } },
{ ItemDefinitionIndexx::WEAPON_USPS,{ "#SFUI_WPNHUD_USP_SILENCER", "WEAPON_USP", "models/weapons/v_pist_223.mdl", "usp_silencer" } },
{ ItemDefinitionIndexx::WEAPON_CZ75,{ "#SFUI_WPNHUD_CZ75", "WEAPON_CZ75", "models/weapons/v_pist_cz_75.mdl", "cz75a" } },
{ ItemDefinitionIndexx::WEAPON_REVOLVER,{ "#SFUI_WPNHUD_REVOLVER", "WEAPON_REVOLVER", "models/weapons/v_pist_revolver.mdl", "revolver" } },
{ ItemDefinitionIndexx::WEAPON_BAYONET,{ "#SFUI_WPNHUD_KnifeBayonet", "WEAPON_KNIFE_BAYONET", "models/weapons/v_knife_bayonet.mdl", "bayonet" } },
{ ItemDefinitionIndexx::WEAPON_KNIFE_FLIP,{ "#SFUI_WPNHUD_KnifeFlip", "WEAPON_KNIFE_FLIP", "models/weapons/v_knife_flip.mdl", "knife_flip" } },
{ ItemDefinitionIndexx::WEAPON_KNIFE_GUT,{ "#SFUI_WPNHUD_KnifeGut", "WEAPON_KNIFE_GUT", "models/weapons/v_knife_gut.mdl", "knife_gut" } },
{ ItemDefinitionIndexx::WEAPON_KNIFE_KARAMBIT,{ "#SFUI_WPNHUD_KnifeKaram", "WEAPON_KNIFE_KARAMBIT", "models/weapons/v_knife_karam.mdl", "knife_karambit" } },
{ ItemDefinitionIndexx::WEAPON_KNIFE_M9BAYONET,{ "#SFUI_WPNHUD_KnifeM9", "WEAPON_KNIFE_M9BAYONET", "models/weapons/v_knife_m9_bay.mdl", "knife_m9_bayonet" } },
{ ItemDefinitionIndexx::WEAPON_KNIFE_HUNTSMAN,{ "#SFUI_WPNHUD_KnifeTactical", "WEAPON_KNIFE_HUNTSMAN", "models/weapons/v_knife_tactical.mdl", "knife_tactical" } },
{ ItemDefinitionIndexx::WEAPON_KNIFE_FALCHION,{ "#SFUI_WPNHUD_knife_falchion_advanced", "WEAPON_KNIFE_FALCHION", "models/weapons/v_knife_falchion_advanced.mdl", "knife_falchion" } },
{ ItemDefinitionIndexx::WEAPON_KNIFE_BOWIE,{ "#SFUI_WPNHUD_knife_survival_bowie", "WEAPON_KNIFE_BOWIE", "models/weapons/v_knife_survival_bowie.mdl", "knife_survival_bowie" } },
{ ItemDefinitionIndexx::WEAPON_KNIFE_BUTTERFLY,{ "#SFUI_WPNHUD_Knife_Butterfly", "WEAPON_KNIFE_BUTTERFLY", "models/weapons/v_knife_butterfly.mdl", "knife_butterfly" } },
{ ItemDefinitionIndexx::WEAPON_KNIFE_DAGGER,{ "#SFUI_WPNHUD_knife_push", "WEAPON_KNIFE_DAGGER", "models/weapons/v_knife_push.mdl", "knife_push" } },
{ ItemDefinitionIndexx::GLOVE_STUDDED_BLOODHOUND,{ "#CSGO_Wearable_t_studdedgloves", "studded_bloodhound_gloves", "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl" } },
{ ItemDefinitionIndexx::GLOVE_T_SIDE,{ "#CSGO_Wearable_t_defaultgloves", "t_gloves", "models/weapons/v_models/arms/glove_fingerless/v_glove_fingerless.mdl" } },
{ ItemDefinitionIndexx::GLOVE_CT_SIDE,{ "#CSGO_Wearable_ct_defaultgloves", "ct_gloves", "models/weapons/v_models/arms/glove_hardknuckle/v_glove_hardknuckle.mdl" } },
{ ItemDefinitionIndexx::GLOVE_SPORTY,{ "#CSGO_Wearable_v_sporty_glove", "sporty_gloves", "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl" } },
{ ItemDefinitionIndexx::GLOVE_SLICK,{ "#CSGO_Wearable_v_slick_glove", "slick_gloves", "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl" } },
{ ItemDefinitionIndexx::GLOVE_LEATHER_WRAP,{ "#CSGO_Wearable_v_leather_handwrap", "leather_handwraps", "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl" } },
{ ItemDefinitionIndexx::GLOVE_MOTORCYCLE,{ "#CSGO_Wearable_v_motorcycle_glove", "motorcycle_gloves", "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl" } },
{ ItemDefinitionIndexx::GLOVE_SPECIALIST,{ "#CSGO_Wearable_v_specialist_glove", "specialist_gloves", "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl" } }
};

enum MaterialPropertyTypes_t
{
	MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0,					// bool
	MATERIAL_PROPERTY_OPACITY,								// int (enum MaterialPropertyOpacityTypes_t)
	MATERIAL_PROPERTY_REFLECTIVITY,							// vec3_t
	MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS				// bool
};

enum ImageFormat
{
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,			// Single-channel 32-bit floating point
	IMAGE_FORMAT_RGB323232F,	// NOTE: D3D9 does not have this format
	IMAGE_FORMAT_RGBA32323232F,
	IMAGE_FORMAT_RG1616F,
	IMAGE_FORMAT_RG3232F,
	IMAGE_FORMAT_RGBX8888,

	IMAGE_FORMAT_NULL,			// Dummy format which takes no video memory

								// Compressed normal map formats
								IMAGE_FORMAT_ATI2N,			// One-surface ATI2N / DXN format
								IMAGE_FORMAT_ATI1N,			// Two-surface ATI1N format

								IMAGE_FORMAT_RGBA1010102,	// 10 bit-per component render targets
								IMAGE_FORMAT_BGRA1010102,
								IMAGE_FORMAT_R16F,			// 16 bit FP format

															// Depth-stencil texture formats
															IMAGE_FORMAT_D16,
															IMAGE_FORMAT_D15S1,
															IMAGE_FORMAT_D32,
															IMAGE_FORMAT_D24S8,
															IMAGE_FORMAT_LINEAR_D24S8,
															IMAGE_FORMAT_D24X8,
															IMAGE_FORMAT_D24X4S4,
															IMAGE_FORMAT_D24FS8,
															IMAGE_FORMAT_D16_SHADOW,	// Specific formats for shadow mapping
															IMAGE_FORMAT_D24X8_SHADOW,	// Specific formats for shadow mapping

																						// supporting these specific formats as non-tiled for procedural cpu access (360-specific)
																						IMAGE_FORMAT_LINEAR_BGRX8888,
																						IMAGE_FORMAT_LINEAR_RGBA8888,
																						IMAGE_FORMAT_LINEAR_ABGR8888,
																						IMAGE_FORMAT_LINEAR_ARGB8888,
																						IMAGE_FORMAT_LINEAR_BGRA8888,
																						IMAGE_FORMAT_LINEAR_RGB888,
																						IMAGE_FORMAT_LINEAR_BGR888,
																						IMAGE_FORMAT_LINEAR_BGRX5551,
																						IMAGE_FORMAT_LINEAR_I8,
																						IMAGE_FORMAT_LINEAR_RGBA16161616,

																						IMAGE_FORMAT_LE_BGRX8888,
																						IMAGE_FORMAT_LE_BGRA8888,

																						NUM_IMAGE_FORMATS
};

enum ItemDefinitionIndex : int
{
	WEAPON_NONE = 0,
	WEAPON_DEAGLE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INCGRENADE,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER
};

#define	CONTENTS_EMPTY			0		// No contents

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	CONTENTS_OPAQUE

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200	

// unused 
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
// CONTENTS_OPAQUE + SURF_NODRAW count as CONTENTS_OPAQUE (shadow-casting toolsblocklight textures)
#define CONTENTS_BLOCKLIGHT		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions 
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

#define	MASK_SHOT	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

// NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
#define	SURF_LIGHT		0x0001		// value will hold the light strength
#define	SURF_SKY2D		0x0002		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
#define	SURF_SKY		0x0004		// don't draw, but add to skybox
#define	SURF_WARP		0x0008		// turbulent water warp
#define	SURF_TRANS		0x0010
#define SURF_NOPORTAL	0x0020	// the surface can not have a portal placed on it
#define	SURF_TRIGGER	0x0040	// FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define	SURF_NODRAW		0x0080	// don't bother referencing the texture

#define	SURF_HINT		0x0100	// make a primary bsp splitter

#define	SURF_SKIP		0x0200	// completely ignore, allowing non-closed brushes
#define SURF_NOLIGHT	0x0400	// Don't calculate light
#define SURF_BUMPLIGHT	0x0800	// calculate three lightmaps for the surface for bumpmapping
#define SURF_NOSHADOWS	0x1000	// Don't receive shadows
#define SURF_NODECALS	0x2000	// Don't receive decals
#define SURF_NOPAINT	SURF_NODECALS	// the surface can not have paint placed on it
#define SURF_NOCHOP		0x4000	// Don't subdivide patches on this surface 
#define SURF_HITBOX		0x8000	// surface is part of a hitbox

#define	MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks fluid movement
#define	MASK_NPCFLUID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
// water physics in these contents
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// bullets see these as solid, except monsters (world+brush only)
#define MASK_SHOT_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPlocalweaponsORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPlocalweaponsORLDSTATIC_FLUID	(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

// UNDONE: This is untested, any moving water
#define MASK_CURRENT				(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define	MASK_DEADSOLID				(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)

enum ClassID_t {
	CAI_BaseNPC = 0,
	CAK47,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBRC4Target,
	CBreachCharge,
	CBreachChargeProjectile,
	CBreakableProp,
	CBreakableSurface,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPlayer,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDangerZone,
	CDangerZoneController,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDrone,
	CDronegun,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvGasCanister,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFists,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CGrassBurn,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoMapRegion,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CItemCash,
	CItemDogtags,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMaterialModifyControl,
	CMelee,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParadropChopper,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPhysPropAmmoBox,
	CPhysPropLootCrate,
	CPhysPropRadarJammer,
	CPhysPropWeaponUpgrade,
	CPlantedC4,
	CPlasma,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPointWorldText,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropCounter,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CSurvivalSpawnChopper,
	CTablet,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWorld,
	CWorldVguiText,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail,
};