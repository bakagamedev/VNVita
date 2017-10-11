#include "novelbrowser.h"

NovelBrowser::NovelBrowser()
{
	StatusCode = ErrorType::OK;

	int Directory = sceIoDopen("ux0:data/vnvita/");
	if(Directory >= 0)
	{
		SceIoDirent * FileInfo;
		int Next = sceIoDRead(Directory, &FileInfo);
		while(Next != 0)
		{
			if(Next > 0)
			{
				SceIoStat * stat = FileInfo->d_stat;
				if(stat->st_mode == SCE_SO_IFDIR)
				{
					/* add directory to list of things to consider */
				}

			}
			Next = sceIoDread(Directory, &FileInfo);	//Next file
		}
		sceIoDclose(Directory); 
	}
	else
	{
		StatusCode = ErrorType::MainDirectoryFail;
		throw std::runtime_error("No directory!");
	}
}

NovelBrowser::~NovelBrowser()
{
	vita2d_free_pgf(pgf);
}

void NovelBrowser::Run()
{
	vita2d_start_drawing();
	vita2d_clear_screen();

	if(StatusCode == ErrorType::MainDirectoryFail)
	{
		vita2d_pgf_draw_text(pgf, 30, 30, RGBA8(255,0,0,255), 2.0f, "bad. No directory for you.");
		return;
	}

	vita2d_end_drawing();
	vita2d_swap_buffers();
}

