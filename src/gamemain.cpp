#include "gamemain.h"

GameMain::GameMain()
{
	StatusCode = ErrorType::OK;
	vita2d_init();
}

void GameMain::GameTick()
{
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

	MainState State = MainState::Browser;
	bool Running = true;
	while(Running)
	{
		switch(State)
		{
			case MainState::Browser:
			{
				
			};break;
			case MainState::Novel:
			{
				
			}; break;
		}

		/*
		if (GamePad.buttons & SCE_CTRL_DOWN)
			tick--;
		if (GamePad.buttons & SCE_CTRL_UP)
			tick++;
		*/
	}

	vita2d_fini();
	vita2d_free_pgf(pgf);

	sceKernelExitProcess(0);
}