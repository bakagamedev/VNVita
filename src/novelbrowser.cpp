#include "novelbrowser.h"

NovelBrowser::NovelBrowser()
{
	std::string SearchPath = "ux0:data/vnvita/";
	SceUID uid = sceIoDopen(SearchPath.c_str());
	if(uid >= 0)
	{
		//Find potential novel directories
		SceIoDirent fileInfo;
		std::vector<std::string> DirectoryList;
		for(int next = sceIoDread(uid, &fileInfo); next != 0; next = sceIoDread(uid, &fileInfo))
		{
			if(next > 0)
			{
				SceIoStat stat = fileInfo.d_stat;
				if(stat.st_mode == 4486)	//4486 == directory
				{
					std::string name(fileInfo.d_name);
					DirectoryList.push_back(name);
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

		//Add to list
	    for (std::string Name : DirectoryList)
		{
			std::string TempPath = SearchPath;
			TempPath.append(Name);
			NovelList.push_back(NovelHeader(TempPath));
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
	SceCtrlData GamePad, GamePadLast;
	ItemSelected = 0;

	bool Ready = false;
	while(!Ready)
	{
		sceCtrlPeekBufferPositive(0, &GamePad, 1);

		if(StatusCode == ErrorType::MainDirectoryFail)
		{
			vita2d_start_drawing();
			vita2d_clear_screen();
			vita2d_pgf_draw_text(pgf, 30, 30, RGBA8(255,0,0,255), 2.0f, "bad. No directory for you.");
			vita2d_end_drawing();
			vita2d_swap_buffers();

			if(GamePad.buttons != 0)
			{
				Ready = true;
			}
		}

		if(StatusCode == ErrorType::OK)
		{
			//Picker
			if((GamePad.buttons & SCE_CTRL_UP) && ((GamePadLast.buttons & SCE_CTRL_UP) == 0))
				ItemSelected = std::max(ItemSelected-1,0);
			if((GamePad.buttons & SCE_CTRL_DOWN) && ((GamePadLast.buttons & SCE_CTRL_DOWN) == 0))
				ItemSelected = std::min(ItemSelected+1,((int)NovelList.size())-1);

			if((GamePad.buttons & SCE_CTRL_CROSS) && ((GamePadLast.buttons & SCE_CTRL_CROSS) == 0))
				Ready = true;

			vita2d_start_drawing();
			vita2d_clear_screen();

			//Header text
			int count = NovelList.size();
			char CountString[25];
			sprintf(CountString,"%d Novels detected",count);
			vita2d_pgf_draw_text(pgf, 30, 30, RGBA8(0,255,0,255), 1.5f, CountString);

			//List 'o things
			for(int i=0; i<NovelList.size(); ++i)
			{
				int y = 62 + (i*32);

				if(i == ItemSelected)
				{
					vita2d_pgf_draw_text(pgf, 40, y, RGBA8(0,0,255,255), 1.5f, ">");
				}
				vita2d_pgf_draw_text(pgf, 55, y, RGBA8(0,0,255,255), 1.5f, NovelList[i].Name.c_str());

				if(NovelList[i].Icon != NULL)
				{
					vita2d_draw_texture(NovelList[i].Icon,0,y-24);
				}
			}

			vita2d_end_drawing();
			vita2d_swap_buffers();
		}

		GamePadLast = GamePad;
	}
}

