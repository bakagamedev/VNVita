#include "gamemain.h"

GameMain::GameMain()
{
	StatusCode = StatusType::OK;
	vita2d_init();
	vita2d_set_vblank_wait(true);
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
				NovelBrowser browser;
				browser.Run();
				if(browser.StatusCode == StatusType::GoLoad)
				{
					
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