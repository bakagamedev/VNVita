#include "gamemain.h"

GameMain::GameMain()
{
	StatusCode = StatusType::OK;
	vita2d_init();
	vita2d_set_vblank_wait(true);
}

void GameMain::GameTick()
{
	bool Running = true;
	while(Running)
	{
		NovelBrowser * browser = new NovelBrowser();
		std::string Path = browser->Run();
		StatusType Status = browser->StatusCode;
		delete browser;

		if(Status == StatusType::GoLoad)
		{		
			NovelMain novel = NovelMain(Path);
			novel.Run();
		}
		else
		{
			Running = false;
		}
	}

	vita2d_fini();

	sceKernelExitProcess(0);
}