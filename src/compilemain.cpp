#include "compilemain.h"

CompileMain::CompileMain(NovelInfo header)
{
	this->header = header;
	loader = CompilerLoader();
	if((header.Format == NovelFormatType::VNDS) || (header.Format == NovelFormatType::VNVita))
	{
		Compiler compiler = loader.Load(header.Path+"\\scripts",header.Path+"\\compiled",header.Format);
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