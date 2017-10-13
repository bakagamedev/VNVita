#include "gamemain.h"

GameMain::GameMain()
{
	StatusCode = StatusType::OK;
	vita2d_init();
	vita2d_set_vblank_wait(true);
}

void GameMain::GameTick()
{
	MainState State = MainState::Browser;

	NovelHeader * CurrentNovel;
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
					State = MainState::Novel;
					CurrentNovel = browser.NovelSelected;
				}
				else
				{
					Running = false;
				}
			};break;
			case MainState::Novel:
			{
				//Uncomment to crash console!
				/*
				NovelMain novel(CurrentNovel);
				novel.Run();
				*/
				Running = false;
			}; break;
		}
	}

	vita2d_fini();

	sceKernelExitProcess(0);
}