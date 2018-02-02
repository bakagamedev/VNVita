#include "compilemain.h"

CompileMain::CompileMain(NovelInfo header)
{
	this->header = header;
	if(header.Format == NovelFormatType::VNDS)
		DetectVNDS();
}

void CompileMain::DetectVNDS()
{
	const std::string SearchPath = header.Path+"\\scripts";
	SceUID uid = sceIoDopen(SearchPath.c_str());
	if(uid >= 0)
	{
		SceIoDirent fileInfo;
		for(int next = sceIoDread(uid, &fileInfo); next != 0; next = sceIoDread(uid, &fileInfo))
		{
			if(next > 0)
			{
				SceIoStat stat = fileInfo.d_stat;
				if(stat.st_mode = 0000)	//???? file type here
				{
					std::string name(fileInfo.d_name);
					stringtrim(name);
					if(StringHasExtension(name,"txt"))
						sourcefiles.Add(name);
				}
			}
		}
	}
}

void CompileMain::Run()
{
	static const int Tasks = sourcefiles.Count();
	for(int i=0; i<Tasks; ++i)
	{
		//Do thing here
		progress.SetPercent(static_cast<float>(i)/static_cast<float>(Tasks));	//argh!
		Draw();
	}
}

void CompileMain::Draw()
{
	vita2d_start_drawing();
	vita2d_clear_screen();

	vita2d_draw_rectangle(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,RGBA8(0,0,0,255));
	if(!header.Preview.IsNull())
	{
		header.Preview.Draw(0,0);
		//SCREEN_WIDTH / SCREEN_HEIGHT;
	}

	progress.Draw((SCREEN_WIDTH/2)-200,SCREEN_HEIGHT-48,400,32);

	vita2d_end_drawing();
	vita2d_swap_buffers();
}