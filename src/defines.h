#pragma once

enum class MainState
{
	Startup,
	Browser,
	Novel,
};

enum class StatusType
{
	OK,
	GenericFail,
	EpicFail,
	MainDirectoryFail,
	GoLoad,
};

constexpr static const int SCREEN_WIDTH  = 960;
constexpr static const int	SCREEN_HEIGHT = 544;

constexpr static const char * VersionString = "0.1a";

constexpr static const char * ASSET_LogoSmall = "app0:assets/logosmall.png";

//constexpr static const auto 
constexpr static const auto COLOUR_Deselected = RGBA8(28,28,28,255);
constexpr static const auto COLOUR_Selected   = RGBA8(200,200,200,255);