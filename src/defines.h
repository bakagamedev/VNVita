#pragma once

enum MainState
{
	Startup,
	Browser,
	Novel,
};

enum StatusType
{
	OK,
	GenericFail,
	EpicFail,
	MainDirectoryFail,
	GoLoad,
};

enum {
	SCREEN_WIDTH  = 960,
	SCREEN_HEIGHT = 544
};

