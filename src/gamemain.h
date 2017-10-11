#pragma once
#include "common.h"

class GameMain
{
private:
	SDL_Window    * gWindow   = NULL;
	SDL_Renderer  * gRenderer = NULL;
	SceCtrlData GamePad;

public:
	ErrorType StatusCode;
	void GameTick();
	GameMain();
	~GameMain();
};