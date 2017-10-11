#include "novelbrowser.h"

NovelBrowser::NovelBrowser()
{
	SceUID uid = sceIoDopen("ux0:data/vnvita/");
	if(uid >= 0)
	{
		SceIoDirent fileInfo;
		for(int next = sceIoDread(uid, &fileInfo); next != 0; next = sceIoDread(uid, &fileInfo))
		{
			if(next > 0)
			{
				SceIoStat stat = fileInfo.d_stat;
				if(stat.st_mode == SCE_SO_IFDIR)
				{
					// do dir stuff
				}
			}
			else
			{
			// log error?
			}
		}
		if(sceIoDclose(uid) < 0)
		{
			// also an error
		}
		this->StatusCode = ErrorType::OK;
	}
	else
	{
		StatusCode = ErrorType::MainDirectoryFail;
	}
}

NovelBrowser::~NovelBrowser()
{
	vita2d_free_pgf(pgf);
}

void NovelBrowser::Run()
{
	SceCtrlData GamePad;
	bool Ready = false;
	while(!Ready)
	{
		sceCtrlPeekBufferPositive(0, &GamePad, 1);
		vita2d_start_drawing();
		vita2d_clear_screen();

		if(StatusCode == ErrorType::MainDirectoryFail)
		{
			vita2d_pgf_draw_text(pgf, 30, 30, RGBA8(255,0,0,255), 2.0f, "bad. No directory for you.");
			while(GamePad.buttons != 0)
			{
				//wow I hope this multithreads this sort of thing
				sceCtrlPeekBufferPositive(0, &GamePad, 1);
			}
		}
		else
		{
			//double good thing you can force close things!
			vita2d_pgf_draw_text(pgf, 30, 30, RGBA8(255,0,0,255), 2.0f, "YES!");
		}

		vita2d_end_drawing();
		vita2d_swap_buffers();
	}
}

