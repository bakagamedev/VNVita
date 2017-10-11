#pragma once
#include "common.h"

class GameMain
{
private:
	SceCtrlData GamePad;

public:
	ErrorType StatusCode;
	void GameTick();
	GameMain();
};