#pragma once

enum ErrorType
{
	OK,
	GenericFail,
	EpicFail,
};

enum {
  SCREEN_WIDTH  = 960,
  SCREEN_HEIGHT = 544
};


class RedRectangle
{
public:
	uint8_t R;
	uint8_t G;
	uint8_t B;
};

