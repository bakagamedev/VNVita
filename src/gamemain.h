#pragma once
#include "common.h"

class GameMain
{
public:
	ErrorType StatusCode;
	void GameTick();
	GameMain();
};