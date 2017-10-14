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

constexpr static const char * ASSET_LogoSmall = "app0:assets/logosmall.png";