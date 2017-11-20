#include "novelbrowser.h"

NovelBrowser::NovelBrowser()
{
	vita2d_set_clear_color(COLOUR_UIBackground);
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
					stringtrim(name);
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

		//Sort alphabetically (doesn't really work)
		std::sort(DirectoryList.begin(),DirectoryList.end());

		//Add to list
	    for (std::string Name : DirectoryList)
		{
			std::string TempPath = SearchPath;
			TempPath.append(Name);
			NovelList.emplace_back(TempPath);
		}

		//Remove invalid dirs
		size_t count = NovelList.size();
		for (int i=0; i<count; ++i)
		{
			if(NovelList[i].Type == NovelType::Error)
			{
				NovelList.erase(i);
				--i;
				--count;
			}
		}

		this->StatusCode = StatusType::OK;
	}
	else
	{
		StatusCode = StatusType::MainDirectoryFail;
	}
}

NovelHeader NovelBrowser::Run()
{
	std::string PathReturn = "";
	ItemSelected = 0;

	ViewModeType ViewMode = ViewModeType::List;

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
			if(Tick(ViewMode))
				return NovelList[ItemSelected].Path;

			vita2d_start_drawing();
			vita2d_clear_screen();

			vita2d_set_clip_rectangle(0,32,SCREEN_WIDTH/2,SCREEN_HEIGHT);
			vita2d_enable_clipping();

			if(ViewMode == ViewModeType::List)
				DrawList();
			else
				DrawGrid();

			vita2d_disable_clipping();

			//Preview section
			float X = SCREEN_WIDTH/2;
			float Y = 32;	
			//Status panel above thumbnail
			vita2d_draw_rectangle(X, Y, SCREEN_WIDTH/2, 32, COLOUR_UITitlebar);
			vita2d_pgf_draw_text(pgf, X,Y+25,COLOUR_Font, 1.5f,NovelList[ItemSelected].Name.c_str());
			vita2d_draw_line(X,Y+32, X+(SCREEN_WIDTH/2), Y+32, COLOUR_UIBorder);
			//Thumbnail itself
			Y += 32;
			auto Thumbnail = NovelList[ItemSelected].Thumbnail.get();
			if(Thumbnail != NULL)
			{				
				//Thumbnail
				float Width = 100.0f;	//Small thumbs are 100px wide, vita2d textures round up to ^2 so cannot be trusted
				if(vita2d_texture_get_width(Thumbnail) > 128.0f)
				{
					Width = vita2d_texture_get_width(Thumbnail);	//Large ones are 512px, hopefully
				}
				float Scale = (SCREEN_WIDTH/2) / Width;//vita2d_texture_get_width(Thumbnail);	//Base scale on width of texture

				vita2d_draw_texture_scale(Thumbnail, X, Y, Scale, Scale);
				Y += (vita2d_texture_get_height(Thumbnail)*Scale) + 16;
			}
			else
			{
				Y += 360;	//How tall a properly configured thumbnail should be.
			}
			//Text area
			char ResolutionString[10];
			sprintf(ResolutionString,"%d x %d",NovelList[ItemSelected].Width,NovelList[ItemSelected].Height);
			vita2d_pgf_draw_text(pgf, X, Y,COLOUR_Font, 1.0f, ResolutionString);

			//Headerbar
			vita2d_draw_rectangle(0, 0, SCREEN_WIDTH, 32, COLOUR_UITitlebar);
			vita2d_pgf_draw_text(pgf, 0,25,COLOUR_Font, 1.5f, "VNVita");
			vita2d_draw_line(0,32,960,32,RGBA8(255,255,255,255));	//Underscore line

			//Divide centre of screen
			vita2d_draw_line((SCREEN_WIDTH/2)-1, 32, (SCREEN_WIDTH/2), SCREEN_HEIGHT, RGBA8(255,255,255,255));	

			vita2d_end_drawing();
			vita2d_swap_buffers();
		}

		GamePadLast = GamePad;
	}

	return PathReturn;
}

bool NovelBrowser::Tick(ViewModeType &ViewMode)
{
	int GoLeft,GoRight,GoUp,GoDown;
	switch(ViewMode)
	{
		case ViewModeType::List:
		{
			GoLeft = 0;
			GoRight= 0;
			GoUp = 	 1;
			GoDown = 1;
		}; break;
		case ViewModeType::Grid:
		{
			GoLeft = 1;
			GoRight= 1;
			GoUp = 	 GridPerLine;
			GoDown = GridPerLine;
		}; break;
	}

	//Picker
	if((GamePad.buttons & SCE_CTRL_UP) && ((GamePadLast.buttons & SCE_CTRL_UP) == 0))
		ItemSelected = std::max(ItemSelected-GoUp,0);
	if((GamePad.buttons & SCE_CTRL_DOWN) && ((GamePadLast.buttons & SCE_CTRL_DOWN) == 0))
		ItemSelected = std::min(ItemSelected+GoDown,((int)NovelList.size())-1);
	if((GamePad.buttons & SCE_CTRL_LEFT) && ((GamePadLast.buttons & SCE_CTRL_LEFT) == 0))
		ItemSelected = std::max(ItemSelected-GoLeft,0);
	if((GamePad.buttons & SCE_CTRL_RIGHT) && ((GamePadLast.buttons & SCE_CTRL_RIGHT) == 0))
		ItemSelected = std::min(ItemSelected+GoRight,((int)NovelList.size())-1);
	
	if((GamePad.buttons & SCE_CTRL_CROSS) && ((GamePadLast.buttons & SCE_CTRL_CROSS) == 0))
	{
		StatusCode = StatusType::GoLoad;
		return true;
	}

	//Other buttons
	if((GamePad.buttons & SCE_CTRL_SQUARE) && ((GamePadLast.buttons & SCE_CTRL_SQUARE) == 0))
	{
		if(ViewMode == ViewModeType::List)
			ViewMode = ViewModeType::Grid;
		else
			ViewMode = ViewModeType::List;
	}

	if(ViewMode == ViewModeType::Grid)
	{
		//L & R trigger defines are swapped??
		if((GamePad.buttons & SCE_CTRL_RTRIGGER ) && ((GamePadLast.buttons & SCE_CTRL_RTRIGGER ) == 0))
		{
			GridPerLine = std::max(GridPerLine-1,4);
		}
		if((GamePad.buttons & SCE_CTRL_LTRIGGER ) && ((GamePadLast.buttons & SCE_CTRL_LTRIGGER ) == 0))
		{
			GridPerLine = std::min(GridPerLine+1,10);
		}
	}

	return false;
}

void NovelBrowser::DrawList()
{
	//List 'o things
	int IconSize = 64;
	int SelectedY = (ItemSelected * IconSize);
	if (SelectedY < ScrollY)
	{
		ScrollY -= 16;
	}
	if(SelectedY > (ScrollY+(512-IconSize)))
	{
		ScrollY += 16;
	}

	for(int i=0; i<NovelList.size(); ++i)
	{
		float Y = -ScrollY+ (64 + (i*64));
		auto Colour = (i == ItemSelected) ? COLOUR_UIBackgroundFocus : COLOUR_UIBackground;

		vita2d_draw_rectangle(0, Y-32, SCREEN_WIDTH/2, 64, Colour);

		vita2d_draw_line(0,Y+32, SCREEN_WIDTH/2, Y+32, COLOUR_UIBorder);
		vita2d_pgf_draw_text(pgf, 66, Y, COLOUR_Font, 2.0f, NovelList[i].Name.c_str());
		vita2d_pgf_draw_text(pgf, 66, Y+24, COLOUR_Font, 1.0f, NovelList[i].Path.c_str());

		auto Icon = NovelList[i].Icon.get();
		if(Icon != NULL)
		{
			float Scale = 64.0f / (float)vita2d_texture_get_width(Icon);	//Base scale on width of texture
			vita2d_draw_texture_scale(Icon, 0, Y-32, Scale, Scale);
			//vita2d_draw_texture(Icon,0,Y-32);
		}
	}
}

void NovelBrowser::DrawGrid()
{
	const float IconWidth = (SCREEN_WIDTH / 2) / GridPerLine;	//96px at 5

	float Y = 32;
	float X = 0;
	for(int i=0; i<NovelList.size(); ++i)
	{
		auto Icon = NovelList[i].Icon.get();
		if(Icon != NULL)
		{
			float Scale = IconWidth / (float)vita2d_texture_get_width(Icon);	//Base scale on width of texture
			vita2d_draw_texture_scale(Icon, X*IconWidth, Y, Scale, Scale);
		}

		if(++X >= GridPerLine)
		{
			X = 0;
			Y += IconWidth;
		}
	}
}