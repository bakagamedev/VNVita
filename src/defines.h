#pragma once
#include "common.h"

enum class StatusType
{
	OK,
	GenericFail,
	EpicFail,
	MainDirectoryFail,
	GoLoad,
	Finished,
};

enum class MenuStateType
{
	OK,
	QuitNovel,
};

enum class NovelType
{
	Error,
	VNVita,
	VNDS,
};

constexpr static const int SCREEN_WIDTH  = 960;
constexpr static const int SCREEN_HEIGHT = 544;

constexpr static const char * VersionString = "0.1a";

constexpr static const char * ASSET_LogoSmall = "app0:assets/logosmall.png";
constexpr static const char * ASSET_ArrowUp	  = "app0:assets/arrowup.png";
constexpr static const char * ASSET_ArrowDown = "app0:assets/arrowdown.png";
constexpr static const char * ASSET_NoAsset	  = "app0:assets/nofile.png";
constexpr static const char * ASSET_VNDSFlag  = "app0:assets/vndslogo.png";
constexpr static const char * ASSET_VNVitaFlag= "app0:assets/vnvitalogo.png";
constexpr static const char * ASSET_NoIcon	  = "app0:assets/noicon.png";

//constexpr static const auto 
constexpr static const auto COLOUR_Font					= RGBA8(0,0,0,255);
constexpr static const auto COLOUR_Deselected			= RGBA8(28,28,28,255);
constexpr static const auto COLOUR_Selected  			= RGBA8(200,200,200,255);
constexpr static const auto COLOUR_UIBackgroundFocus	= RGBA8(114, 137, 217, 255);
constexpr static const auto COLOUR_UIBackground			= RGBA8(166, 191, 204, 255);
constexpr static const auto COLOUR_UITitlebar			= RGBA8(74 ,  98, 109, 255);
constexpr static const auto COLOUR_UIBorder 			= RGBA8(255,255,255,255);