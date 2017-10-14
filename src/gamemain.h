#pragma once
#include "common.h"
#include "novelbrowser.h"
#include "novelmain.h"

class GameMain
{
public:
	StatusType StatusCode;
	void GameTick();
	GameMain();
};