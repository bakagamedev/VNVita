#include "novelbrowser.h"

NovelBrowser::NovelBrowser()
{
	//const char *Paths[] = {"ux0:data/vnvita/","ur0:data/vnvita/","uma0:data/vnvita/"};
	std::string SearchPath = "ux0:data/vnvita/";
	Search(SearchPath.c_str());
}

NovelBrowser::~NovelBrowser()
{
	vita2d_wait_rendering_done();
	vita2d_free_pgf(pgf);
}

void NovelBrowser::Search(std::string SearchPath)
{
	NovelList.clear();
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
			NovelList.emplace_back(NovelHeader(TempPath,true));
		}

		this->StatusCode = StatusType::OK;
	}
	else
	{
		StatusCode = StatusType::MainDirectoryFail;
	}
}

std::string NovelBrowser::Run()
{
	std::string PathReturn = "";
	SceCtrlData GamePad, GamePadLast;
	ItemSelected = 0;

	bool Ready = false;
	while(!Ready)
	{
		sceCtrlPeekBufferPositive(0, &GamePad, 1);

		if(StatusCode == StatusType::MainDirectoryFail)
		{
			vita2d_start_drawing();
			vita2d_clear_screen();
			vita2d_pgf_draw_text(pgf, 0,25,RGBA8(255,0,0,255), 1.5f, "No directory!");
			vita2d_end_drawing();
			vita2d_swap_buffers();

			if(GamePad.buttons != 0)
			{
				Ready = true;
			}
		}

		if(StatusCode == StatusType::OK)
		{
			//Picker
			if((GamePad.buttons & SCE_CTRL_UP) && ((GamePadLast.buttons & SCE_CTRL_UP) == 0))
				ItemSelected = std::max(ItemSelected-1,0);
			if((GamePad.buttons & SCE_CTRL_DOWN) && ((GamePadLast.buttons & SCE_CTRL_DOWN) == 0))
				ItemSelected = std::min(ItemSelected+1,((int)NovelList.size())-1);
			
			if((GamePad.buttons & SCE_CTRL_CROSS) && ((GamePadLast.buttons & SCE_CTRL_CROSS) == 0))
			{
				StatusCode = StatusType::GoLoad;
				return NovelList[ItemSelected].Path;
			}

			vita2d_start_drawing();
			vita2d_clear_screen();

			//Header text
			int count = NovelList.size();
			char CountString[30];
			sprintf(CountString,"VNVita - %d Novels detected",count);
			vita2d_pgf_draw_text(pgf, 0,25,RGBA8(255,255,255,255), 1.5f, CountString);
			vita2d_draw_line(0,32,960,32,RGBA8(255,255,255,255));

			//Thumbnail
			auto Thumbnail = NovelList[ItemSelected].Thumbnail.get();
			if(Thumbnail != NULL)
			{
				//Scale to fit half of screen
				float Width = 100.0f;	//Small thumbs are 100px wide, vita2d textures round up to ^2 so cannot be trusted
				if(vita2d_texture_get_width(Thumbnail) > 128.0f)
				{
					Width = vita2d_texture_get_width(Thumbnail);	//Large ones are 512px, hopefully
				}
				float Scale = (960/2) / Width;//vita2d_texture_get_width(Thumbnail);	//Base scale on width of texture
				float X = 960/2;
				float Y = 32;
				vita2d_draw_texture_scale(Thumbnail, X, Y, Scale, Scale);

				char ResolutionString[10];
				sprintf(ResolutionString,"%d x %d",NovelList[ItemSelected].Width,NovelList[ItemSelected].Height);
				vita2d_pgf_draw_text(pgf, 960/2, 520,RGBA8(255,255,255,255), 1.0f, ResolutionString);
			}

			//List 'o things
			for(int i=0; i<NovelList.size(); ++i)
			{
				float Y = 64 + (i*64);

				auto White = RGBA8(255,255,255,255);
				auto Colour = RGBA8(0,0,255,255);
				if(i == ItemSelected)
					Colour = White;

				vita2d_draw_line(0,Y+32, 960/2, Y+32, White);
				vita2d_pgf_draw_text(pgf, 66, Y, Colour, 2.0f, NovelList[i].Name.c_str());
				vita2d_pgf_draw_text(pgf, 66, Y+24, RGBA8(0,0,255,255), 1.0f, NovelList[i].Path.c_str());

				auto Icon = NovelList[i].Icon.get();
				if(Icon != NULL)
				{
					float Scale = 64.0f / (float)vita2d_texture_get_width(Icon);	//Base scale on width of texture
					vita2d_draw_texture_scale(Icon, 0, Y-32, Scale, Scale);
					//vita2d_draw_texture(Icon,0,Y-32);
				}
			}

			vita2d_end_drawing();
			vita2d_swap_buffers();
		}

		GamePadLast = GamePad;
	}

	return PathReturn;
}

