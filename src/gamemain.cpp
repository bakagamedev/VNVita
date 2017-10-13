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

	bool Running = true;
	while(Running)
	{
		std::string Path;
		NovelBrowser browser;
		Path = browser.Run();
		if(browser.StatusCode == StatusType::GoLoad)
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