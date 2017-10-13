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
		std::string Path;
		StatusType Status;
		{
			NovelBrowser browser = NovelBrowser();
			Path = browser.Run();
			Status = browser.StatusCode;
		}
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