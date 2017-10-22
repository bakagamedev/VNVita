#include "common.h"
#include "defines.h"
#include "novelheader.h"
#include "novelbrowser.h"
#include "novelmain.h"

int main(int argc, char *argv[]) 
{
	StatusType StatusCode = StatusType::OK;
	vita2d_init_advanced(8 * 1024 * 1024);
	vita2d_set_vblank_wait(true);

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