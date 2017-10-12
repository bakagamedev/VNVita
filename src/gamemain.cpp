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

	bool Running = true;
	while(Running)
	{
		//File browser 
		NovelBrowser* browser = new NovelBrowser();
		browser->Run();

		//Todo : Load file condition
		if(browser->StatusCode == ErrorType::OK)
		{
			Running = false;
		}
		else
		{
			Running = false;
		}

		delete browser;
	}

	vita2d_fini();
	vita2d_free_pgf(pgf);

	sceKernelExitProcess(0);
}