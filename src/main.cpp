#include "common.h"
#include "defines.h"
#include "novelmain.h"
#include "header.h"
#include "novelbrowser.h"

int main(int argc, char *argv[]) 
{
	StatusType StatusCode = StatusType::OK;
	vita2d_init_advanced(8 * 1024 * 1024);	//8MB for video
	vita2d_set_vblank_wait(true);

	bool Running = true;
	while(Running)
	{
		NovelHeader Header;
		StatusType Status;
		{
			NovelBrowser Browser = NovelBrowser();
			Header = Browser.Run();
			Status = Browser.StatusCode;
		}
		if(Status == StatusType::GoLoad)
		{		
			
			NovelMain Novel = NovelMain(Header);
			while(Novel.StatusCode == StatusType::OK)
			{
				Novel.Run();
			}
		}
	}

	vita2d_fini();
	sceKernelExitProcess(0);
}