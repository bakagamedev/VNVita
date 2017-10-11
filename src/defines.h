#pragma once

enum MainState
{
	Startup,
	Browser,
	Novel,
};

enum ErrorType
{
	OK,
	GenericFail,
	EpicFail,
	MainDirectoryFail,
};

enum {
	SCREEN_WIDTH  = 960,
	SCREEN_HEIGHT = 544
};

