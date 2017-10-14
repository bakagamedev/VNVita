#pragma once
#include "common.h"
#include "novelheader.h"
#include "novelbrowser.h"
#include "novelmain.h"

class GameMain
{
public:
	StatusType StatusCode;
	void GameTick();
	GameMain();
};