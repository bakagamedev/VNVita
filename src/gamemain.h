#pragma once
#include "common.h"

class GameMain
{
public:
	SDL_Window    * gWindow   = NULL;
	SDL_Renderer  * gRenderer = NULL;
	ErrorType StatusCode;

	void GameTick();
	GameMain();
	~GameMain();
};