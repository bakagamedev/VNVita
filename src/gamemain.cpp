#include "gamemain.h"

GameMain::GameMain()
{
	StatusCode = ErrorType::OK;
	vita2d_init();
	vita2d_set_vblank_wait(true);
}

void GameMain::GameTick()
{
	vita2d_pgf * pgf = vita2d_load_default_pgf();	//Font!

	MainState State = MainState::Browser;

	NovelBrowser browser;

	bool Running = true;
	while(Running)
	{
		switch(State)
		{
			case MainState::Browser:
			{
				browser.Run();

				//Todo : Load file condition
				if(browser.StatusCode == ErrorType::OK)
				{

					Running = false;
				}
				else
				{
					Running = false;
				}
			};break;
			case MainState::Novel:
			{
				
			}; break;
		}
	}

	vita2d_fini();
	vita2d_free_pgf(pgf);

	sceKernelExitProcess(0);
}