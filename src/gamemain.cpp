#include "gamemain.h"

GameMain::GameMain()
{
	StatusCode = ErrorType::OK;

	SDL_Init( SDL_INIT_VIDEO );
	gWindow = SDL_CreateWindow( "Test!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer( gWindow, -1, 0);
}

GameMain::~GameMain()
{
	SDL_Delay(500);
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );

	SDL_Quit();
	sceKernelExitProcess(0);
}

void GameMain::GameTick()
{
	RedRectangle rect;

	SDL_Rect fillRect = { SCREEN_WIDTH  / 4, 
		SCREEN_HEIGHT / 4, 
		SCREEN_WIDTH  / 2, 
		SCREEN_HEIGHT / 2 
	};

	for(uint16_t tick = 0; tick < 255; ++tick)
	{
		rect.R = tick;
		rect.G = 255 - tick;
		rect.B = 255 - tick;
		SDL_SetRenderDrawColor( gRenderer, rect.R,rect.G,rect.B, 255);
		SDL_RenderFillRect( gRenderer, &fillRect );
		SDL_RenderPresent( gRenderer );
		SDL_Delay(1000/255);
	}
}